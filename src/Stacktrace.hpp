#pragma once

#include <array>
#include <cstdio>
#include <cxxabi.h>
#include <dlfcn.h>
#include <iostream>
#include <libproc.h>
#include <regex>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

#define UNW_LOCAL_ONLY

#include <libunwind.h>

class Stacktrace {
private:
  // This is a pure class, it cannot be instantiated.
  Stacktrace() = delete;
  Stacktrace(const Stacktrace&) = delete;
  Stacktrace& operator=(const Stacktrace&) = delete;
  ~Stacktrace() = delete;

  static void* FindImageLoadAddress() {
    Dl_info info;

    dladdr((const void*) &FindImageLoadAddress, &info);
    return info.dli_fbase;
  }

  static std::string FindProcessPath() {
    std::array<char, PROC_PIDPATHINFO_MAXSIZE> buffer{};
    int ret;
    pid_t pid;

    pid = getpid();
    ret = proc_pidpath(pid, buffer.data(), buffer.size());
    if (ret <= 0) {
      std::ostringstream ss;
      ss << __FILE__ << ":" << __LINE__ << "proc_pidpath() failed: " << strerror(errno)
         << std::endl;
      throw std::runtime_error(ss.str());
    }

    return buffer.data();
  }

  static std::string ExecuteCommand(const char* cmd) {
    std::array<char, 128> buffer{};
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
      std::ostringstream ss;
      ss << __FILE__ << ":" << __LINE__ << "popen() failed" << std::endl;
      throw std::runtime_error(ss.str());
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
      result += buffer.data();
    }
    return result;
  }

  static std::string AddressToLine(const void* load_address, const void* address) {
    std::ostringstream command;
    std::string process_path = FindProcessPath();

    command << "atos -o "
            << process_path
            << " -fullPath -l "
            << load_address
            << " "
            << address
            << std::endl;

    std::string command_output = ExecuteCommand(command.str().c_str());
    command_output = command_output.substr(0, command_output.find("\n"));

    // Check string.
    std::regex regex("\\(.*\\)$");
    std::smatch match;
    std::regex_search(command_output, match, regex);

    if (match.empty()) {
      return "??";
    }

    command_output = command_output.substr(command_output.find_last_of("(") + 1);
    command_output = command_output.substr(0, command_output.find_last_of(")"));

    return command_output;
  }

public:
  static std::vector<std::string> GetTrace(bool with_line_number = true, int frames_to_drop = 0) {
    std::vector<std::string> stack_frames;
    // Get the load address which corresponds to the image slide caused by ASLR.
    void* load_address = FindImageLoadAddress();

    unw_cursor_t cursor;
    unw_context_t context;

    // Initialize cursor to current frame for local unwinding.
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    for (int f = 0; f < frames_to_drop && unw_step(&cursor) < 0; ++f) {}

    // Unwind frames one by one, going up the frame stack.
    int i = 0;
    while (unw_step(&cursor) > 0) {
      unw_word_t pc;
      unw_word_t offset;

      unw_get_reg(&cursor, UNW_REG_IP, &pc);
      if (pc == 0) {
        break;
      }

      char stack_frame[4096] = {};
      char sym[256];
      if (unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
        char* function_symbol = sym;
        int status;
        char* demangled_symbol = abi::__cxa_demangle(sym, nullptr, nullptr, &status);
        if (status == 0) {
          function_symbol = demangled_symbol;
        }
        sprintf(stack_frame, "%4d: 0x%llx - %s", i, pc, function_symbol);
        free(demangled_symbol);
      }
      else {
        sprintf(stack_frame, "%4d: 0x%llx - unable to obtain symbol name for this frame",
                i, pc);
      }

      std::string frame_str(stack_frame);

      if (with_line_number) {
        std::string line_info = AddressToLine(load_address, (const void*) pc);
        frame_str += "\n                  at " + line_info;
      }

      stack_frames.push_back(frame_str);

      i++;
    }

    return stack_frames;
  }

  static void Print(bool with_line_number = true, int frames_to_drop = 0) {
    auto frames = GetTrace(with_line_number, frames_to_drop + 1);
    std::for_each(frames.cbegin(), frames.cend(),
                  [](const std::string& frame) { std::cerr << frame << std::endl; });
  }
};

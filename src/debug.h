#pragma once

#include "Config.h"
#include "Stacktrace.hpp"
#include <fmt/core.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define PANIC(...)                                                       \
  do {                                                                   \
    fprintf(stderr, "panicked at '");                                    \
    fprintf(stderr, __VA_ARGS__);                                        \
    fprintf(stderr, "', %s:%d\nstack backtrace:\n", __FILE__, __LINE__); \
    Stacktrace::Print(DEBUG_ENABLE_STACKTRACE_LINE);                     \
    abort();                                                             \
  } while (0)

#define ASSERT(EXPRESSION)                                                                                 \
  do {                                                                                                     \
    if (!(EXPRESSION)) {                                                                                   \
      fprintf(stderr, "Assertion failed: %s, %s:%d\nstack backtrace:\n", #EXPRESSION, __FILE__, __LINE__); \
      Stacktrace::Print(DEBUG_ENABLE_STACKTRACE_LINE);                                                     \
      abort();                                                                                             \
    }                                                                                                      \
  } while (0)

#define _GL(_call)                                       \
  do {                                                   \
    _call;                                               \
    GLenum err = glGetError();                           \
    if (err != GL_NO_ERROR) {                            \
      PANIC("OpenGL error %08x, for %s\n", err, #_call); \
    }                                                    \
  } while (0)

#if DEBUG_ENABLED
#define GL(_call) _GL(_call)
#else
#define GL(_call) _call
#endif

template<>
struct fmt::formatter<glm::mat4> {
  constexpr auto parse(format_parse_context& ctx) {
    return ctx.begin();
  }

  template<typename FormatContext>
  auto format(const glm::mat4& d, FormatContext& ctx) {
    format_to(ctx.out(), "{:<10} {:<10} {:<10} {:<10}\n", d[0][0], d[0][1], d[0][2], d[0][3]);
    format_to(ctx.out(), "{:<10} {:<10} {:<10} {:<10}\n", d[1][0], d[1][1], d[1][2], d[1][3]);
    format_to(ctx.out(), "{:<10} {:<10} {:<10} {:<10}\n", d[2][0], d[2][1], d[2][2], d[2][3]);
    return format_to(ctx.out(), "{:<10} {:<10} {:<10} {:<10}", d[3][0], d[3][1], d[3][2], d[3][3]);
  }
};

template<typename... Args>
void p(const char* format, const Args&... args) {
  fmt::vprint(format, fmt::make_format_args(args...));
  fmt::print("\n");
}

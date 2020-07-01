#include "Game.h"
#include "Stacktrace.hpp"
#include <iostream>

void on_exception() {
  if (auto ex = std::current_exception()) {
    try {
      std::rethrow_exception(ex);
    }
    catch (std::exception& ex) {
      std::cerr << "Uncaught exception: " << ex.what() << std::endl;
    }
    catch (...) {
      std::cerr << "Uncaught exception (unknown)" << std::endl;
    }
  }
  else {
    std::cerr << "Terminated due to unknown reason" << std::endl;
  }

  Stacktrace::Print(true);
  std::abort();
}

int main() {
  std::set_terminate(on_exception);

  Game game;
  int error;

  error = game.Run();
  if (error) {
    return error;
  }

  return 0;
}

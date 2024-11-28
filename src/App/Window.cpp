#include "Window.h"
#include <Utilities/Logger.h>

namespace App {
  Window::Window(const std::string& title, int width, int height) : logger("Window") {
    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
      logger.Log(Util::LogLevel::ERROR, "Failed to create SDL window");
      throw std::runtime_error("Failed to create SDL window");
    }

      logger.Log(Util::LogLevel::TRACE, "SDL window initialized");
  }

  Window::~Window() {
    if (window) {
      SDL_DestroyWindow(window);
      logger.Log(Util::LogLevel::TRACE, "Destroyed SDL window");
    }
  }

  SDL_Window* Window::GetSDLWindow() const {
    return window;
  }
}

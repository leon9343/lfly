#include "App.h"
#include <Utilities/Logger.h>

#include <SDL2/SDL.h>
#include <stdexcept>

namespace App {
  Application::Application(const std::string& title, int width, int height) : logger("Application") {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
      logger.Log(Util::LogLevel::ERROR, "Failed to initialze SDL");
      throw std::runtime_error("Failed to initialize SDL");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = std::make_unique<Window>(title, width, height);
    eventHandler = std::make_unique<EventHandler>();
    graphicsEngine = std::make_unique<Graphics::GraphicsEngine>(*window);

    logger.Log(Util::LogLevel::INFO, "OpenGL version: " + std::string((const char*)glGetString(GL_VERSION)));
    logger.Log(Util::LogLevel::INFO, "GLSL version: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));

    isRunning = true;
  }

  Application::~Application() {
    SDL_Quit();
  }

  void Application::Run() {
    logger.Log(Util::LogLevel::INFO, "Application started");

    while (isRunning) {
      eventHandler->PollEvents();

      if (eventHandler->ShouldQuit()) {
        isRunning = false;
        logger.Log(Util::LogLevel::TRACE, "Application received QUIT event");
      }

      graphicsEngine->Render();
    }

    logger.Log(Util::LogLevel::INFO, "Application stopped");
  }
}

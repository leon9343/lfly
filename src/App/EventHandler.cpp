#include "EventHandler.h"
#include <Utilities/Logger.h>

namespace App {
  EventHandler::EventHandler() : logger("EventHandler") {
    logger.Log(Util::LogLevel::TRACE, "EventHandler initialized");
  }

  void EventHandler::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          logger.Log(Util::LogLevel::INFO, "Received quit event");
          break;

        default:
          break;
      }
    }

  }

  bool EventHandler::ShouldQuit() const {
    return quit;
  }

}

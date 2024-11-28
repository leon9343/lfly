#pragma once
#include <Utilities/Logger.h>

#include <SDL2/SDL.h>

namespace App {

  /**
   * @brief The EventHandler class handles mouse/keyboard inputs and other kinds of events
   *
   * The class processes polled events from SDL2 and allows for custom callbacks
   */
  class EventHandler {
  public:
    EventHandler();
    /**
     * @brief Processes pending SDL2 events
     *
     * The function polls events from SDL2 and calls the relative handlers
     */
    void PollEvents();

    /**
     * @brief Checks if the application should quit
     *
     * @return true if a quit event has been polled, false otherwise
     */
    bool ShouldQuit() const;

    // TODO callback set
  
  private:
    Util::Logger logger;  ///< Logger instance for EventHandler

    bool quit = false;    ///< Flag indicating whether a quit event has been received
  };

}

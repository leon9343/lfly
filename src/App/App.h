#pragma once

#include "Window.h"
#include "EventHandler.h"
#include <Graphics/Graphics.h>
#include <memory>
#include <string>

namespace App {

  /**
   * @brief The Application class initializes SDL2, creates the window and event handler
   *
   * The class handles the application lifecycle 
   */
  class Application {
  public:
    /**
     * @brief Constructs the Application
     * @param title  The title of the window
     * @param width  The width of the window
     * @param height The height of the window
     */
    Application(const std::string& title, int width, int height);

    /**
     * @brief Destructor which ensures proper application resources cleanup
     */
    ~Application();

    /**
     * @brief Runs the application loop
     */
    void Run();

  private:
    std::unique_ptr<Window> window;                           ///< The Application window
    std::unique_ptr<EventHandler> eventHandler;               ///< The event handler
    std::unique_ptr<Graphics::GraphicsEngine> graphicsEngine; ///< The graphics engine for rendering objects
    Util::Logger logger;                                      ///< Logger instance for App
    bool isRunning = false;                                   ///< Flag indicating whether the app should run or not
  };
}

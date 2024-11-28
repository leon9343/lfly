#pragma once
#include <Utilities/Logger.h>

#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>

namespace App {
  
  /**
   * @brief The Window class manages the SDL2 window 
   *
   * Encapsulates the creation and management of the SDL2 window
   */
  class Window {
  public:
    /**
     * @brief Constructs a window with the specified properties
     * @param title  The title of the window
     * @param width  The window width in pixels
     * @param height The window height in pixels
     */
    Window(const std::string& title, int width, int height);

    /**
     * @brief Destructor which ensures proper window resources cleanup
     */
    ~Window();

    /**
     * @brief Retrieves the SDL_Window pointer
     * @return A pointer to the SDL_Window
     */
    SDL_Window* GetSDLWindow() const;

  private:
    SDL_Window* window = nullptr; ///< SDL_Window instance
    Util::Logger logger;          ///< Logger instance for Window

    // Copying is not allowed
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
  };
}

#pragma once
#include "Renderer.h"
#include <App/Window.h>
#include <Utilities/Logger.h>

#include <glad/glad.h>
#include <SDL2/SDL.h>

namespace Graphics {

  /**
   * @brief The GraphicsEngine class initializes OpenGL and handles rendering
   * 
   * This class sets up the OpenGL context, initializes rendering resources and provides methods to render graphics
   */
  class GraphicsEngine {
  public:
    /**
     * @brief Constructs the GraphicsEngine
     * @param window A reference to App::Window 
     */
    explicit GraphicsEngine(App::Window& window);

    /**
     * @brief Destructor to ensure proper graphics resources cleanup
     */
    ~GraphicsEngine();
    
    /**
     * @brief Initializes the graphics engine
     */
    void Initialize();

    /**
     * @brief Renders a single frame
     */
    void Render();

    /**
     * @brief Checks for OpenGL errors and issues them as warnings
     * @param context The context of the error check
     */
    void CheckGLError(const std::string& context);

  private:
    App::Window& window;      ///< Reference to application window
    SDL_GLContext glContext;  ///< The OpenGL context
    Renderer renderer;        ///< The renderer responsible for drawing
    Util::Logger logger;      ///< Logger instance for graphics engine

    // Copying is not allowed
    GraphicsEngine(const GraphicsEngine&) = delete;
    GraphicsEngine& operator=(const GraphicsEngine&) = delete;
  };

}

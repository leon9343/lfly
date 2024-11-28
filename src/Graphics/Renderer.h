#pragma once
#include "Shader.h"
#include <Utilities/Logger.h>

#include <glad/glad.h>
#include <vector>

namespace Graphics {

  /**
   * @brief The Renderer class handles drawing objects to the screen
   *
   * This class sets up vertex data and issues draw calls
   */
  class Renderer {
  public:
    /**
     * @brief Constructs the Renderer
     */
    Renderer();

    /**
     * @brief Destructor that ensures correct cleanup of resources
     */
    ~Renderer();

    /**
     * @brief Initializes the renderer
     */
    void Initialize();

    /**
     * @brief Renders the objects
     */
    void Render();



  private:
    unsigned int VAO;       ///< Vertex Array Object
    unsigned int VBO;       ///< Vertex Buffer Object
    Shader shaderProgram;   ///< Shader program for rendering
    Util::Logger logger;    ///< Logger instance of the Renderer
  };

}

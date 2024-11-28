#pragma once
#include <Utilities/Logger.h>
#include <glad/glad.h>

#include <string>

namespace Graphics {
  /**
   * @brief The Shader class handles compiling and linking shader programs
   *
   * This class streamlines shader usage
   */
  class Shader {
  public:
    /**
     * @brief Constructs the Shader
     */
    Shader();

    /**
     * @brief Destructor ensures correct resources cleanup
     */
    ~Shader();

    /**
     * @brief Compiles and links the shader program
     * @param vertexPath    The path to the vertex shader file
     * @param fragmentPath  The path to the fragment shader file
     */
    void Compile(const std::string& vertexPath, const std::string& fragmentPath);

    /**
     * @brief Activates the shader program
     */
    void Use() const;

    /**
     * @brief Retrieve the program ID
     * @return The OpenGL shader program ID
     */
    unsigned int GetID() const;

  private:
    unsigned int ID;
    Util::Logger logger;

    /**
     * @brief Loads shader code from a file.
     * @param filePath The path to the shader file.
     * @return The shader code as a string.
     */
    std::string LoadShaderCode(const std::string& filePath);

    /**
     * @brief Checks for shader compilation or linking errors
     * @param shader The shader ID to check
     * @param type   The type of shader to check 
     */
    void CheckCompileErrors(unsigned int shader, const std::string& type);
  };
}

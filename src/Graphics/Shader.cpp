#include "Shader.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Graphics {

  Shader::Shader() : ID(0), logger("Shader") {}

  Shader::~Shader() {
    if (ID != 0) {
      glDeleteProgram(ID);
    }
  }

  void Shader::Compile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = LoadShaderCode(vertexPath);
    std::string fragmentCode = LoadShaderCode(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
      throw std::runtime_error("Failed to load shader source code");
    }

    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexCode.c_str();
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentCode.c_str();
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    logger.Log(Util::LogLevel::INFO, "Shader program compiled and linked");
  }

  void Shader::Use() const {
    glUseProgram(ID);
  }

  unsigned int Shader::GetID() const {
    return ID;
  }

  std::string Shader::LoadShaderCode(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
      shaderFile.open(filePath);
      shaderStream << shaderFile.rdbuf();
      shaderFile.close();
      logger.Log(Util::LogLevel::INFO, "Loaded shader: " + filePath);
    } catch (std::ifstream::failure& e) {
      logger.Log(Util::LogLevel::ERROR, "Failed to read shader: " + filePath);
      return "";
    }

    return shaderStream.str();
  }

  void Shader::CheckCompileErrors(unsigned int shader, const std::string& type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      if (strlen(infoLog) > 0) {
        logger.Log(Util::LogLevel::INFO, "Shader (" + type + ") Info Log:\n" + infoLog);
      }
      if (!success) {
        logger.Log(Util::LogLevel::ERROR, "Shader Compilation Error (" + type + "):\n" + infoLog);
        throw std::runtime_error("Shader Compilation Failed (" + type + ")");
      }
    } else {
      glGetProgramiv(shader, GL_LINK_STATUS, &success);
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      if (strlen(infoLog) > 0) {
        logger.Log(Util::LogLevel::INFO, "Program Linking Info Log:\n" + std::string(infoLog));
      }
      if (!success) {
        logger.Log(Util::LogLevel::ERROR, "Program Linking Error:\n" + std::string(infoLog));
        throw std::runtime_error("Shader Linking Failed");
      }
    }
  }


}

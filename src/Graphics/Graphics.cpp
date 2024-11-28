#include "Graphics.h"

#include <stdexcept>

namespace Graphics {

  GraphicsEngine::GraphicsEngine(App::Window& window) : window(window), logger("GraphicsEngine") {
    glContext = SDL_GL_CreateContext(window.GetSDLWindow());
    if (!glContext) {
      logger.Log(Util::LogLevel::ERROR, "Failed to create OpenGL context" + std::string(SDL_GetError()));
      throw std::runtime_error("Failed to create OpenGL context");
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
      logger.Log(Util::LogLevel::ERROR, "Failed to initialize GLAD");
      throw std::runtime_error("Failed to initialize GLAD");
    }

    Initialize();
  }

  GraphicsEngine::~GraphicsEngine() {
    SDL_GL_DeleteContext(glContext);
    logger.Log(Util::LogLevel::TRACE, "OpenGL context destroyed");
  }

  void GraphicsEngine::Initialize() {
    renderer.Initialize();

    int width, height;
    SDL_GetWindowSize(window.GetSDLWindow(), &width, &height);
    glViewport(0, 0, width, height);

    glDisable(GL_CULL_FACE);

//    glEnable(GL_DEPTH_TEST);
    CheckGLError("Initialization");

    logger.Log(Util::LogLevel::TRACE, "GraphicsEngine initialized");
  }

  void GraphicsEngine::Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer.Render();
    CheckGLError("Render");

    SDL_GL_SwapWindow(window.GetSDLWindow());
  }

  void GraphicsEngine::CheckGLError(const std::string& context) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      logger.Log(Util::LogLevel::WARNING, "OpenGLError in " + context + ": " + std::to_string(error));
    }
  }
}

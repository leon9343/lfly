#include "Renderer.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

namespace Graphics {
  Renderer::Renderer() : VAO(0), VBO(0), logger("Renderer") {}

  Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
  }

  void Renderer::Initialize() {
    shaderProgram = Shader();

    shaderProgram.Compile(
        "/home/leonardo/dev/Graphics/lfly/src/Graphics/Shaders/triangle.vert",
        "/home/leonardo/dev/Graphics/lfly/src/Graphics/Shaders/triangle.frag"
    );

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  }

  void Renderer::Render() {
    shaderProgram.Use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
  }
}

#include "Wing.h"

namespace Sim {

  Wing::Wing(float area, float aspectRatio) : _area(area), _aspectRatio(aspectRatio) {
    _liftCoefficient = 0.0f;
    _dragCoefficient = 0.0f;
  }

  void Wing::Update(float deltaTime) {
    // TODO
  }

  glm::vec3 Wing::ComputeForce() const {
    // TODO
    glm::vec3 lift = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 drag = glm::vec3(0.0f, 0.0f, 0.0f);
    
    return lift + drag;
  }

  glm::vec3 Wing::ComputeMoment() const {
    return glm::vec3(0.0f);
  }

}

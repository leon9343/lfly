#include "Engine.h"

namespace Sim {

  Engine::Engine(float maxPower) : _maxPower(maxPower), _throttle(0.0f) {}

  void Engine::Update(float deltaTime) {
    // TODO
  }

  glm::vec3 Engine::ComputeForce() const {
    // TODO: actual calculation
    float thrust = _maxPower * _throttle;
    return glm::vec3(thrust, 0.0f, 0.0f);
  }

  glm::vec3 Engine::ComputeForce() const {
    // TODO: actual calculation
    return glm::vec3(0.0f);
  }

  glm::vec3 Engine::SetThrottle(float newThrottle) {
    _throttle = newThrottle;
  }

  
}

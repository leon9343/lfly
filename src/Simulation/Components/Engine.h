#pragma once
#include "Component.h"

namespace Sim {

  /**
   * @brief The Engine class models the aircraft's engine
   */
  class Engine : public Component {
  public:
    Engine(float maxPower);

    void Update(float deltaTime) override;

    glm::vec3 ComputeForce() const override;

    glm::vec3 ComputeMoment() const override;

    void SetThrottle(float newThrottle);

  private:
    float _throttle;  ///< Engine current throttle
    float _maxPower;  ///< Engine's max power
  };

}

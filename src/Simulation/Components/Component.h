#pragma once

namespace Sim {

  /**
   * @brief Abstract base class for aircraft components
   */
  class Component {
  public:
    virtual ~Component() = default;

    /**
     * @brief Updates the component's state
     * @param deltaTime Time step in seconds
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief Compute the moment generated by the specific component
     * @return Moment vector
     */
    virtual glm::vec3 ComputeMoment() const = 0;
  };
}
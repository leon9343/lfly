#pragma once
#include "Components/Component.h"

#include <glm/glm.hpp>

namespace Sim {

  /**
   * @brief The Aircraft class serves as an interface for different aircraft types
   *
   * The class provides an interface for different types of aircrafts which may differ in mass,
   * components, and other characteristics
   */
  class Aircraft {
  public:
    virtual ~Aircraft() = default;

    /**
     * @brief Update the state of the aircraft
     * @param deltaTime Time step in seconds
     */
    virtual void Update(float deltaTime);

    /**
     * @brief Retrieve the position of the aircraft
     * @return The aircraft's position 
     */
    glm::vec3 GetPosition() const;

    /**
     * @brief Retrieve the direction of the aircraft
     * @return The aircraft's direction 
     */
    glm::vec3 GetDirection() const;

  protected:
    glm::vec3 _position;    ///< Aircraft position
    glm::vec3 _direction;   ///< Aircraft direction
    float _weight;          ///< Aircraft weight
    // TODO: add more
  };

}

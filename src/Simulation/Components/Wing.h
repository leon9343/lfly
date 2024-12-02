#pragma once
#include "Component.h"

namespace Sim {

  /**
   * @brief The Wing class models the aircraft's wing which generates lift and drag
   */
  class Wing : public Component {
  public:

    /**
     * @brief Constructs Wing object
     * @param area Wing area in m2
     * @param liftCoefficient Lift coefficient
     * @param dragCoefficient Drag coefficient
     */
    Wing(float area, float liftCoefficient, float dragCoefficient);

    void Update(float deltaTime) override;
    void ComputeMoment() override;

  private:
    float _area;
    float _liftCoefficient;
    float _dragCoefficient;
  };

}

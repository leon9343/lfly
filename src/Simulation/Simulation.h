#pragma once
#include "Aircraft.h"
#include <Utilities/Logger.h>

#include <memory>

namespace Sim {
  
  /**
   * @brief The Simulation class handles updating the current state of the aircraft(s) on screen based on received signals
   */
  class Simulation {
  public:
    /**
     * @brief Constructs the Simulation class
     */
    Simulation();

    /**
     * @brief Updates the state of the simulation
     * @param deltaTime Time step in seconds
     */
    void Update(float deltaTime);

    /**
     * @brief Retrieves the loaded aircraft
     * @return Pointer to the simulated aircraft
     */
    const std::shared_ptr<Aircraft>& GetAircraft() const;

  private:
    std::shared_ptr<Aircraft> aircraft; ///< The simulated aircraft
    Util::Logger logger;                ///< Logger instance of the simulation
  };

}

#include "simulation.h"
#include "simulation_state.h"
#include "trains.h"
#include "switches.h"
#include "io.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std ;
// ============================================================================
// SIMULATION.CPP - Implementation of main simulation logic
// ============================================================================

// ----------------------------------------------------------------------------
// INITIALIZE SIMULATION
// ----------------------------------------------------------------------------

void initializeSimulation() {
    initializeSimulationState();
}

// ----------------------------------------------------------------------------
// SIMULATE ONE TICK
// ----------------------------------------------------------------------------

void simulateOneTick()
{
    cout << "Tick: " << currentTick << endl;

    spawnTrainsForTick();   // Day 2 logic
    determineAllRoutes();   // NEW
    detectCollisions();     // NEW
    moveAllTrains();        // Day 2 logic
    currentTick++;
}
// ----------------------------------------------------------------------------
// CHECK IF SIMULATION IS COMPLETE
// ----------------------------------------------------------------------------

bool isSimulationComplete() {
    return simulationComplete;
}

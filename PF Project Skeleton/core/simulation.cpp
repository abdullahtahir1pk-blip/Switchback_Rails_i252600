#include "simulation.h"
#include "simulation_state.h"
#include "trains.h"
#include "switches.h"
#include "io.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h> // ONLY linux
#include <iostream>
using namespace std;

// ============================================================================
// SIMULATION.CPP - Implementation of main simulation logic
// ============================================================================

// Forward (io.cpp may not declare printGrid in your header): safe forward-declare.
void printGrid();

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

    // Phase 1 - spawn
    spawnTrainsForTick();

    // Phase 2 - plan routes / next positions
    determineAllRoutes();

    // Phase 3 - update switch counters based on train positions
    updateSwitchCounters();

    // Phase 4 - queue flips if thresholds reached (deferred)
    queueSwitchFlips();

    // Phase 5 - collision detection using planned moves
    // --- any collision-printing should be added inside detectCollisions()
    detectCollisions();

    // Phase 6 - commit moves
    // --- any per-train movement prints should be added inside moveAllTrains()
    moveAllTrains();

    // Phase 7 - apply deferred flips
    // --- any switch-flip prints should be added inside applyDeferredFlips()
    applyDeferredFlips();

    // Phase 8 - arrivals / metrics
    // --- arrival-printing should be added inside checkArrivals()
    checkArrivals();

    // Render / debug output
    printGrid();

    // small delay so terminal output is readable
    usleep(300000);

    // Check if all trains are finished
    bool allDone = true;
    for (int i = 0; i < trainCount; i++)
    {
        if (trainActive[i]) { allDone = false; break; }
    }

    if (allDone)
    {
        cout << "Simulation Complete!" << endl;
        simulationComplete = true;
    }

    currentTick++;
}

// ----------------------------------------------------------------------------
// CHECK IF SIMULATION IS COMPLETE
// ----------------------------------------------------------------------------
bool isSimulationComplete() {
    return simulationComplete;
}

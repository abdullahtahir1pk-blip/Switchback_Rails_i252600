#ifndef SIMULATION_STATE_H
#define SIMULATION_STATE_H

// ============================================================================
// SIMULATION_STATE.H - Global constants and state (global-array style)
// ============================================================================

// GRID
extern int rows;
extern int cols;
extern char grid[200][200];

// TRAINS (global arrays)
extern int trainCount;
extern int trainRow[200];
extern int trainCol[200];
extern int trainDir[200];
extern bool trainActive[200];
extern int trainStartTick[200];
extern int spawnRow[200];
extern int spawnCol[200];

// Planned move arrays (Day-3/Day-4)
extern int nextRow[200];
extern int nextCol[200];
extern int nextDir[200];
extern bool willMove[200];   // true = intends to move this tick
extern bool crashed[200];

// SWITCHES
extern int switchCount;
extern char switchId[200];
extern int switchState[200];
extern int switchCounter[200];
extern bool switchFlipQueued[200];

// SIMULATION PARAMS
extern int currentTick;
extern int totalTicks;
extern bool simulationComplete;

// EMERGENCY HALT
extern bool emergencyActive;
extern int emergencyTimer;

// Initialization
void initializeSimulationState();

#endif

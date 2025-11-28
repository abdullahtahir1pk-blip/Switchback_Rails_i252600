#ifndef TRAINS_H
#define TRAINS_H

// ============================================================================
// TRAINS.H - Train logic
// ============================================================================

// Spawn trains scheduled for the current tick.
void spawnTrainsForTick();

// Compute routes for all trains (Phase 2).
void determineAllRoutes();

// Compute next position/direction for a train.
bool determineNextPosition(int id);

// Get next direction on entering a tile.
int getNextDirection(int dir, char tile);

// Choose best direction at a crossing.
int getSmartDirectionAtCrossing(int dir);

// Move trains and handle collisions (Phase 5).
void moveAllTrains();

// Detect trains targeting the same tile / swap / crossing
void detectCollisions();

// Mark trains that reached destinations.
void checkArrivals();

// Emergency halt hooks
void applyEmergencyHalt();
void updateEmergencyHalt();

#endif

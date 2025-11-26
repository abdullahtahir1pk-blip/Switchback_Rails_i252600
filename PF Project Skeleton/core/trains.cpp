#include "trains.h"
#include "simulation_state.h"
#include "grid.h"
#include "switches.h"
#include <cstdlib>

// ============================================================================
// TRAINS.CPP - Train logic
// ============================================================================
// Direction vectors
// 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
int dr[4] = {-1, 0, 1,  0};
int dc[4] = { 0, 1, 0, -1};
// Storage for planned moves (for collisions).

// Previous positions (to detect switch entry).

// ----------------------------------------------------------------------------
// SPAWN TRAINS FOR CURRENT TICK
// ----------------------------------------------------------------------------
// Activate trains scheduled for this tick.
// ----------------------------------------------------------------------------
void spawnTrainsForTick()
{
    for (int i = 0; i < trainCount; i++)
    {
        if (trainActive[i]) continue;

        if (trainStartTick[i] == currentTick)
        {
            int r = spawnRow[i];
            int c = spawnCol[i];

            // Only spawn if spot is empty
            if (grid[r][c] == 'S')
            {
                trainRow[i] = r;
                trainCol[i] = c;
                trainActive[i] = true;
            }
        }
    }
}



// ----------------------------------------------------------------------------
// DETERMINE NEXT POSITION for a train
// ----------------------------------------------------------------------------
// Compute next position/direction from current tile and rules.
// ----------------------------------------------------------------------------
bool determineNextPosition(int id) {
    //day 3 routing
    return 0 ;
}

// ----------------------------------------------------------------------------
// GET NEXT DIRECTION based on current tile and direction
// ----------------------------------------------------------------------------
// Return new direction after entering the tile.
// ----------------------------------------------------------------------------
int getNextDirection(int id , char tile) {
    //day 3 turning logic
    return 0 ;
}

// ----------------------------------------------------------------------------
// SMART ROUTING AT CROSSING - Route train to its matched destination
// ----------------------------------------------------------------------------
// Choose best direction at '+' toward destination.
// ----------------------------------------------------------------------------
int getSmartDirectionAtCrossing(int id) {
    //day 3 chose best direction
    return 0 ;
}

// ----------------------------------------------------------------------------
// DETERMINE ALL ROUTES (PHASE 2)
// ----------------------------------------------------------------------------
// Fill next positions/directions for all trains.
// ----------------------------------------------------------------------------
void determineAllRoutes() {
    //day 3 future position
}

// ----------------------------------------------------------------------------
// MOVE ALL TRAINS (PHASE 5)
// ----------------------------------------------------------------------------
// Move trains; resolve collisions and apply effects.
// ----------------------------------------------------------------------------
void moveAllTrains()
{
    for (int i = 0; i < trainCount; i++)
    {
        if (!trainActive[i])
            continue;

        int r = trainRow[i];
        int c = trainCol[i];
        int d = trainDir[i];

        // Compute next tile
        int nr = r + dr[d];
        int nc = c + dc[d];

        char tile = grid[nr][nc];

        // Track turning rules
        if (tile == '/')
        {
            if (d == 0) d = 1;
            else if (d == 1) d = 0;
            else if (d == 2) d = 3;
            else if (d == 3) d = 2;
        }
        else if (tile == '\\')
        {
            if (d == 0) d = 3;
            else if (d == 3) d = 0;
            else if (d == 2) d = 1;
            else if (d == 1) d = 2;
        }
        else if (tile == '+')
        {
            // Day-2: No routing logic yet
            // '+' behaves as straight
        }

        // Apply movement
        trainRow[i] = nr;
        trainCol[i] = nc;
        trainDir[i] = d;
    }
}

// ----------------------------------------------------------------------------
// DETECT COLLISIONS WITH PRIORITY SYSTEM
// ----------------------------------------------------------------------------
// Resolve same-tile, swap, and crossing conflicts.
// ----------------------------------------------------------------------------
void detectCollisions() {
    //day 4
}

// ----------------------------------------------------------------------------
// CHECK ARRIVALS
// ----------------------------------------------------------------------------
// Mark trains that reached destinations.
// ----------------------------------------------------------------------------
void checkArrivals() {
    //day 5 
}

// ----------------------------------------------------------------------------
// APPLY EMERGENCY HALT
// ----------------------------------------------------------------------------
// Apply halt to trains in the active zone.
// ----------------------------------------------------------------------------
void applyEmergencyHalt() {
}

// ----------------------------------------------------------------------------
// UPDATE EMERGENCY HALT
// ----------------------------------------------------------------------------
// Decrement timer and disable when done.
// ----------------------------------------------------------------------------
void updateEmergencyHalt() {
    //day 6
}


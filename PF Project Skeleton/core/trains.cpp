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
        Train &t = trains[i];

        if (t.active) continue;
        if (trainStartTick[i] != currentTick) continue;

        int r = spawnRow[i];
        int c = spawnCol[i];

        t.row = r;
        t.col = c;
        t.direction = trainDir[i];
        t.active = true;
    }
}



// ----------------------------------------------------------------------------
// DETERMINE NEXT POSITION for a train
// ----------------------------------------------------------------------------
// Compute next position/direction from current tile and rules.
// ----------------------------------------------------------------------------
bool determineNextPosition(int id)
{
    Train &t = trains[id];

    int nr = t.row + dr[t.direction];
    int nc = t.col + dc[t.direction];

    t.nextRow = nr;
    t.nextCol = nc;

    return true;
}



// ----------------------------------------------------------------------------
// GET NEXT DIRECTION based on current tile and direction
// ----------------------------------------------------------------------------
// Return new direction after entering the tile.
// ----------------------------------------------------------------------------
int getNextDirection(int dir, char tile)
{
    if (tile == '-' || tile == '|')
        return dir;
    if (tile == '/')
    {
        if (dir == 0) return 1;
        if (dir == 1) return 0;
        if (dir == 2) return 3;
        if (dir == 3) return 2;
    }
    if (tile == '\\')
    {
        if (dir == 0) return 3;
        if (dir == 3) return 0;
        if (dir == 1) return 2;
        if (dir == 2) return 1;
    }
    return dir;
}

// ----------------------------------------------------------------------------
// SMART ROUTING AT CROSSING - Route train to its matched destination
// ----------------------------------------------------------------------------
// Choose best direction at '+' toward destination.
// ----------------------------------------------------------------------------
int getSmartDirectionAtCrossing(int dir)
{
    return dir; // Day-3 simple version (full comes in Day-5)
}
// ----------------------------------------------------------------------------
// DETERMINE ALL ROUTES (PHASE 2)
// ----------------------------------------------------------------------------
// Fill next positions/directions for all trains.
void determineAllRoutes()
{
    for (int i = 0; i < trainCount; i++)
    {
        Train &t = trains[i];
        if (!t.active) continue;

        determineNextPosition(i);
    }
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
        if (!trainActive[i]) continue;

        int r = trainRow[i];
        int c = trainCol[i];
        int d = trainDir[i];

        int nr = r + dr[d];
        int nc = c + dc[d];

        char tile = grid[nr][nc];

        if (tile == '+')
            d = getSmartDirectionAtCrossing(d);
        else
            d = getNextDirection(d, tile);

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


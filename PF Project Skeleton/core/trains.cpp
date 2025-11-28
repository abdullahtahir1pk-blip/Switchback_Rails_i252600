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
        if (trainStartTick[i] != currentTick) continue;

        int r = spawnRow[i];
        int c = spawnCol[i];

        trainRow[i]  = r;
        trainCol[i]  = c;
        trainActive[i] = true;
        
        willMove[i] = false;
        nextRow[i] = -1;
        nextCol[i] = -1;
        nextDir[i] = trainDir[i];
        crashed[i] = false;
    }
}




// ----------------------------------------------------------------------------
// DETERMINE NEXT POSITION for a train
// ----------------------------------------------------------------------------
// Compute next position/direction from current tile and rules.
// ----------------------------------------------------------------------------
bool determineNextPosition(int id)
{
    if (!trainActive[id]) {
        willMove[id] = false;
        return false;
    }

    int r = trainRow[id];
    int c = trainCol[id];
    int d = trainDir[id];

    int nr = r + dr[d];
    int nc = c + dc[d];

    // safe bounds check
    if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
        // out of bounds -> mark as not moving (will be handled as crash if you want)
        willMove[id] = false;
        nextRow[id] = nr;
        nextCol[id] = nc;
        nextDir[id] = d;
        return false;
    }

    char tile = grid[nr][nc];
    int nd = d;
    if (tile == '+') {
        nd = getSmartDirectionAtCrossing(d); // day-3 simple straight, may be extended
    } else {
        nd = getNextDirection(d, tile); // handles / and \ and straight
    }

    nextRow[id] = nr;
    nextCol[id] = nc;
    nextDir[id] = nd;
    willMove[id] = true;
    crashed[id] = false;
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
    // reset plan map
    for (int i = 0; i < trainCount; ++i) {
        willMove[i] = false;
        nextRow[i] = -999; nextCol[i] = -999; nextDir[i] = trainDir[i];
        crashed[i] = false;
    }
    for (int i = 0; i < trainCount; ++i) {
        if (trainActive[i]) determineNextPosition(i);
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
        if (!willMove[i]) continue;

        int nr = nextRow[i];
        int nc = nextCol[i];
        int nd = nextDir[i];

        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) {
            trainActive[i] = false;
            crashed[i] = true;
            continue;
        }

        trainRow[i] = nr;
        trainCol[i] = nc;
        trainDir[i] = nd;

        if (grid[nr][nc] == 'D') {
            trainActive[i] = false;
        }
    }
}


// ----------------------------------------------------------------------------
// DETECT COLLISIONS WITH PRIORITY SYSTEM
// ----------------------------------------------------------------------------
// Resolve same-tile, swap, and crossing conflicts.
// ----------------------------------------------------------------------------
void detectCollisions()
{
    for (int i = 0; i < trainCount; i++)
    {
        if (!trainActive[i]) continue;

        for (int j = i + 1; j < trainCount; j++)
        {
            if (!trainActive[j]) continue;

            if (!willMove[i] || !willMove[j]) continue;

            // Same target tile
            if (nextRow[i] == nextRow[j] && nextCol[i] == nextCol[j])
            {
                willMove[i] = false;
                willMove[j] = false;
            }

            // Swap
            if (nextRow[i] == trainRow[j] && nextCol[i] == trainCol[j] &&
                nextRow[j] == trainRow[i] && nextCol[j] == trainCol[i])
            {
                willMove[i] = false;
                willMove[j] = false;
            }
        }
    }
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


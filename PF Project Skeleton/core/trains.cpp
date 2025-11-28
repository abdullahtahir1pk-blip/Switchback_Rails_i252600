#include "trains.h"
#include "simulation_state.h"
#include "grid.h"
#include "switches.h"
#include "io.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// ============================================================================
// TRAINS.CPP - Train logic (global-array style)
// ============================================================================
int dr[4] = {-1, 0, 1,  0};
int dc[4] = { 0, 1, 0, -1};

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

        trainRow[i] = r;
        trainCol[i] = c;
        // assume trainDir[i] already set during level load
        trainActive[i] = true;

        // initialize planned move arrays
        willMove[i] = false;
        nextRow[i]  = -1;
        nextCol[i]  = -1;
        nextDir[i]  = trainDir[i];
        crashed[i]  = false;
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
    if (!isInBounds(nr, nc)) {
        willMove[id] = false;
        nextRow[id] = nr;
        nextCol[id] = nc;
        nextDir[id] = d;
        return false;
    }

    char tile = grid[nr][nc];
    int nd = d;

    if (tile == '+') {
        nd = getSmartDirectionAtCrossing(d);
    } else {
        nd = getNextDirection(d, tile);
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
int getNextDirection(int dir, char tile)
{
    if (tile == '-' || tile == '|') return dir;

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

    // Switch handling could be added later (Day-6+)
    return dir;
}

// ----------------------------------------------------------------------------
// SMART ROUTING AT CROSSING - simple for now (can be improved Day-5+)
// ----------------------------------------------------------------------------
int getSmartDirectionAtCrossing(int dir)
{
    int straight = dir;
    int right = (dir + 1) % 4;
    int left  = (dir + 3) % 4;
    int back  = (dir + 2) % 4;
    int rr, rc;
    rr = nextRow[0]; 
    rr = trainRow[0]; rc = trainCol[0];
    rr = trainRow[0]; rc = trainCol[0]; 
    auto test_dir = [&](int base_r, int base_c, int cand_dir)->bool {
        int tr = base_r, tc = base_c;
        if (cand_dir == 0) tr--;
        else if (cand_dir == 1) tc++;
        else if (cand_dir == 2) tr++;
        else tc--;
        if (!isInBounds(tr, tc)) return false;
        return isTrackTile(grid[tr][tc]) || isSwitchTile(grid[tr][tc]) || grid[tr][tc] == 'D';
    };

    int base_r = trainRow[0]; 
    return straight;
}

// ----------------------------------------------------------------------------
// DETERMINE ALL ROUTES (PHASE 2)
// ----------------------------------------------------------------------------
// Fill next positions/directions for all trains.
void determineAllRoutes()
{
  
    for (int i = 0; i < trainCount; ++i) {
        willMove[i] = false;
        nextRow[i] = -999;
        nextCol[i] = -999;
        nextDir[i] = trainDir[i];
        crashed[i] = false;
    }
    for (int i = 0; i < trainCount; ++i) {
        if (trainActive[i]) determineNextPosition(i);
    }
}

// ----------------------------------------------------------------------------
// MOVE ALL TRAINS (PHASE 6 - commit moves)
// ----------------------------------------------------------------------------
void moveAllTrains()
{
    for (int i = 0; i < trainCount; ++i)
    {
        if (!trainActive[i]) continue;
        if (!willMove[i]) continue;

        int nr = nextRow[i];
        int nc = nextCol[i];
        int nd = nextDir[i];

        if (!isInBounds(nr, nc)) {
            trainActive[i] = false;
            crashed[i] = true;
            continue;
        }

        trainRow[i] = nr;
        trainCol[i] = nc;
        trainDir[i] = nd;
    }
}

// ----------------------------------------------------------------------------
// DETECT COLLISIONS WITH PRIORITY SYSTEM (basic version)
// ----------------------------------------------------------------------------
void detectCollisions()
{
    for (int i = 0; i < trainCount; ++i)
    {
        if (!trainActive[i]) continue;

        for (int j = i + 1; j < trainCount; ++j)
        {
            if (!trainActive[j]) continue;
            if (!willMove[i] || !willMove[j]) continue;

           
            if (nextRow[i] == nextRow[j] && nextCol[i] == nextCol[j])
            {
                willMove[i] = false;
                willMove[j] = false;
            }

           
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
void checkArrivals()
{
    for (int i = 0; i < trainCount; ++i)
    {
        if (!trainActive[i]) continue;

        int r = trainRow[i];
        int c = trainCol[i];

        if (isInBounds(r, c) && grid[r][c] == 'D')
        {
            trainActive[i] = false;
            crashed[i] = false;
            cout << "Train " << i << " arrived at destination!\n";
        }
    }
}

// ----------------------------------------------------------------------------
// Emergency halt stubs (Day-6+)
// ----------------------------------------------------------------------------
void applyEmergencyHalt() { }
void updateEmergencyHalt() { }

#include "switches.h"
#include "simulation_state.h"
#include "grid.h"
#include "io.h"
#include <cstdio>
#include <iostream>
using namespace std ; 
// ============================================================================
// SWITCHES.CPP - Switch management (global-style)
// ============================================================================

// Simple placeholder threshold for when to queue a flip.
// You can parse per-switch thresholds from .lvl later; K=3 is safe default.
static const int DEFAULT_SWITCH_FLIP_THRESHOLD = 3;

// ----------------------------------------------------------------------------
// UPDATE SWITCH COUNTERS
// ----------------------------------------------------------------------------
// Increment counters for trains currently on a switch tile.
// ----------------------------------------------------------------------------
void updateSwitchCounters()
{
    for (int i = 0; i < trainCount; ++i)
    {
        if (!trainActive[i]) continue;
        int r = trainRow[i];
        int c = trainCol[i];
        if (!isInBounds(r,c)) continue;
        char tile = grid[r][c];
        if (!isSwitchTile(tile)) continue;
        int index = getSwitchIndex(tile);
        if (index < 0 || index >= switchCount) continue;
        switchCounter[index]++;
        cout << "Switch " << i << " counter = " << switchCounter[i] << "\n";
    }
}

// ----------------------------------------------------------------------------
// QUEUE SWITCH FLIPS
// ----------------------------------------------------------------------------
// When a counter reaches threshold, queue it to flip after movement.
// ----------------------------------------------------------------------------
void queueSwitchFlips()
{
    for (int i = 0; i < switchCount; ++i)
    {
        int threshold = DEFAULT_SWITCH_FLIP_THRESHOLD;
        // if you later add per-switch thresholds, read them here
        if (switchCounter[i] >= threshold)
        {
            switchFlipQueued[i] = true;
            switchCounter[i] = 0; // reset counter when queued
        }
    }
}

// ----------------------------------------------------------------------------
// APPLY DEFERRED FLIPS
// ----------------------------------------------------------------------------
// Apply queued flips after movement (deferred).
// ----------------------------------------------------------------------------
void applyDeferredFlips()
{
    for (int i = 0; i < switchCount; i++)
    {
        if (!switchFlipQueued[i]) continue;

        switchFlipQueued[i] = false;
        switchState[i] = 1 - switchState[i];

        cout << "Switch " << i << " flipped to state " << switchState[i] << "\n";
    }
}


// ----------------------------------------------------------------------------
// UPDATE SIGNAL LIGHTS
// ----------------------------------------------------------------------------
void updateSignalLights()
{
    // stub — implement visual signal logic later
}

// ----------------------------------------------------------------------------
// TOGGLE SWITCH STATE (Manual)
// ----------------------------------------------------------------------------
void toggleSwitchState()
{
    // stub for UI/manual toggles later
}

// ----------------------------------------------------------------------------
// GET SWITCH STATE FOR DIRECTION
// ----------------------------------------------------------------------------
int getSwitchStateForDirection(int index)
{
    if (index < 0 || index >= switchCount) return 0;
    return switchState[index];
}

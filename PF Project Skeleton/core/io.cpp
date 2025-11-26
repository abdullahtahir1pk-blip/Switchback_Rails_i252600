#include "io.h"
#include "simulation_state.h"
#include "grid.h"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>

// ============================================================================
// IO.CPP - Level I/O and logging
// ============================================================================

// ----------------------------------------------------------------------------
// LOAD LEVEL FILE
// ----------------------------------------------------------------------------
// Load a .lvl file into global state.
// ----------------------------------------------------------------------------
bool loadLevelFile(const char* filename)
{
    std::ifstream in(filename);
    if (!in) return false;

    std::string token;

    while (in >> token)
    {
        if (token == "ROWS:") in >> rows;
        else if (token=="COLS:") in >> cols;
        else if (token=="MAP:")
        {
            std::string line;
            std::getline(in,line); // skip
            for (int r=0; r<rows; r++) {
                std::getline(in,line);
                for (int c=0; c<cols; c++)
                    grid[r][c] = line[c];
            }
        }
    }

    return true;
}
// ----------------------------------------------------------------------------
// INITIALIZE LOG FILES
// ----------------------------------------------------------------------------
// Create/clear CSV logs with headers.
// ----------------------------------------------------------------------------
void initializeLogFiles() {
}

// ----------------------------------------------------------------------------
// LOG TRAIN TRACE
// ----------------------------------------------------------------------------
// Append tick, train id, position, direction, state to trace.csv.
// ----------------------------------------------------------------------------
void logTrainTrace() {
}

// ----------------------------------------------------------------------------
// LOG SWITCH STATE
// ----------------------------------------------------------------------------
// Append tick, switch id/mode/state to switches.csv.
// ----------------------------------------------------------------------------
void logSwitchState() {
}

// ----------------------------------------------------------------------------
// LOG SIGNAL STATE
// ----------------------------------------------------------------------------
// Append tick, switch id, signal color to signals.csv.
// ----------------------------------------------------------------------------
void logSignalState() {
}

// ----------------------------------------------------------------------------
// WRITE FINAL METRICS
// ----------------------------------------------------------------------------
// Write summary metrics to metrics.txt.
// ----------------------------------------------------------------------------
void writeMetrics() {
}
void printGrid()
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            bool placed = false;

            for (int t = 0; t < trainCount; t++)
            {
                if (trainActive[t] && trainRow[t] == r && trainCol[t] == c)
                {
                    std::cout << 'T';
                    placed = true;
                    break;
                }
            }

            if (!placed)
                std::cout << grid[r][c];
        }
        std::cout << "\n";
    }
}

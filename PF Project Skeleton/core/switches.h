#ifndef SWITCHES_H
#define SWITCHES_H

// ============================================================================
// SWITCHES.H - Switch logic (global-style)
// ============================================================================

// Increment counters when trains enter switches.
void updateSwitchCounters();

// Queue flips when counters reach threshold.
void queueSwitchFlips();

// Apply queued deferred flips after movement.
void applyDeferredFlips();

// Update signal light colors (stub).
void updateSignalLights();

// Manually toggle a switch state (stub).
void toggleSwitchState();

// Get switch state helper (index -> state)
int getSwitchStateForDirection(int index);

#endif

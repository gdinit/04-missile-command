/* en_defines.h */
// ===================================80 chars=================================|

#ifndef EN_DEFINES_H
#define EN_DEFINES_H

#include "mc_game_defines.h"

// ============ BEGIN: HARDCODED ENGINE GENERIC SETTINGS ==============
//// RENAMED AND NEW
#define CONST_WIN_FULLSCREEN 0
#define CONST_DEBUG_ONLAUNCH_SHOW_OVERLAY 1
#define CONST_DEBUG_ONLAUNCH_PRINT_TO_CONSOLE 0
#define CONST_DEBUG_ONLAUNCH_PRINT_TO_CONSOLE_FPS 0
#define CONST_OBSERVED_FPS_REGISTRY_MAXSIZE 10
#define CONST_OBSERVED_FPS_ACTION_THRESHOLD 5
#define CONST_MIN_STATE_AGE_2OBSERVE_ADJUST_SECS_INT 5
#define CONST_MIN_STATE_AGE_2UPDATE_SECS_INT 1
// ============================
// #define CONST_SCREENRES_W 320
#define CONST_SCREENRES_W 640
#define CONST_SCALE 640.f
// #define CONST_SCREENRES_W 800
// #define CONST_SCREENRES_W 1024
// #define CONST_SCREENRES_W 1920
// ============ END: HARDCODED ENGINE GENERIC SETTINGS ==============

// ============ BEGIN: DECIDE FINAL SETTINGS ==============
// Game Name -- set it, only if game-define-file has not done so
#ifndef CONST_GAME_NAME
#define CONST_GAME_NAME "Untitled"
#endif

// FPS Int -- set it, only if game-define-file has not done so
#ifndef CONST_DESIRED_FPS_INT
#define CONST_DESIRED_FPS_INT 60
#endif

// FPS Float -- set it, only if game-define-file has not done so
#ifndef CONST_DESIRED_FPS_FLOAT
#define CONST_DESIRED_FPS_FLOAT 60.f
#endif
// ============ END: DECIDE FINAL SETTINGS ==============

// EN_DEFINES_H
#endif

// ===================================80 chars=================================|
/* EOF */


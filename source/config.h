/* config.h */
// ===================================80 chars==================================

// TODO This file is being included by too many!
// Try and reduce size of this to a few lines && reduce includers

// TODO Prefix sections as: EN_ (Engine), BR_ (Breakout)

#ifndef C_H
#define C_H

#include "essentials.h"
#include "globals.h"

// For window_title etc.
#include <string>

////////////////////////////////////////////////////////////////////////////////
////////////// BEGIN: NEED REVIEW //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// FPS
constexpr int32	C_DESIRED_FPS_INT { 30 };
constexpr float	C_DESIRED_FPS_FLOAT { 30.f };
constexpr int32	C_OBSFPS_CONTMAXSIZE { 10 };
constexpr int32	C_OBSFPS_ACTTHRESHOLD { 5 };
constexpr float	C_FPS_CATCHUP_STEP_F { 0.5f };
constexpr int32	C_DTYTHRESHOLD_SEC_INT { 5 };
constexpr int32	C_FPSO_MAGE_2U_SECS_INT { 1 };
// BORDER
constexpr float	C_BORDER_START_X { 0.f };
constexpr float	C_BORDER_START_Y { 20.f };
constexpr float	C_BORDER_THICKNESS { 12.f };
// PREGAME ANIMATION STUFF
constexpr float	C_PGA_SD { .50f };
#pragma float_control(precise, off)
// TODO fixme
constexpr float	C_PGA_POS_X { 99 / 2.f };
#pragma float_control(precise, on)
// TODO fixme
constexpr float	C_PGA_POS_Y { 99 * 0.38f };
// SCORE
constexpr float	C_SCORE_STEP { 1.f };
// ARENA
constexpr float	C_ARENA_WIDTH { 300.f };
constexpr float	C_ARENA_HEIGHT { 300.f };
constexpr float	C_ARENA_SPAWN_POS { -10000.f };
////////////////////////////////////////////////////////////////////////////////
////////////// END: NEED REVIEW ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//////////////// BEGIN: TODO LATER /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// MAIN MENU -- TODO switch to `dear imgui` and remove these hard coded values
constexpr float	C_MENU_BOX_WIDTH { 220.f };
constexpr float	C_MENU_BOX_HEIGHT { 40.f };
constexpr float	C_MENU_BUTTON_1 { .40f };
constexpr float	C_MENU_BUTTON_2 { .55f };
constexpr float	C_MENU_BUTTON_3 { .70f };

// LEVEL DETAILS - MOVE TO LEVEL01.TXT
// Always start counting from zero.
constexpr int32	CONFIG_FIRSTCELL = { 0 };
// We want this many cells in total
constexpr int32	CONFIG_LASTCELL = { 96 };
// Line break
constexpr int32	CONFIG_COLUMNS = { 16 };
////////////////////////////////////////////////////////////////////////////////
//////////////// END: TODO LATER ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// SOFT SETTINGS (INITIAL CONFIG ONLY) -- THEN USE FROM SETTINGS.JSON //////////
////////////////////////////////////////////////////////////////////////////////
// WINDOW
constexpr bool	C_WIN_FULLSCREEN { 0 };
constexpr int32	C_WIN_W = { 640 };
constexpr int32	C_WIN_H = { 480 };

// DEBUG STUFF
// NOT IN USE (Using CMake build type instead) constexpr bool	DEBUG { 1 };
// show in-game FPS/Stats overlay
constexpr bool	C_DEBUG_SHOW_OVERLAY { 0 };
// print extra messages in game console window
constexpr bool	C_D_CO { 0 };
// dynamic fps monitoring & adjustment => report to the console
constexpr bool	C_D_DFPS_CO { 0 };
////////////////////////////////////////////////////////////////////////////////
////////////////// END OF SOFT SETTINGS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// HARD SETTINGS (RESIDE IN BINARY) ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// WINDOW (hardcoded)
const std::string	C_WIN_TITLETEXT { "Breakout" };

// TODO: MOVE TO GAME  -- OBJECT SIZE RATIOS
constexpr double	CEXPR_TBXRATIO { 0.10 };
constexpr double	CEXPR_TBYRATIO { 0.15 };
constexpr double	CEXPR_TBWRATIO { 0.78 };
constexpr double	CEXPR_TBHRATIO { 0.06 };
constexpr double	CEXPR_LBXRATIO { 0.10 };
constexpr double	CEXPR_LBYRATIO { 0.15 };
constexpr double	CEXPR_LBWRATIO { 0.4347826086956522 };
constexpr double	CEXPR_LBHRATIO { 0.06 };
constexpr double	CEXPR_RBXRATIO { 0.10 };
constexpr double	CEXPR_RBYRATIO { 0.15 };
constexpr double	CEXPR_RBWRATIO { 0.4347826086956522 };
constexpr double	CEXPR_RBHRATIO { 0.06 };
constexpr double	CEXPR_VBWRATIO { 23.0 };
constexpr double	CEXPR_VBHRATIO { 1.347290640394089 };
constexpr float		CEXPR_BRHRATIO { 0.02564102564102564f };
constexpr float		CEXPR_BRPYRATIO { 0.3113553113553114f };
constexpr float		CEXPR_BRWRATIO { 0.0461f };
constexpr float		CEXPR_BRPXRATIO { 0.1293f };

// BALL
constexpr float		C_BALL_W { 7.f };
constexpr float		C_BALL_H { 7.f };
constexpr float		C_BALL_SPAWN_POS { -100.f };
constexpr float		C_BALL_SPEED { 0.72f };
// PADDLE
constexpr float		C_PADDLE_MOVSTEP { 7.4f };
constexpr float		C_PADDLE_W { 60.f };
constexpr float		C_PADDLE_H { 10.f };
constexpr int32		C_LIVES = { 5 };
////////////////////////////////////////////////////////////////////////////////
////////////////// END OF HARDCODED ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif	// C_H

// ===================================80 chars==================================
/* EOF */


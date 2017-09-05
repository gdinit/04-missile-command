/* en_defines.h */
// ===================================80 chars==================================

#ifndef EN_DEFINES_H
#define EN_DEFINES_H

// ============ BEGIN: HARDCODED ENGINE GENERIC SETTINGS ==============
#ifndef GA_GAME_DEFINES_H
//
// ============================
// RENAMED AND NEW
#define CONST_GAME_NAME	"Untitled Game"
#define CONST_DESIRED_FPS_INT 30
#define CONST_DESIRED_FPS_FLOAT	30.f
// ============================
//
// ============================
// STILL NEED TO BE RENAMED TO CONTS_BLAH_BLAH
// TODO RENAME TO CONST
#define C_WIN_W 320
#define C_WIN_H 240
#define CONST_WIN_FULLSCREEN 0
#define C_DEBUG_SHOW_OVERLAY 1
#define C_D_CO 0
#define C_D_DFPS_CO 0
// TODO MOVE TO GA_DEFINES
#define CONST_MENU_BOX_WIDTH 220.f
#define CONST_MENU_BOX_HEIGHT 40.f
#define CONST_MENU_BUTTON_1 .40f
#define CONST_MENU_BUTTON_2 .55f
#define CONST_MENU_BUTTON_3 .70f
// -------------- TODO switch these below back to constexpr
// constexpr float	CONST_MENU_BOX_WIDTH { 220.f };
// constexpr float	CONST_MENU_BOX_HEIGHT { 40.f };
// constexpr float	CONST_MENU_BUTTON_1 { .40f };
// constexpr float	CONST_MENU_BUTTON_2 { .55f };
// constexpr float	CONST_MENU_BUTTON_3 { .70f };
// --------------

#define CONST_DESIRED_FPS_INT 30
#define CONST_DESIRED_FPS_FLOAT 30.f
#define C_OBSFPS_CONTMAXSIZE 10
#define C_OBSFPS_ACTTHRESHOLD 5
#define C_FPS_CATCHUP_STEP_F 0.5f
#define C_DTYTHRESHOLD_SEC_INT 5
#define C_FPSO_MAGE_2U_SECS_INT 1

//// WINDOW (hardcoded)
// const std::string	C_WIN_TITLETEXT { "Missile Command" };
//// TODO remove this?
// constexpr int32		C_LIVES = { 5 };

//// FPS
// constexpr int32	CONST_DESIRED_FPS_INT { 30 };
// constexpr float	CONST_DESIRED_FPS_FLOAT { 30.f };
// constexpr int32	C_OBSFPS_CONTMAXSIZE { 10 };
// constexpr int32	C_OBSFPS_ACTTHRESHOLD { 5 };
// constexpr float	C_FPS_CATCHUP_STEP_F { 0.5f };
// constexpr int32	C_DTYTHRESHOLD_SEC_INT { 5 };
// constexpr int32	C_FPSO_MAGE_2U_SECS_INT { 1 };
// possibly outdated & unnceessary
// #define BR_BOUNCE_CHANCE_LOWN -0.24
// #define BR_BOUNCE_CHANCE_LOWP 0.24
// #define BR_BOUNCE_CHANCE_HIGHN -0.48
// #define BR_BOUNCE_CHANCE_HIGHP 0.48
#endif
// ============================
//
// ============ END: HARDCODED ENGINE GENERIC SETTINGS ==============

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#endif	// EN_DEFINES_H

// ===================================80 chars==================================
/* EOF */


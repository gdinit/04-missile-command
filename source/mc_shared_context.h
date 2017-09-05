/* mc_shared_context.h */
// ===================================80 chars==================================

// This struct stores some data and makes it accessible to all game states.
// It is instantiated in Application() & passed to each GameState as &ref.

#ifndef MC_SHARED_CONTEXT_H
#define MC_SHARED_CONTEXT_H

#include "en_arena.h"
#include "mc_hud.h"

struct SharedContext
{
	// Game
	bool gameIsPaused = false;
	bool mustMainMenu = false;
	bool moveUpReqActive = false;
	bool moveLeftReqActive = false;
	bool moveDownReqActive = false;
	bool moveRightReqActive = false;

	// Window
	// TODO: Change this
	// For now we only save a pointer & access it via a pointer.
	// Improve this code so we have no pointer here at all.
	sf::RenderWindow* pWindow = nullptr;
	sf::View view;

	// TODO convert to a struct?
	float m_resx = 0.f;
	float m_resy = 0.f;

	// bool windowHasFocus = false;

	// HUD Data
	int32 currentScore = -9999;
	int32 livesLeft = -9999;
	int32 gameLevel = -9999;

	// Sound Stuff
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;

	// Time Stuff
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;
};

#endif	// MC_SHARED_CONTEXT_H

// ===================================80 chars==================================
/* EOF */


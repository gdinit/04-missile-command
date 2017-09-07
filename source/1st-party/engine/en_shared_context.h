/* en_shared_context.h */
// ===================================80 chars==================================

// This struct stores some data and makes it accessible to all game states.
// It is instantiated in Application() & passed to each GameState as &ref.

#ifndef EN_SHARED_CONTEXT_H
#define EN_SHARED_CONTEXT_H

// #include "en_arena.h"
// TODO remove this #include "mc_hud.h"

struct EngineSharedContext
{
	// Window
	// TODO: Change this
	// For now we only save a pointer & access it via a pointer.
	// Improve this code so we have no pointer here at all.
	sf::RenderWindow* pWindow = nullptr;
	sf::View view;

	// Game Run State
	bool gameIsPaused = false;

	// Game
	bool mustMainMenu = false;
	bool moveUpReqActive = false;
	bool moveLeftReqActive = false;
	bool moveDownReqActive = false;
	bool moveRightReqActive = false;
	int32 currentScore = -9999;
	int32 livesLeft = -9999;
	int32 gameLevel = -9999;

	// Time Stuff
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;

	// Sound Stuff
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;
};

// EN_SHARED_CONTEXT_H
#endif

// ===================================80 chars==================================
/* EOF */


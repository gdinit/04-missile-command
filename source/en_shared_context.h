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

	// Time Stuff
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;

	// Sound Stuff
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;
};

#endif	// EN_SHARED_CONTEXT_H

// ===================================80 chars==================================
/* EOF */


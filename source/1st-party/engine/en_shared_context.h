/* en_shared_context.h */
// ===================================80 chars=================================|

// This struct stores some data and makes it accessible to all game states.
// It is instantiated in Application() & passed to each GameState as &ref.

#ifndef EN_SHARED_CONTEXT_H
#define EN_SHARED_CONTEXT_H

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
	unsigned long long int frameID = 0;

	// Time Stuff
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;

	// d += d1 Extend the duration d by the duration d1
	// std::chrono::duration simulationTime =
	// std::chrono::duration_values::zero;
	// std::chrono::duration accumulatedTime =
	// std::chrono::duration_values::zero;
	// auto accStart = std::chrono::system_clock::now();
	// auto accEnd = std::chrono::system_clock::now();
	// std::chrono::duration<double> diff = accEnd - accStart;

	// Sound Stuff
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;
};

// EN_SHARED_CONTEXT_H
#endif

// ===================================80 chars=================================|
/* EOF */


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
	// DIRECTIONS
	// 1 UP		Num8
	// 2 UPRIGHT	Num9
	// 3 RIGHT	Num6
	// 4 DOWNRIGHT	Num3
	// 5 DOWN	Num2
	// 6 DOWNLEFT	Num1
	// 7 LEFT	Num4
	// 8 LEFTUP	Num7
	bool moveReqActiveUp = false;
	bool moveReqActiveUpRight = false;
	bool moveReqActiveRight = false;
	bool moveReqActiveDownRight = false;
	bool moveReqActiveDown = false;
	bool moveReqActiveDownLeft = false;
	bool moveReqActiveLeft = false;
	bool moveReqActiveUpLeft = false;
	int32 currentScore = -9999;
	int32 livesLeft = -9999;
	int32 gameLevel = -9999;
	unsigned long long int frameID = 0;

	// Time
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;

	// Sound
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;
};

// EN_SHARED_CONTEXT_H
#endif

// ===================================80 chars=================================|
/* EOF */


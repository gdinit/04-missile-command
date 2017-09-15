/* en_globals.h */
// ===================================80 chars=================================|

#ifndef EN_GLOBALS_H
#define EN_GLOBALS_H

#include "en_essentials.h"

#include <string>

struct Settings {
	// App Window
	int32 CfgWindowResX, CfgWindowResY;
	bool inGameOverlay = false;
	bool debugPrintToConsole = false;
	bool debugPrintToConsoleFPS = false;
	int32 currentScreenSizeWidth = -9999;
	int32 currentScreenSizeHeight = -9999;
	float ballSpeed = -9999.f;
};

struct Globals {
	// TODO move these to sharedContext
	int32 currentScore = -9999;
	int32 livesLeft = -9999;
	int32 gameLevel = -9999;
	std::string gameHudText = "9999 to-be-updated-shortly 9999";
	std::string currentScoreText = "999";
	bool returnToMainMenuRequested = 0;
};

// EN_GLOBALS_H
#endif

// ===================================80 chars=================================|
/* EOF */


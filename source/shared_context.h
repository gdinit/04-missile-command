/* shared_context.h */
// ===================================80 chars==================================

// This struct stores some data and makes it accessible to all game states.
// It is instantiated in Application() & passed to each GameState as &ref.

// IDEAS
// sf::RenderWindow window = {{396, 400}, "One Room",
// sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings{0, 0,
// 8}};
// thor::ResourceHolder<sf::Texture, std::string> textures;
// thor::ResourceHolder<sf::Font, std::string> fonts;
// thor::ResourceHolder<sf::SoundBuffer, std::string> sounds;
// sf::Music track_one;
// thor::ActionMap<std::string> actionmap;
// std::shared_ptr<Screen> current_room = nullptr;
// const std::vector<int> lock_combination = {1, 0, 3};
// const std::vector<int> pin_combination = {3, 2, 7, 6};
// const std::string password = "NSA4u";
// bool key = false;
// bool combination = false;
// bool login = false;
// bool briefcase = false;
// bool win = false;

#ifndef SHARED_CONTEXT_H
#define SHARED_CONTEXT_H

#include "arena.h"
#include "hud.h"

struct SharedContext
{
	// Game
	bool gameIsPaused = false;
	bool mustMainMenu = false;
	bool moveLeftReqActive = false;
	bool moveRightReqActive = false;

	// Window
	// TODO: Change this
	// For now we only save a pointer & access it via a pointer.
	// Improve this code so we have no pointer here at all.
	sf::RenderWindow* pWindow = nullptr;
	sf::View view;

	float m_desktopResY = 0.f;
	// TODO convert to a struct?
	float m_resx = 0.f;
	float m_resy = 0.f;

	// bool windowHasFocus = false;

	// HUD Data
	int32 currentScore = -9999;
	int32 livesLeft = -9999;
	int32 gameLevel = -9999;

	// Animation Stuff
	bool preGameAnimationNeeded = true;
	bool preGameAnimationRunning = false;
	bool preGameAnimationStep1Needed = true;
	bool preGameAnimationStep2Needed = true;
	bool preGameAnimationStep3Needed = true;
	bool preGameAnimationStep4Needed = true;
	bool preGameAnimationStep1SFXNeeded = true;
	bool preGameAnimationStep2SFXNeeded = true;
	bool preGameAnimationStep3SFXNeeded = true;
	bool preGameAnimationStep4SFXNeeded = true;

	// Sound Stuff
	bool reqSndPlyFromPlay = 0;
	bool reqSndPlyFromPause = 0;

	// Time Stuff
	std::chrono::steady_clock::time_point tIntroFirstLaunchTime;
};

#endif	// SHARED_CONTEXT_H

// ===================================80 chars==================================
/* EOF */


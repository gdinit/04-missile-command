/* en_play_state.h */
// ===================================80 chars=================================|

#ifndef EN_PLAY_STATE_H
#define EN_PLAY_STATE_H

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
#include "en_main_menu_state.h"
#include "en_pause_state.h"
// Required for centerOrigin
#include "en_util_utility.h"
#include "en_util_make_unique.h"
// TODO remove this
#include "mc_game_objects.h"
#include "mc_arena.h"
// TODO remove this #include "mc_hud.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

// to in-line document
// Required for std::unique_ptr
#include <memory>
// Required for debugging -- TODO REMOVE THIS
#include <iostream>
// Required for capturing last windowResizeEvent
#include <chrono>
// Required for JSON
#include <fstream>

class StateMachine;

class PlayState : public State
{
public:
	PlayState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace = true );
	virtual ~PlayState();
	void	onResize();
	void	initializeState();
	void	processEvents();
	void	update();
	void	draw();
	void	pause();
	void	resume();
	// animation stuff
	void	restartPregameAnimationClock();
	void	drawPreGameAnimation();
	float	getPreGameAnimationAgeAsSeconds();
	void	tglGameDebug(void);

private:
	const t_objectName	m_myObjNameStr;
	Arena			arena;
	// TODO remove this Hud			hud;
	sf::Vector2f		m_res;

	// window resize stuff
	// Added to store texture size
	sf::Vector2u		m_textureSize;
	// Added to store window size
	sf::Vector2u		m_windowSize;
	// TODO move this to app
	float			m_desiredAspectRatio;

	// animation stuff
	sf::Clock		m_animationClock;
	sf::Time		m_animationAge;
	sf::Text		m_preGameAnimationStep1Text;
	sf::Text		m_preGameAnimationStep2Text;
	sf::Text		m_preGameAnimationStep3Text;
	sf::Text		m_preGameAnimationStep4Text;
	sf::SoundBuffer		m_sbBlip2;
	sf::Sound		m_sBlip2;
	Direction		m_moveDirection;
	sf::SoundBuffer		m_sbClicked;
	sf::Sound		m_sClicked;
	int32			m_systemResizeHourglass;
	// imgui stuff
	sf::CircleShape		m_shape;
	sf::Clock		deltaClock;
	int32			m_clicked;
};

// EN_PLAY_STATE_H
#endif

// ===================================80 chars=================================|
/* EOF */


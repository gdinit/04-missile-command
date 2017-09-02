/* play_state.h */
// ===================================80 chars==================================

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "essentials.h"
#include "state.h"
#include "state_machine.h"
#include "main_menu_state.h"
#include "pause_state.h"
#include "config.h"
// For centerOrigin
#include "utility.h"
#include "make_unique.h"
#include "game_objects.h"
#include "ball.h"
#include "arena.h"
#include "hud.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>

// to in-line document
// For std::unique_ptr
#include <memory>
// For debugging -- TODO REMOVE THIS
#include <iostream>
// For capturing last windowResizeEvent
#include <chrono>

class StateMachine;

class PlayState : public State
{
	public:
		PlayState( StateMachine &machine
		, sf::RenderWindow &window
		, SharedContext &context
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

	private:
		const t_objectName	m_myObjNameStr;
		Arena			arena;
		Hud			hud;
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
};

#endif	// PLAY_STATE_H

// ===================================80 chars==================================
/* EOF */


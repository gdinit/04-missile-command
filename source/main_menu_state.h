/* main_menu_state.h */
// ===================================80 chars==================================

#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "essentials.h"
#include "state.h"
#include "state_machine.h"
#include "config.h"
// For centerOrigin
#include "utility.h"
#include "play_state.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>

// for FPS text
#include <string>
// For round()
#include <cmath>

class StateMachine;

class MainMenuState : public State
{
	public:
		MainMenuState( StateMachine &machine
		, sf::RenderWindow &window
		, SharedContext &context
		, bool replace = true );
		virtual ~MainMenuState();
		// resize stuff here
		void	onResize();
		void	initializeState();
		void	processEvents();
		void	buttonCollisionDetectRespond( void ) noexcept;
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprPlay;
		bool			m_sprPlayNeedSFX;
		bool			m_sprPlayButtonHot;
		sf::Font		m_fontPlayText;
		sf::Text		m_textPlay;

		sf::Sprite		m_sprCredits;
		bool			m_sprCreditsNeedSFX;
		bool			m_sprCreditsButtonHot;
		sf::Font		m_fontCreditsText;
		sf::Text		m_textCredits;

		sf::Sprite		m_sprQuit;
		bool			m_sprQuitNeedSFX;
		bool			m_sprQuitButtonHot;
		sf::Font		m_fontQuitText;
		sf::Text		m_textQuit;

		sf::SoundBuffer		m_sbMouseOver;
		sf::Sound		m_sMouseOver;
		sf::Vector2i		m_mousePos;

		// window resize stuff
		// Added to store texture size
		sf::Texture		m_textureWhite;
		sf::Vector2u		m_textureSize;
		// Added to store window size
		sf::Vector2u		m_windowSize;
		// TODO move this to app
		float			m_desiredAspectRatio;
		int32			m_systemResizeHourglass;
};

#endif	// MAIN_MENU_STATE_H

// ===================================80 chars==================================
/* EOF */


/* pause_state.h */
// ===================================80 chars==================================

#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "essentials.h"
#include "state.h"
#include "state_machine.h"
#include "config.h"
#include "globals.h"
// For centerOrigin
#include "utility.h"
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

// for FPS text
#include <string>

class StateMachine;

// namespace sf
// {
// class RenderWindow;
// }

class PauseState : public State
{
	public:
		PauseState( StateMachine &machine
		, sf::RenderWindow &window
		, SharedContext &context
		, bool replace = true );
		virtual ~PauseState();
		// TODO remove resize stuff now that we're using letterBox?
		// resize stuff here
		void	onResize();
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		const t_objectName	m_myObjNameStr;
		sf::Font		m_fontPressToContinue;
		sf::Text		m_textPressToContinue;
		sf::Font		m_fontPressToContinueLine2;
		sf::Text		m_textPressToContinueLine2;

		// window resize stuff
		// Added to store texture size
		sf::Vector2u		m_textureSize;
		// Added to store window size
		// TODO remove resize stuff now that we're using letterBox?
		sf::Vector2u		m_windowSize;
		// TODO move this to app
		float			m_desiredAspectRatio;
		int32			m_systemResizeHourglass;

		sf::SoundBuffer		m_sbClicked;
		sf::Sound		m_sClicked;
};

#endif	// PAUSE_STATE_H

// ===================================80 chars==================================
/* EOF */


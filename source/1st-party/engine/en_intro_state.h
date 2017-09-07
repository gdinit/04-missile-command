/* en_intro_state.h */
// ===================================80 chars==================================

#ifndef EN_INTRO_STATE_H
#define EN_INTRO_STATE_H

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
#include "en_play_state.h"
// TODO remove this #include "mc_config.h"
// For centerOrigin
#include "en_utility.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

// Required for FPS text
#include <string>
// Required for round()
#include <cmath>
// Required for capturing First Launch Time
#include <chrono>

class StateMachine;

class IntroState : public State
{
	public:
		IntroState( StateMachine &machine
		, sf::RenderWindow &window
		, EngineSharedContext &context
		, bool replace = true );
		virtual ~IntroState();
		void	onResize();
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();

	private:
		const t_objectName	m_myObjNameStr;
		sf::Texture		m_bgTex;
		sf::Sprite		m_bg;
		sf::RectangleShape	m_fader;
		sf::Color		m_alpha;
		sf::Font		m_fontPressToContinue;
		sf::Text		m_textPressToContinue;

		// window resize stuff
		// Added to store texture size
		sf::Vector2u		m_textureSize;
		// Added to store window size
		sf::Vector2u		m_windowSize;
		// TODO move this to app
		float			m_desiredAspectRatio;
		int			m_systemResizeHourglass;
};

#endif	// EN_INTRO_STATE_H

// ===================================80 chars==================================
/* EOF */


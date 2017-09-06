/* main_menu_state.h */
// ===================================80 chars==================================

#ifndef EN_MAIN_MENU_STATE_H
#define EN_MAIN_MENU_STATE_H

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
// TODO remove this #include "mc_config.h"
// For centerOrigin
#include "en_utility.h"
#include "en_play_state.h"

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
#include <imgui.h>
#include <imgui-SFML.h>

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
		, EngineSharedContext &context
		, bool replace = true );
		virtual ~MainMenuState();
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
		// window resize stuff
		// Added to store texture size
		sf::Texture		m_textureWhite;
		sf::Vector2u		m_textureSize;
		// Added to store window size
		sf::Vector2u		m_windowSize;
		// TODO move this to app
		float			m_desiredAspectRatio;
		int32			m_systemResizeHourglass;
		// imgui stuff
		sf::CircleShape		m_shape;
		sf::Clock		deltaClock;
		int32			m_clicked;
};

#endif	// EN_MAIN_MENU_STATE_H

// ===================================80 chars==================================
/* EOF */


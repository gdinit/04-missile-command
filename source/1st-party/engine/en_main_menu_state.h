/* en_main_menu_state.h */
// ===================================80 chars=================================|

#ifndef EN_MAIN_MENU_STATE_H
#define EN_MAIN_MENU_STATE_H

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
// For centerOrigin
#include "en_util_utility.h"
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
		sf::Clock		deltaClock;
		int32			m_clicked;
		// TODO clean-up this. imgui image button tests.
		sf::Texture		m_tex1Play;
		sf::Texture		m_tex2Cred;
		sf::Texture		m_tex3Exit;
		sf::Sprite		m_spr1Play;
		sf::Sprite		m_spr2Cred;
		sf::Sprite		m_spr3Exit;
		sf::Sprite		m_iconstex;
		sf::Vector2f		m_position = { 0, 0 };
		sf::Vector2f		m_dimension = { 0, 0 };
		//
		float			m_btnPlayXPosRatio = 0;
		float			m_btnPlayYPosRatio = 0;
		float			m_btnPlayWidthRatio = 0;
		float			m_btnPlayHeightRatio = 0;
		//
		float			m_btnCredXPosRatio = 0;
		float			m_btnCredYPosRatio = 0;
		float			m_btnCredWidthRatio = 0;
		float			m_btnCredHeightRatio = 0;
		//
		float			m_btnExitXPosRatio = 0;
		float			m_btnExitYPosRatio = 0;
		float			m_btnExitWidthRatio = 0;
		float			m_btnExitHeightRatio = 0;

		sf::Color		m_bgColor;
		sf::Color		m_tintColor;
};

// EN_MAIN_MENU_STATE_H
#endif

// ===================================80 chars=================================|
/* EOF */


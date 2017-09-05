/* en_play_state.h */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE
// (BLACK BOX)  STATE.
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////
#ifndef EN_PLAY_STATE_H
#define EN_PLAY_STATE_H
#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
#include "en_main_menu_state.h"
#include "en_pause_state.h"
#include "en_utility.h"
#include "en_make_unique.h"
#include "en_arena.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <chrono>
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
		void	restartPregameAnimationClock();
		void	drawPreGameAnimation();
		float	getPreGameAnimationAgeAsSeconds();

	private:
		const t_objectName	m_myObjNameStr;
		sf::Vector2f		m_res;
		sf::Vector2u		m_textureSize;
		sf::Vector2u		m_windowSize;
		float			m_desiredAspectRatio;
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

#endif	// EN_PLAY_STATE_H

// ===================================80 chars==================================
/* EOF */


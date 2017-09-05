/* en_pause_state.h */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE
// (BLACK BOX)  STATE.
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////

#ifndef EN_PAUSE_STATE_H
#define EN_PAUSE_STATE_H

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
#include "en_utility.h"
#include "en_arena.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <string>
class StateMachine;
class PauseState : public State
{
	public:
		PauseState( StateMachine &machine
		, sf::RenderWindow &window
		, EngineSharedContext &context
		, bool replace = true );
		virtual ~PauseState();
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
		sf::Vector2u		m_textureSize;
		sf::Vector2u		m_windowSize;
		float			m_desiredAspectRatio;
		int32			m_systemResizeHourglass;
		sf::SoundBuffer		m_sbClicked;
		sf::Sound		m_sClicked;
};

#endif	// EN_PAUSE_STATE_H

// ===================================80 chars==================================
/* EOF */


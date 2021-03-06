/* en_state.h */
// ===================================80 chars=================================|

#ifndef EN_STATE_H
#define EN_STATE_H

#include "en_defines.h"
#include "en_essentials.h"
#include "en_shared_context.h"
//// make configuration values to all derived classes
//// forward declare Settings struct
#include "en_globals.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
// For view
#include <SFML/System/Vector2.hpp>

// For consoleDebugOut cout
#include <iostream>
// For unique_ptr
#include <memory>
// container to store observedFPS last N values
#include <deque>
// For round()
#include <cmath>

// TODO remove this
extern std::unique_ptr <Settings> SETTINGS;

sf::View getLetterboxView( sf::View view, int windowWidth, int windowHeight );

class StateMachine;

class State
{
public:
	State( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace = true );

	virtual ~State() = default;

	State( const State & ) = delete;

	State & operator	=( const State & ) = delete;
	std::unique_ptr <State> next();
	virtual void		update() = 0;
	virtual void		draw() = 0;
	virtual void		pause() = 0;
	virtual void		resume() = 0;
	bool			isReplacing();
	void			tglDbgShowOverlay();
	void			toggleDebugConsoleOutput();
	void			tglDbgDFPSConsOutput();
	void			updateDebugOverlayTextIfEnabled( bool b );
	void			updateDebugOverlayTextIfEnabled();
	void			printConsoleDebugIfEnabled();
	void			recordObservedFPS();
	void			dynamicallyAdjustFPSLimit();
	unsigned short int	calcMedianFPS(
	std::deque <unsigned short int> records );
	void			restartStateClock();
	int			getStateAgeAsSeconds();

protected:
	std::unique_ptr <State>		m_next;
	StateMachine &			m_machine;
	sf::RenderWindow &		m_window;
	EngineSharedContext &		m_engineSharedContext;
	bool				m_replacing;
	static const sf::Time		TimePerFrame;
	int				m_statisticsNumFrames = 0;
	sf::Time			m_timeSinceLastUpdate;
	sf::Time			m_elapsedTime;
	sf::Clock			m_clock;
	sf::Clock			m_stateBirthdate;
	// TODO looks like we're not using this?
	sf::Time			m_stateAge;
	sf::Font			m_font;
	sf::Text			m_statisticsText;
	sf::Time			m_statisticsUpdateTime;
	unsigned short int		m_urgentUpdateNeeded = 0;
	std::deque <unsigned short int>	m_observedFPSLastN;
	short int			m_FPSAdjPosDelta = 0;
	short int			m_FPSAdjNegDelta = 0;
	unsigned short int		m_activeFPSLimit = CONST_FPS_INT;
	bool				m_justResumed = false;
	// Needed to center stuff
	sf::View			m_worldView;
};

// EN_STATE_H
#endif

// ===================================80 chars=================================|
/* EOF */


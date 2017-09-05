/* en_pause_state.cc */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE
// (BLACK BOX)  STATE.
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////

#include "en_pause_state.h"

PauseState::PauseState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }, m_myObjNameStr(
		"PauseState" )
{
	m_engineSharedContext.gameIsPaused = true;
	initializeState();
}

PauseState::~PauseState()
{
	m_engineSharedContext.gameIsPaused = false;
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed state:\t" << m_myObjNameStr << "\n";
	#endif
}

void PauseState::onResize()
{
}

void PauseState::initializeState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated state:\t\t" << m_myObjNameStr << "\n";
	#endif
	restartStateClock();
	m_systemResizeHourglass = 0;
	m_desiredAspectRatio = 640.f / 480.f;
	m_urgentUpdateNeeded = 10;
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );
	m_fontPressToContinue.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinue.setFont( m_fontPressToContinue );
	m_textPressToContinue.setCharacterSize( 48u );
	m_textPressToContinue.setFillColor( sf::Color::White );
	m_textPressToContinue.setString( "GAME PAUSED" );
	centerOrigin( m_textPressToContinue );
	m_textPressToContinue.setPosition(
		( m_engineSharedContext.view.getSize().x / 2 )
		, ( m_engineSharedContext.view.getSize().y / 2 ) );
	m_fontPressToContinueLine2.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinueLine2.setFont( m_fontPressToContinue );
	m_textPressToContinueLine2.setCharacterSize( 15u );
	m_textPressToContinueLine2.setFillColor( sf::Color::White );
	m_textPressToContinueLine2.setString(
		"\nPress ESC, PauseBreak, or P to continue" );
	centerOrigin( m_textPressToContinueLine2 );
	m_textPressToContinueLine2.setPosition(
		( m_engineSharedContext.view.getSize().x / 2 )
		, ( ( m_engineSharedContext.view.getSize().y / 2 ) + 50 ) );
	if ( !m_sbClicked.loadFromFile(
		     "assets/sounds/button_clicked2.wav" ) ) {
	}
	m_sClicked.setBuffer( m_sbClicked );
	if ( m_engineSharedContext.reqSndPlyFromPause ) {
		m_engineSharedContext.reqSndPlyFromPause = 0;
		m_sClicked.play();
	}
}

void PauseState::pause()
{
}

void PauseState::resume()
{
	restartStateClock();
}

void PauseState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;
	if ( m_systemResizeHourglass > 0 ) {
		--m_systemResizeHourglass;
	} else {
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		if ( m_urgentUpdateNeeded > 0 ) {
			--m_urgentUpdateNeeded;
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();
			m_urgentUpdateNeeded = false;
		}
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				break;
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}
	}
}

void PauseState::processEvents()
{
	sf::Event evt;

	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				m_machine.quit();
				break;
			case sf::Event::Resized:
				m_engineSharedContext.view = getLetterboxView(
						m_engineSharedContext.view
						, evt.size.width
						, evt.size.height );
				break;
			case sf::Event::KeyPressed:
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						m_engineSharedContext.
						reqSndPlyFromPlay = 1;
						m_machine.lastState();
						break;
					case sf::Keyboard::Q:
						m_machine.quit();
						break;
					case sf::Keyboard::F2:
						this->tglDbgShowOverlay();
						break;
					case sf::Keyboard::F3:
						this->toggleDebugConsoleOutput();
						break;
					case sf::Keyboard::F4:
						this->
						tglDbgDFPSConsOutput();
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
}

void PauseState::draw()
{
	m_window.display();
}

// ===================================80 chars==================================
/* EOF */


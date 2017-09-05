/* main_menu_state.cc */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE 
// (BLACK BOX)  STATE. 
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////

#include "en_main_menu_state.h"

MainMenuState::MainMenuState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }, m_myObjNameStr(
		"MainMenuState" )
{
	initializeState();
}

MainMenuState::~MainMenuState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed state:\t" << m_myObjNameStr << "\n";
	#endif
}

void MainMenuState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

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
	this->buttonCollisionDetectRespond();
}

void MainMenuState::draw()
{
	m_window.clear();
	m_window.display();
}

void MainMenuState::initializeState()
{
}

void MainMenuState::onResize()
{
}

void MainMenuState::pause()
{
}

void MainMenuState::resume()
{
	restartStateClock();
}

void MainMenuState::buttonCollisionDetectRespond( void ) noexcept
{
}

void MainMenuState::processEvents()
{
	sf::Event evt;
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				std::cout << "Quitting on close event."
				" Goodbye!\n";
				m_machine.quit();
			case sf::Event::KeyPressed:
				switch ( evt.key.code ) {
					case sf::Keyboard::Space:
						m_next = StateMachine::build
							<PlayState> ( m_machine
								, m_window
								,
								m_engineSharedContext
								, true );
						break;
					case sf::Keyboard::F2:
						this->tglDbgShowOverlay();
						break;
					case sf::Keyboard::F3:
						this->
						toggleDebugConsoleOutput();
						break;
					case sf::Keyboard::F4:
						this->
						tglDbgDFPSConsOutput();
						break;
					case sf::Keyboard::Q:
						std::cout <<
						"Quitting on Q key press."
						" Goodbye!\n";
						m_machine.quit();
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

// ===================================80 chars==================================
/* EOF */


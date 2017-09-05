/* en_play_state.cc */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE
// (BLACK BOX)  STATE.
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////
#include "en_play_state.h"
PlayState::PlayState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }
	, m_myObjNameStr( "PlayState" )
{
}

PlayState::~PlayState()
{
}

void PlayState::initializeState()
{
}

void PlayState::update()
{
	processEvents();
}

void PlayState::draw()
{
	m_window.clear();
	m_window.display();
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::processEvents()
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
					case sf::Keyboard::Q:
						std::cout << "Quitting on Q key"
						" press. Goodbye!\n";
						m_machine.quit();
						break;
					default:
						break;
				}
				break;
				break;
			default:
				break;
		}
	}
}

void PlayState::onResize()
{
}

// ===================================80 chars==================================
/* EOF */


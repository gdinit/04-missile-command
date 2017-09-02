/* state_machine.cc */
// ===================================80 chars==================================

#include "state_machine.h"

StateMachine::StateMachine()
	: m_resume{ false }
	, m_running{ false }
{
}

void StateMachine::run( std::unique_ptr <State> state )
{
	m_running = true;
	m_states.push_back( std::move( state ) );
}

void StateMachine::nextState()
{
	if ( m_resume ) {
		// Cleanup the current state
		if ( !m_states.empty() ) {
			m_states.pop_back();
		}

		// Resume previous state
		if ( !m_states.empty() ) {
			m_states.back()->resume();
		}

		m_resume = false;
	}

	// There needs to be a state
	if ( !m_states.empty() ) {
		std::unique_ptr <State> temp = m_states.back()->next();

		// Only change states if there's a next one existing
		if ( temp != nullptr ) {
			// Replace the running state
			if ( temp->isReplacing() ) {
				m_states.pop_back();
			}
			// Pause the running state
			else {
				m_states.back()->pause();
			}

			m_states.push_back( std::move( temp ) );
		}
	}
}

void StateMachine::lastState()
{
	m_resume = true;
}

void StateMachine::drawPrevious()
{
	// in PauseState, let's draw PlayState instantiated objects
	if ( m_states.size() == 2 ) {
		// m_states.at(m_states.size() - 1)->draw();
		m_states.at( 0 )->draw();
	}
}

void StateMachine::update()
{
	// Let the state update the game
	m_states.back()->update();
}

void StateMachine::draw()
{
	// Let the state draw the screen
	m_states.back()->draw();
}

// ===================================80 chars==================================
/* EOF */


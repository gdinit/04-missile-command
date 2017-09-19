/* en_state_machine.h */
// ===================================80 chars=================================|

#ifndef EN_STATE_MACHINE_H
#define EN_STATE_MACHINE_H

#include "en_essentials.h"
#include "en_state.h"

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// For unique_ptr
#include <memory>
// TODO: why is this here?
#include <string>

class State;

class StateMachine
{
public:
	StateMachine();

	void				run(
	std::unique_ptr <State> state );

	void				nextState();
	void				lastState();
	void				drawPrevious();

	void				update();
	void				draw();

	bool running() { return m_running; }

	void quit() { m_running = false; }

	template<typename T>
	static std::unique_ptr <T>	build( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace = true );

private:
	// The stack of states
	// std::stack <std::unique_ptr <State> >	m_states;
	// The vector of states
	std::vector <std::unique_ptr <State> >	m_states;

	bool					m_resume;
	bool					m_running;
};

template<typename T>
std::unique_ptr <T> StateMachine::build( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
{
	return std::unique_ptr <T> ( new T( machine
			, window
			, context
			, replace ) );
}

// EN_STATE_MACHINE_H
#endif

// ===================================80 chars=================================|
/* EOF */


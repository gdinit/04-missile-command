/* en_state.cc */
// ===================================80 chars=================================|

#include "en_state.h"

const sf::Time State::TimePerFrame =
	sf::seconds( 1.f / CONST_DESIRED_FPS_FLOAT );

State::State( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: m_machine{ machine }
	, m_window{ window }
	, m_engineSharedContext{ context }
	, m_replacing{ replace }
{
}

std::unique_ptr <State> State::next()
{
	return std::move( m_next );
}

bool State::isReplacing()
{
	return m_replacing;
}

void State::tglDbgShowOverlay()
{
	if ( SETTINGS->inGameOverlay == true ) {
		SETTINGS->inGameOverlay = false;
		// destroy the text
		m_statisticsText.setString( "" );
	} else if ( SETTINGS->inGameOverlay == false ) {
		SETTINGS->inGameOverlay = true;
		// immediately ugenerate some values
		// give me stats in the first frame,
		// but first make up some plausible values
		updateDebugOverlayTextIfEnabled( true );
	}
	std::cout << "DebugOverlay\t[" << SETTINGS->inGameOverlay << "]\n";
}

void State::toggleDebugConsoleOutput()
{
	SETTINGS->debugPrintToConsole = !SETTINGS->debugPrintToConsole;
	std::cout << "\nConsole debug\t[" << SETTINGS->debugPrintToConsole <<
	"]\n";
}

void State::tglDbgDFPSConsOutput()
{
	SETTINGS->debugPrintToConsoleFPS = !SETTINGS->debugPrintToConsoleFPS;
	std::cout << "debugPrintToConsoleFPS\t[" <<
	SETTINGS->debugPrintToConsoleFPS << "]\n";
}

void State::updateDebugOverlayTextIfEnabled( bool b )
{
	// we should not update for `too young` states
	// or it will print values like 13084738473 FPS!
	if ( SETTINGS->inGameOverlay ) {
		if ( b ) {
			// fabricate the initial values TODO <-- fix this
			int short	n = CONST_DESIRED_FPS_INT;
			int long	mil = 1000000;
			m_statisticsText.setString(
				// FPS
				"FPS: "	+ std::to_string( n )
				// FrameTime
				+ "\nFrameTime: " + std::to_string( mil / n )
				// FrameID
				+ " us\nFID: " + std::to_string(
					m_engineSharedContext.frameID
					)
				// RunTime
				+ "\nRunTime: " + std::to_string(
					std::chrono::duration_cast
					<std::chrono::seconds> ( (
							std::chrono::
							steady_clock::time_point
								( std::chrono::
								steady_clock::
								now() ) ) -
						m_engineSharedContext.
						tIntroFirstLaunchTime )
					.count() ) + " s\n"
				// Close
				);
		} else {
			updateDebugOverlayTextIfEnabled();
		}
	}
}

// update the overlay text
void State::updateDebugOverlayTextIfEnabled()
{
	if ( SETTINGS->inGameOverlay
	     && ( getStateAgeAsSeconds()
		  >= CONST_MIN_STATE_AGE_2UPDATE_SECS_INT ) ) {
		m_statisticsText.setString(
			// FPS
			"FPS: " + std::to_string(
				m_statisticsNumFrames )
			// FrameTime
			+ "\nFrameTime: " + std::to_string(
				m_statisticsUpdateTime.
				asMicroseconds() / m_statisticsNumFrames )
			// FrameID
			+ " us\nFID: " + std::to_string(
				m_engineSharedContext.frameID )
			// RunTime
			+ "\nRunTime: " + std::to_string(
				std::chrono::duration_cast <std::chrono::
					seconds> (
					( std::chrono::steady_clock::time_point(
						  std::chrono::steady_clock::
						  now() ) ) -
					m_engineSharedContext.
					tIntroFirstLaunchTime ).
				count() ) + " s\n"
			// Close
			);
	}
}

void State::printConsoleDebugIfEnabled()
{
	if ( SETTINGS->debugPrintToConsole ) {
		std::cout << "\nFPS: " + std::to_string(
			m_statisticsNumFrames ) + "\t" + "Time/Update: " +
		std::	to_string(
			m_statisticsUpdateTime.asMicroseconds() /
			m_statisticsNumFrames ) + "us\t" + "updateTime: " +
		std::	to_string(
			m_statisticsUpdateTime.asMicroseconds() ) + "us\n";
	}
}

void State::recordObservedFPS()
{
	if ( getStateAgeAsSeconds()
	     < CONST_MIN_STATE_AGE_2OBSERVE_ADJUST_SECS_INT ) {
	} else {
		// add the observed fps to the end of the queue
		m_observedFPSLastN.push_back( m_statisticsNumFrames );
		// prevent overgrowth
		while ( m_observedFPSLastN.size() >
			CONST_OBSERVED_FPS_REGISTRY_MAXSIZE ) {
			m_observedFPSLastN.pop_front();
		}
		// print all values
		if ( SETTINGS->debugPrintToConsoleFPS ) {
			std::cout << "\n<m_observedFPSLastN>: ";
			std::deque <unsigned short int>::iterator it =
				m_observedFPSLastN.begin();
			while ( it != m_observedFPSLastN.end() ) {
				std::cout << ' ' << *it++;
			}
		}
	}
}

void State::dynamicallyAdjustFPSLimit()
{
	if ( getStateAgeAsSeconds()
	     < CONST_MIN_STATE_AGE_2OBSERVE_ADJUST_SECS_INT ) {
	} else {
		// act if there are at least N values in our de-queue
		if ( m_observedFPSLastN.size() >=
		     CONST_OBSERVED_FPS_ACTION_THRESHOLD ) {
			// get median
			unsigned short int median = calcMedianFPS(
					m_observedFPSLastN );

			// modify the running FPS limit
			if ( median < CONST_DESIRED_FPS_INT ) {
				// our FPS is too low!
				unsigned short int delta =
					CONST_DESIRED_FPS_INT - median;
				// set frameLimit to the delta corrected new
				// value -- for large values go slow
				if ( delta > 10 ) {
					m_activeFPSLimit = m_activeFPSLimit +
						10;
					// action only if delta is more than 1
				} else if ( delta < 10 && delta > 1 ) {
					m_activeFPSLimit += delta;
				} else if ( delta == 1 ) {
					// do nothing = allow 1 FPS delta.
					// trying to fix 1 FPS delta causes more
					// harm than good (i.e.: 2 fps or more
					// fps delta!)
					if ( SETTINGS->debugPrintToConsoleFPS )
					{
						std::cout <<
						"\t(Delta=1)\tFPSLimit INTACT."
						"\tMedian: " << median << "\t";
					}
				}
				// apply the new frame limit
				m_window.setFramerateLimit( m_activeFPSLimit );
				if ( SETTINGS->debugPrintToConsoleFPS ) {
					std::cout <<
					"\tFPSLimit INCREASED to: " <<
					m_activeFPSLimit << "\tDelta is: " <<
					delta << "\tMedian: " << median << "\t";
				}
				// wipe the container
				m_observedFPSLastN.clear();
			} else if ( median > CONST_DESIRED_FPS_INT ) {
				// our FPS is too high!
				unsigned short int delta = median -
					CONST_DESIRED_FPS_INT;
				// set frameLimit to the delta corrected new
				// value -- for large values go slow
				if ( delta > 10 ) {
					m_activeFPSLimit = m_activeFPSLimit -
						10;
					// action only if delta is more than 1.
					// trying to fix 1 FPS delta causes more
					// harm than good (i.e.: 2 fps or more
					// fps delta!)
				} else if ( delta < 10 && delta > 1 ) {
					m_activeFPSLimit -= delta;
				} else if ( delta == 1 ) {
					// do nothing = allow 1 FPS delta.
					// trying to fix 1 FPS delta causes more
					// harm than good (i.e.: 2 fps or more
					// fps delta!)
					if ( SETTINGS->debugPrintToConsoleFPS )
					{
						std::cout <<
						"\t(Delta=1)\tFPSLimit INTACT."
						"\tMedian: " << median << "\t";
					}
				}
				if ( delta != 1 ) {
					// apply the new frame limit
					m_window.setFramerateLimit(
						m_activeFPSLimit );
					if ( SETTINGS->debugPrintToConsoleFPS )
					{
						std::cout <<
						"\tFPSLimit REDUCED to: " <<
						m_activeFPSLimit <<
						"\tDelta is: " << delta <<
						"\tMedian: " <<	median << "\t";
					}
					// wipe the container
					m_observedFPSLastN.clear();
				}
			} else if ( median == CONST_DESIRED_FPS_INT ) {
				if ( SETTINGS->debugPrintToConsoleFPS ) {
					std::cout <<
					"\t(median==desired)\tFPSLimit INTACT."
					"\tMedian: " << median << "\t";
				}
			}
		}
	}
}

unsigned short int State::calcMedianFPS( std::deque <unsigned short
		int> records )
{
	int	median;

	size_t	size = records.size();
	sort( records.begin(), records.end() );
	if ( size % 2 == 0 ) {
		median = ( records [ size / 2 - 1 ] + records [ size / 2 ] ) /
			2;
	} else {
		median = records [ size / 2 ];
	}

	return median;
}

void State::restartStateClock()
{
	m_stateBirthdate.restart();

	// reset the birth date 2nd time to (almost) zero out the state age.
	// used for dynFPSadj
	//
	// TODO looks like we're not using this??
	m_stateAge = m_stateBirthdate.restart();
}

int State::getStateAgeAsSeconds()
{
	sf::Time		tmp = sf::Time::Zero;

	tmp = m_stateBirthdate.getElapsedTime();

	signed short int	n = std::round( tmp.asSeconds() );

	return n;
}

// ===================================80 chars=================================|
/* EOF */


/* en_play_state.cc */
// ===================================80 chars=================================|

#include "en_play_state.h"

// TODO delete these?
extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;

PlayState::PlayState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }
	, m_myObjNameStr( "PlayState" )
{
	// Reset to prevent instant-game-over next time
	GLOBALS->returnToMainMenuRequested = 0;
	initializeState();
}

PlayState::~PlayState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed state:\t" << m_myObjNameStr << "\n";
	#endif

	// TODO remove me
	#if defined DBG
	std::cout << "This session of PlayState runTime: " <<
	getStateAgeAsSeconds() << std::endl;
	#endif
}

void PlayState::initializeState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated state:\t\t" << m_myObjNameStr << "\n";
	std::cout << "[DEBUG]\tCreating New Level:\tLevel " <<
	m_engineSharedContext.gameLevel << "\n";
	#endif

	restartStateClock();
	m_systemResizeHourglass = 0;
	m_engineSharedContext.moveReqActiveUp = 0;
	m_engineSharedContext.moveReqActiveUpRight = 0;
	m_engineSharedContext.moveReqActiveRight = 0;
	m_engineSharedContext.moveReqActiveDownRight = 0;
	m_engineSharedContext.moveReqActiveDown = 0;
	m_engineSharedContext.moveReqActiveDownLeft = 0;
	m_engineSharedContext.moveReqActiveLeft = 0;
	m_engineSharedContext.moveReqActiveUpLeft = 0;

	// TODO base these values on config variables
	m_desiredAspectRatio = 640.f / 480.f;
	#if defined DBG
	std::cout << "[DEBUG]\tm_desiredAspectRatio is: \t" <<
	m_desiredAspectRatio << " //" << m_myObjNameStr << "\n";
	#endif

	m_justResumed = false;
	// need this? m_worldView = m_window.getDefaultView();
	m_urgentUpdateNeeded = 10;

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	// SOUNDS
	// TODO place this in a function
	if ( !m_sbClicked.loadFromFile(
		     "assets/sounds/button_clicked2.wav" ) ) {
	}
	m_sClicked.setBuffer( m_sbClicked );

	// if there is a pending play sound request, play it
	if ( m_engineSharedContext.reqSndPlyFromPlay ) {
		m_engineSharedContext.reqSndPlyFromPlay = 0;
		m_sClicked.play();
	}

	if ( !m_sbBlip2.loadFromFile( "assets/sounds/blip1.wav" ) ) {
	}
	m_sBlip2.setBuffer( m_sbBlip2 );

	// START A NEW GAME
	m_windowSize = m_window.getSize();
	m_res.x = static_cast <float> ( m_windowSize.x );
	m_res.y = static_cast <float> ( m_windowSize.y );

	// signal arena to set up a new round
	// only level 1 is implemented so far
	m_engineSharedContext.gameLevel = 1;
	arena.newRound( m_res, m_engineSharedContext.gameLevel );

	// TODO fix me
	// hud.newRound( m_res );

	// TODO delete this?	GLOBALS->arenaNewRoundRequested = true;

	m_engineSharedContext.currentScore = 0;
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Reset score." << m_myObjNameStr << "\n";
	#endif
	m_engineSharedContext.livesLeft = 0;
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Reset lives." << m_myObjNameStr << "\n";
	#endif

	////////////////////////////////////////
	// SFML::ImGui Tests
	deltaClock.restart();
	ImGui::SFML::Init( m_window );
	m_clicked = 0;
	// SFML::ImGui Tests
	m_shape.setFillColor( sf::Color::Green );
	m_shape.setRadius( 5 );
	m_shape.setOutlineColor( sf::Color::Red );
	m_shape.setOutlineThickness( 1 );
	m_shape.setPosition( 10, 80 );
	////////////////////////////////////////
}

void PlayState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	if ( m_systemResizeHourglass > 0 ) {
		--m_systemResizeHourglass;
	} else {
	}

	// if returning from pause(), let's jump in time to prevent
	// slow catchup process
	if ( m_justResumed ) {
		m_timeSinceLastUpdate = TimePerFrame;
	}

	if ( GLOBALS->returnToMainMenuRequested == 1 ) {
		// Game over! Terminate
		#if defined DBG
		std::cout << "Terminating due to returnToMainMenuRequested=1\n";
		#endif
		m_next = StateMachine::build <MainMenuState>
				( m_machine, m_window, m_engineSharedContext
				, true );
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();
		// obtain current screen res - need to pass it to game objects
		m_res = static_cast <sf::Vector2f>
			( m_window.getSize() );
		// TODO update for Missile Command -- add 8 directions?
		// obtain requested moveDirection - need to pass it to paddle
		//
		// UP
		if ( m_engineSharedContext.moveReqActiveUp
			//
			// && !m_engineSharedContext.moveReqActiveUp
		     && !m_engineSharedContext.moveReqActiveUpRight
		     && !m_engineSharedContext.moveReqActiveRight
		     && !m_engineSharedContext.moveReqActiveDownRight
		     && !m_engineSharedContext.moveReqActiveDown
		     && !m_engineSharedContext.moveReqActiveDownLeft
		     && !m_engineSharedContext.moveReqActiveLeft
		     && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::UP;
			// UP RIGHT
		} else if ( m_engineSharedContext.moveReqActiveUpRight
				//
			    && !m_engineSharedContext.moveReqActiveUp
				// &&
				// !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::UPRIGHT;
			// RIGHT
		} else if ( m_engineSharedContext.moveReqActiveRight
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
				// && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::RIGHT;
			// DOWN RIGHT
		} else if ( m_engineSharedContext.moveReqActiveDownRight
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
				// &&
				// !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::DOWNRIGHT;
			// DOWN
		} else if ( m_engineSharedContext.moveReqActiveDown
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
				// && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::DOWN;
			// DOWN LEFT
		} else if ( m_engineSharedContext.moveReqActiveDownLeft
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
				// &&
				// !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::DOWNLEFT;
			// LEFT
		} else if ( m_engineSharedContext.moveReqActiveLeft
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
				// && !m_engineSharedContext.moveReqActiveLeft
			    && !m_engineSharedContext.moveReqActiveUpLeft ) {
			m_moveDirection = Direction::LEFT;
			// UP LEFT
		} else if ( m_engineSharedContext.moveReqActiveUpLeft
				//
			    && !m_engineSharedContext.moveReqActiveUp
			    && !m_engineSharedContext.moveReqActiveUpRight
			    && !m_engineSharedContext.moveReqActiveRight
			    && !m_engineSharedContext.moveReqActiveDownRight
			    && !m_engineSharedContext.moveReqActiveDown
			    && !m_engineSharedContext.moveReqActiveDownLeft
			    && !m_engineSharedContext.moveReqActiveLeft
				// && !m_engineSharedContext.moveReqActiveUpLeft
			    ) {
			m_moveDirection = Direction::UPLEFT;
		} else {
			m_moveDirection = Direction::NONE;
		}
		arena.update( m_elapsedTime, m_res, m_moveDirection );
		// why update HUD separately? process it with arena?
		// TODO fix me
		// hud.update( m_elapsedTime );
		if ( m_engineSharedContext.mustMainMenu == true ) {
			// TODO rename to allLivesLost. 'go to main menu
			// immediately (dead)'
			m_next = StateMachine::build <MainMenuState> (
					m_machine, m_window
					, m_engineSharedContext
					, true );
		}
		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		if ( m_urgentUpdateNeeded > 0 ) {
			// update now!
			--m_urgentUpdateNeeded;
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();
			m_urgentUpdateNeeded = false;
		}
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				break;	// if we're playing catchup, don't
				// bother with debugOverlayText
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();

			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}
	}
	m_justResumed = false;
}

void PlayState::draw()
{
	m_engineSharedContext.frameID++;
	// This draw() executes in two states:
	// 1. playState:	a standard draw.
	// 2. pauseState:	an 'assist draw', to display game objects.
	// If doing the latter, we have to modify our behaviour.

	// Always clear & draw game objects.
	m_window.clear();
	m_window.setView( m_engineSharedContext.view );
	arena.draw( m_window, sf::RenderStates::Default );

	// todo FIXME
	// hud.draw( m_window, sf::RenderStates::Default );

	////////////////////////////////////////
	//// SFML::ImGui Tests
	// ImGui::SFML::Update( m_window, deltaClock.restart() );
	// ImGui::Begin( "  " );
	// if ( ImGui::Button( "Quit to Desktop" ) ) {
	// m_machine.quit();
	// }
	// ImGui::End();
	//// m_window.clear();
	// m_window.draw( m_shape );
	// ImGui::SFML::Render( m_window );
	////////////////////////////////////////

	if ( !m_engineSharedContext.gameIsPaused && SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}

	// Display only if PauseState is not doing it.
	if ( !m_engineSharedContext.gameIsPaused ) {
		m_window.display();
	}
}

void PlayState::pause()
{
	#if defined DBG
	std::cout << "[DEBUG]\tPaused State:\t\t" << m_myObjNameStr << "\n";
	#endif
}

void PlayState::resume()
{
	restartStateClock();
	m_urgentUpdateNeeded = 10;
	// destroy the queue
	m_justResumed = true;
	// give me stats in the first frame, but first make up some plausible
	// values
	updateDebugOverlayTextIfEnabled( true );

	#if defined DBG
	std::cout << "[DEBUG]\tResumed State:\t\t" << m_myObjNameStr << "\n";
	#endif

	// if there is a pending play sound request, play it
	if ( m_engineSharedContext.reqSndPlyFromPlay ) {
		m_engineSharedContext.reqSndPlyFromPlay = 0;
		m_sClicked.play();
	}
}

void PlayState::processEvents()
{
	sf::Event evt;
	while ( m_window.pollEvent( evt ) ) {
		ImGui::SFML::ProcessEvent( evt );
		switch ( evt.type ) {
		case sf::Event::Closed:
			m_machine.quit();
			break;
		case sf::Event::Resized:
			// onResize();
			m_engineSharedContext.view = getLetterboxView(
					m_engineSharedContext.view
					, evt.size.width
					, evt.size.height );
			break;
		case sf::Event::MouseButtonPressed:
			if ( evt.mouseButton.button ==
			     sf::Mouse::Left ) {
				sf::Vector2i mousePos = sf::Mouse::getPosition
						( m_window );
				std::cout << "mousePos: " << mousePos.x <<
				"," << mousePos.y << '\n';
			}
		case sf::Event::KeyPressed:
			switch ( evt.key.code ) {
			case sf::Keyboard::Escape:
			case sf::Keyboard::Pause:
			case sf::Keyboard::P:
				m_engineSharedContext.
				reqSndPlyFromPause = 1;
				m_next = StateMachine::build
					<PauseState> ( m_machine, m_window
						, m_engineSharedContext
						, false
						);
				break;
			case sf::Keyboard::Q:
				std::cout << "Quitting on Q key"
				" press. Goodbye!\n";
				m_machine.quit();
				break;
			case sf::Keyboard::M:
				m_next = StateMachine::build
					<MainMenuState> ( m_machine, m_window
						, m_engineSharedContext
						, true );
				break;
			case sf::Keyboard::Numpad8:
			case sf::Keyboard::C:
				m_engineSharedContext.moveReqActiveUp = 1;
				break;
			case sf::Keyboard::Numpad9:
				m_engineSharedContext.moveReqActiveUpRight = 1;
				break;
			case sf::Keyboard::Numpad6:
			case sf::Keyboard::N:
				m_engineSharedContext.moveReqActiveRight = 1;
				break;
			case sf::Keyboard::Numpad3:
				m_engineSharedContext.moveReqActiveDownRight = 1;
				break;
			case sf::Keyboard::Numpad2:
			case sf::Keyboard::T:
				m_engineSharedContext.moveReqActiveDown = 1;
				break;
			case sf::Keyboard::Numpad1:
				m_engineSharedContext.moveReqActiveDownLeft = 1;
				break;
			case sf::Keyboard::Numpad4:
			case sf::Keyboard::H:
				m_engineSharedContext.moveReqActiveLeft= 1;
				break;
			case sf::Keyboard::Numpad7:
				m_engineSharedContext.moveReqActiveUpLeft = 1;
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
			case sf::Keyboard::CONST_GAMEDEBUGHOTKEY:
				this->tglGameDebug();
				break;
			default:
				break;
			}
			break;
		case sf::Event::KeyReleased:
			switch ( evt.key.code ) {
			case sf::Keyboard::Numpad8:
			case sf::Keyboard::C:
				m_engineSharedContext.moveReqActiveUp = 0;
				break;
			case sf::Keyboard::Numpad9:
				m_engineSharedContext.moveReqActiveUpRight = 0;
				break;
			case sf::Keyboard::Numpad6:
			case sf::Keyboard::N:
				m_engineSharedContext.moveReqActiveRight= 0;
				break;
			case sf::Keyboard::Numpad3:
				m_engineSharedContext.moveReqActiveDownRight = 0;
				break;
			case sf::Keyboard::Numpad2:
			case sf::Keyboard::T:
				m_engineSharedContext.moveReqActiveDown = 0;
				break;
			case sf::Keyboard::Numpad1:
				m_engineSharedContext.moveReqActiveDownLeft = 0;
				break;
			case sf::Keyboard::Numpad4:
			case sf::Keyboard::H:
				m_engineSharedContext.moveReqActiveLeft = 0;
				break;
			case sf::Keyboard::Numpad7:
				m_engineSharedContext.moveReqActiveUpLeft = 0;
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

void PlayState::onResize()
{
}

void PlayState::tglGameDebug(void)
{
	m_engineSharedContext.gameDebugOverlay 
	= !m_engineSharedContext.gameDebugOverlay;
	#if defined DBG
	std::cout << "[DEBUG]\tGameDebug is now:\t" 
	<< m_engineSharedContext.gameDebugOverlay  << "\n";
	#endif
}
// ===================================80 chars=================================|
/* EOF */


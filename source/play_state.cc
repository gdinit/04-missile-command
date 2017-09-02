/* play_state.cc */
// ===================================80 chars==================================

#include "play_state.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;

PlayState::PlayState( StateMachine &machine
	, sf::RenderWindow &window
	, SharedContext &context
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
}

void PlayState::initializeState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated state:\t\t" << m_myObjNameStr << "\n";
	std::cout << "[DEBUG]\tCreating New Level:\tLevel " <<
	m_sCtxt.gameLevel << "\n";
	#endif

	// TODO FIX ME ********** restartStateClock();

	m_systemResizeHourglass = 0;
	m_sCtxt.moveLeftReqActive = 0;
	m_sCtxt.moveRightReqActive = 0;

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

	// PREGAME ANIMATION STUFF
	// TODO place this in a function
	restartPregameAnimationClock();
	// TODO takeback this TEMP change: turning animation off to speed up dev
	// m_sCtxt.preGameAnimationNeeded = 1;
	m_sCtxt.preGameAnimationNeeded = 0;
	// anim stage 1
	m_preGameAnimationStep1Text.setFont( m_font );
	m_preGameAnimationStep1Text.setCharacterSize( 60u );
	m_preGameAnimationStep1Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep1Text.setString( "3" );
	centerOrigin( m_preGameAnimationStep1Text );
	m_preGameAnimationStep1Text.setPosition( C_PGA_POS_X, C_PGA_POS_Y );
	// anim stage 2
	m_preGameAnimationStep2Text.setFont( m_font );
	m_preGameAnimationStep2Text.setCharacterSize( 60u );
	m_preGameAnimationStep2Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep2Text.setString( "2" );
	centerOrigin( m_preGameAnimationStep2Text );
	m_preGameAnimationStep2Text.setPosition( C_PGA_POS_X, C_PGA_POS_Y );
	// anim stage 3
	m_preGameAnimationStep3Text.setFont( m_font );
	m_preGameAnimationStep3Text.setCharacterSize( 60u );
	m_preGameAnimationStep3Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep3Text.setString( "1" );
	centerOrigin( m_preGameAnimationStep3Text );
	m_preGameAnimationStep3Text.setPosition( C_PGA_POS_X, C_PGA_POS_Y );
	// anim stage 4
	m_preGameAnimationStep4Text.setFont( m_font );
	m_preGameAnimationStep4Text.setCharacterSize( 60u );
	m_preGameAnimationStep4Text.setFillColor( sf::Color::White );
	m_preGameAnimationStep4Text.setString( "Go!" );
	centerOrigin( m_preGameAnimationStep4Text );
	m_preGameAnimationStep4Text.setPosition( C_PGA_POS_X, C_PGA_POS_Y );

	// SOUNDS
	// TODO place this in a function
	if ( !m_sbClicked.loadFromFile(
		     "assets/sounds/button_clicked2.wav" ) ) {
	}
	m_sClicked.setBuffer( m_sbClicked );

	// if there is a pending play sound request, play it
	if ( m_sCtxt.reqSndPlyFromPlay ) {
		m_sCtxt.reqSndPlyFromPlay = 0;
		m_sClicked.play();
	}

	if ( !m_sbBlip2.loadFromFile( "assets/sounds/blip1.wav" ) ) {
	}
	m_sBlip2.setBuffer( m_sbBlip2 );

	// start a new game

	// TODO is this the best way?
	m_res.x = static_cast <float> ( C_WIN_W );
	m_res.y = static_cast <float> ( C_WIN_H );

	// signal arena to set up a new round
	// only level 1 is implemented so far
	m_sCtxt.gameLevel = 1;
	arena.newRound( m_res, m_sCtxt.gameLevel );
	hud.newRound( m_res );

	// TODO delete this?	GLOBALS->arenaNewRoundRequested = true;

	m_sCtxt.currentScore = 0;
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Reset score." << m_myObjNameStr << "\n";
	#endif
	m_sCtxt.livesLeft = 0;
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Reset lives." << m_myObjNameStr << "\n";
	#endif
}

void PlayState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	if ( m_systemResizeHourglass > 0 ) {
		--m_systemResizeHourglass;
	} else {
	}

	// if returning from pause(), let's jump in time to prevent slow catchup
	// process
	if ( m_justResumed ) {
		m_timeSinceLastUpdate = TimePerFrame;
	}

	if ( GLOBALS->returnToMainMenuRequested == 1 ) {
		// Game over! Terminate
		#if defined DBG
		std::cout << "Terminating due to returnToMainMenuRequested=1\n";
		#endif
		m_next = StateMachine::build <MainMenuState>
				( m_machine, m_window, m_sCtxt, true );
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();
		// obtain current screen res - need to pass it to game objects
		m_res = static_cast <sf::Vector2f>
			( m_window.getSize() );

		// obtain requested moveDirection - need to pass it to paddle
		if ( m_sCtxt.moveLeftReqActive &&
		     !m_sCtxt.moveRightReqActive ) {
			m_moveDirection = Direction::LEFT;
		} else if ( !m_sCtxt.moveLeftReqActive &&
			    m_sCtxt.moveRightReqActive ) {
			m_moveDirection = Direction::RIGHT;
		} else {
			m_moveDirection = Direction::NONE;
		}
		// update other game objects only if animation is not playing
		if ( !m_sCtxt.preGameAnimationNeeded ) {
			arena.update( m_elapsedTime, m_res, m_moveDirection );
			// why update HUD separately? process it with arena?
			hud.update( m_elapsedTime );
		}
		if ( m_sCtxt.mustMainMenu == true ) {
			// go to main menu immediately (all lives lost)
			m_next = StateMachine::build <MainMenuState> (
					m_machine, m_window, m_sCtxt
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
	// This draw() executes in two states:
	// 1. plasState:	a standard draw.
	// 2. pauseState:	an 'assist draw', to display game objects.
	// If doing the latter, we have to modify our behaviour.

	// Always clear & draw game objects.
	m_window.clear();

	m_window.setView( m_sCtxt.view );

	arena.draw( m_window, sf::RenderStates::Default );
	hud.draw( m_window, sf::RenderStates::Default );

	// Conditional draws & display.
	if ( m_sCtxt.preGameAnimationNeeded &&
	     !m_sCtxt.gameIsPaused ) {
		drawPreGameAnimation();
	}
	if ( !m_sCtxt.gameIsPaused && SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}

	// Display only if PlayState is not doing it.
	if ( !m_sCtxt.gameIsPaused ) {
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
	if ( m_sCtxt.reqSndPlyFromPlay ) {
		m_sCtxt.reqSndPlyFromPlay = 0;
		m_sClicked.play();
	}
}

void PlayState::processEvents()
{
	// fetch events
	sf::Event evt;

	// REMINDER:	virtual bool hasFocus() const;
	// process events
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				m_machine.quit();
				break;
			case sf::Event::Resized:
				// onResize();
				m_sCtxt.view = getLetterboxView(
						m_sCtxt.view
						, evt.size.width
						, evt.size.height );
				break;
			case sf::Event::KeyPressed:
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
					case sf::Keyboard::Pause:
					case sf::Keyboard::P:
						// InGameMenuState is commented
						// out for the time being and
						// replaced with PauseState
						// m_next = StateMachine::build
						// <InGameMenuState> (
						// m_machine, m_window, false );
						//
						// we will be destroyed soon but
						// we can request PauseState
						// to play it for us
						m_sCtxt.
						reqSndPlyFromPause = 1;
						m_next = StateMachine::build
							<PauseState> ( m_machine
								, m_window
								,
								m_sCtxt
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
							<MainMenuState> (
								m_machine
								, m_window
								,
								m_sCtxt
								, true );
						break;
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						m_sCtxt.moveLeftReqActive
							= true;
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						m_sCtxt.moveRightReqActive
							= true;
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
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch ( evt.key.code ) {
					case sf::Keyboard::Left:
					case sf::Keyboard::A:
						m_sCtxt.moveLeftReqActive =
							false;
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						m_sCtxt.moveRightReqActive
							= false;
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

// Animation Stuff
void PlayState::restartPregameAnimationClock()
{
	m_animationClock.restart();
	m_animationAge = m_animationClock.restart();
	// std::cout << "m_animationClock.restart() triggered!\t\tm_animationAge
	// is:" << m_animationAge << "\n";	// TODO REMOVE THIS
}

float PlayState::getPreGameAnimationAgeAsSeconds()
{
	sf::Time	tmp = sf::Time::Zero;

	tmp = m_animationClock.getElapsedTime();
	float		val = tmp.asSeconds();

	return val;
}

void PlayState::drawPreGameAnimation()
{
	// Each step to be displayed for 1 second:
	// preGameAnimationStep1Needed	"3"
	// preGameAnimationStep2Needed	"2"
	// preGameAnimationStep3Needed	"1"
	// preGameAnimationStep4Needed	"Go!"
	if ( getPreGameAnimationAgeAsSeconds() <= C_PGA_SD * 1 ) {
		m_sCtxt.preGameAnimationRunning = true;
		m_window.draw( m_preGameAnimationStep1Text );
		if ( m_sCtxt.preGameAnimationStep1SFXNeeded ) {
			m_sBlip2.play();
			m_sCtxt.preGameAnimationStep1SFXNeeded = false;
		}
	} else if ( getPreGameAnimationAgeAsSeconds() <= C_PGA_SD * 2 ) {
		m_window.draw( m_preGameAnimationStep2Text );
		if ( m_sCtxt.preGameAnimationStep2SFXNeeded ) {
			m_sBlip2.play();
			m_sCtxt.preGameAnimationStep2SFXNeeded = false;
		}
	} else if ( getPreGameAnimationAgeAsSeconds() <= C_PGA_SD * 3 ) {
		m_window.draw( m_preGameAnimationStep3Text );
		if ( m_sCtxt.preGameAnimationStep3SFXNeeded ) {
			m_sBlip2.play();
			m_sCtxt.preGameAnimationStep3SFXNeeded = false;
		}
		// } else if ( getPreGameAnimationAgeAsSeconds() <= C_PGA_SD * 4
		// ) {
	} else if ( getPreGameAnimationAgeAsSeconds() < C_PGA_SD * 4 ) {
		m_sCtxt.preGameAnimationRunning = false;
		m_window.draw( m_preGameAnimationStep4Text );
		if ( m_sCtxt.preGameAnimationStep4SFXNeeded ) {
			m_sBlip2.play();
			m_sCtxt.preGameAnimationStep4SFXNeeded = false;
		}
	} else if ( getPreGameAnimationAgeAsSeconds() >= C_PGA_SD * 5 ) {
		m_sCtxt.preGameAnimationNeeded = false;
		// clear 'SFXNeeded's
		m_sCtxt.preGameAnimationStep1SFXNeeded = true;
		m_sCtxt.preGameAnimationStep2SFXNeeded = true;
		m_sCtxt.preGameAnimationStep3SFXNeeded = true;
		m_sCtxt.preGameAnimationStep4SFXNeeded = true;
	}
}

// ===================================80 chars==================================
/* EOF */


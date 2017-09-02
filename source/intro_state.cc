/* intro_state.cc */
// ===================================80 chars==================================

#include "intro_state.h"

IntroState::IntroState( StateMachine &machine
	, sf::RenderWindow &window
	, SharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }, m_myObjNameStr(
		"IntroState" )
{
	m_sCtxt.tIntroFirstLaunchTime =
		std::chrono::steady_clock::now();
	initializeState();
}

IntroState::~IntroState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed state:\t" << m_myObjNameStr << "\n";
	#endif
}

void IntroState::initializeState()
{
	// Needed to center stuff
	m_worldView = m_window.getDefaultView();

	#if defined DBG
	std::cout << "[DEBUG]\tCreated state:\t\t" << m_myObjNameStr << "\n";
	#endif

	restartStateClock();

	m_systemResizeHourglass = 0;

	// TODO base these values on config variables
	m_desiredAspectRatio = 640.f / 480.f;
	#if defined DBG
	std::cout << "[DEBUG]\tm_desiredAspectRatio is: \t" <<
	m_desiredAspectRatio << " //" << m_myObjNameStr << "\n";
	#endif

	// background
	m_bgTex.loadFromFile( "assets/textures/640x480_title_screen.png" );

	// Get size of texture
	m_textureSize = m_bgTex.getSize();
	// Get size of window.
	m_windowSize = m_window.getSize();

	// Calculate scale
	float	ScaleX = ( float )m_windowSize.x / m_textureSize.x;
	float	ScaleY = ScaleX;
	// float		ScaleY = ( float )m_windowSize.y /
	// m_textureSize.y;

	// m_bg.setTexture( m_bgTex, true );
	m_bg.setTexture( m_bgTex );
	// Set scale.
	m_bg.setScale( ScaleX, ScaleY );

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	// give me stats in the first frame,
	// but first make up some plausible values
	updateDebugOverlayTextIfEnabled( true );

	// PressToContinue Text
	m_fontPressToContinue.loadFromFile( "assets/fonts/sansation.ttf" );
	m_textPressToContinue.setFont( m_fontPressToContinue );
	m_textPressToContinue.setCharacterSize( 24u );
	m_textPressToContinue.setFillColor( sf::Color::White );
	m_textPressToContinue.setString( "Press Space Bar to Continue" );
	centerOrigin( m_textPressToContinue );
	m_textPressToContinue.setPosition( ( m_worldView.getSize().x / 2 )
		, ( m_worldView.getSize().y * .85f ) );

	// Start off opaque
	m_alpha = sf::Color { 0, 0, 0, 255 };
	// Fill the fader surface with black
	m_fader.setFillColor( m_alpha );
	m_fader.setSize( static_cast <sf::Vector2f> ( m_bgTex.getSize() ) );
}

void IntroState::pause()
{
}

void IntroState::resume()
{
	restartStateClock();
}

void IntroState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

	if ( m_systemResizeHourglass > 0 ) {
		--m_systemResizeHourglass;
	}

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;
		processEvents();
		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		if ( m_statisticsUpdateTime >= sf::seconds( 1.0f ) ) {
			if ( m_statisticsNumFrames <= 1 ) {
				// if we're playing catchup,
				// don't bother with debugOverlayText
				break;
			}

			recordObservedFPS();
			dynamicallyAdjustFPSLimit();
			updateDebugOverlayTextIfEnabled();
			printConsoleDebugIfEnabled();

			m_statisticsUpdateTime -= sf::seconds( 1.0f );
			m_statisticsNumFrames = 0;
		}// exiting update statsText only once a second
	}// exiting "m_timeSinceLastUpdate > State::TimePerFrame". --
	// draw()
	// will execute now.
	if ( m_alpha.a != 0 ) {
		m_alpha.a--;
	}
	m_fader.setFillColor( m_alpha );

	// TODO: add delay timer here & when timer is out, automatically
	// continue to the main menu
}// exiting update()

void IntroState::draw()
{
	// Clear the previous drawing
	m_window.clear();
	m_window.setView( m_sCtxt.view );
	m_window.	draw(	m_bg );
	m_window.	draw(	m_statisticsText );
	// No need to draw if it's transparent
	if ( m_alpha.a != 0 ) {
		m_window.draw( m_fader );
	}
	m_window.draw( m_textPressToContinue );
	m_window.display();
}

void IntroState::processEvents()
{
	// fetch events
	sf::Event evt;

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
				// NOTE: Intro should not have pause state (no
				// user input = already paused state!)
				switch ( evt.key.code ) {
					case sf::Keyboard::Escape:
					case sf::Keyboard::Space:
					case sf::Keyboard::Return:
						m_next =
							StateMachine::build
							<MainMenuState>
								( m_machine
								, m_window
								, m_sCtxt
								, true );
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

void IntroState::onResize()
{
}

// ===================================80 chars==================================
/* EOF */


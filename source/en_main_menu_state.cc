/* main_menu_state.cc */
// ===================================80 chars==================================

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

	// TODO is this really necessary?
	// m_engineSharedContext.m_resx = static_cast <float> ( C_WIN_W );
	// m_engineSharedContext.m_resy = static_cast <float> ( C_WIN_H );

	//// resize stuff here
	// if ( m_systemResizeHourglass > 0 ) {
	// --m_systemResizeHourglass;
	// }

	while ( m_timeSinceLastUpdate > State::TimePerFrame ) {
		m_timeSinceLastUpdate -= State::TimePerFrame;

		processEvents();

		// update statistics for the debug overlay
		m_statisticsUpdateTime += m_elapsedTime;
		m_statisticsNumFrames += 1;
		// update statsText only once a second
		// however, if just entered this state
		// (i.e.: this is the 2nd updateStats), then immediately update
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
	// comment out button	this->buttonCollisionDetectRespond();
}

void MainMenuState::draw()
{
	m_window.clear();

	// TODO fix this (fast tracking during engine/game separation)
	// m_window.setView( m_engineSharedContext.view );
	// if ( SETTINGS->inGameOverlay ) {
	// m_window.draw( m_statisticsText );
	// }

	// comment out button stuff
	// m_window.	draw(	m_sprPlay );
	// m_window.	draw(	m_textPlay );
	// m_window.	draw(	m_sprCredits );
	// m_window.	draw(	m_textCredits );
	// m_window.	draw(	m_sprQuit );
	// m_window.	draw(	m_textQuit );

	m_window.display();
}

void MainMenuState::initializeState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated state:\t\t" << m_myObjNameStr << "\n";
	#endif

	restartStateClock();

	// resize stuff here
	m_systemResizeHourglass = 0;
	// TODO base these values on config variables
	m_desiredAspectRatio = 640.f / 480.f;
	#if defined DBG
	std::cout << "[DEBUG]\tm_desiredAspectRatio is: \t" <<
	m_desiredAspectRatio << " //" << m_myObjNameStr << "\n";
	#endif

	m_engineSharedContext.mustMainMenu = false;
	// TODO fix this (fast tracking during engine/game separation)
	// m_engineSharedContext.m_resx = static_cast <float> ( C_WIN_W );
	// m_engineSharedContext.m_resy = static_cast <float> ( C_WIN_H );

	m_urgentUpdateNeeded = 10;

	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );

	//// ButtonsSharedResources ==============
	// if ( !m_sbMouseOver.loadFromFile( "assets/sounds/mouse_over1.wav" ) )
	// {
	// }
	// m_sMouseOver.setBuffer( m_sbMouseOver );
	//// =====================================

	//// PlayMenuButton ======================
	// m_sprPlay.setTexture( m_textureWhite );
	// m_sprPlay.setTextureRect( sf::IntRect( 0, 0, CONST_MENU_BOX_WIDTH
	// , CONST_MENU_BOX_HEIGHT ) );
	// m_sprPlay.setOrigin( CONST_MENU_BOX_WIDTH / 2.f
	// , CONST_MENU_BOX_HEIGHT / 2.f );
	// m_sprPlay.setPosition( ( m_engineSharedContext.view.getSize().x / 2 )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_1 ) );
	// m_sprPlayNeedSFX = true;
	// m_sprPlayButtonHot = false;
	// m_fontPlayText.loadFromFile( "assets/fonts/sansation.ttf" );
	// m_textPlay.setFont( m_fontPlayText );
	// m_textPlay.setCharacterSize( 28u );
	// m_textPlay.setFillColor( sf::Color::Black );
	// m_textPlay.setString( "play   (space)" );
	// centerOrigin( m_textPlay );
	// m_textPlay.setPosition( ( m_engineSharedContext.view.getSize().x / 2
	// )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_1 ) );
	//// =====================================

	//// CreditsMenuButton ===================
	// m_sprCredits.setTexture( m_textureWhite );
	// m_sprCredits.setTextureRect( sf::IntRect( 0, 0, CONST_MENU_BOX_WIDTH
	// , CONST_MENU_BOX_HEIGHT ) );
	// m_sprCredits.setOrigin( CONST_MENU_BOX_WIDTH / 2.f
	// , CONST_MENU_BOX_HEIGHT / 2.f );
	// m_sprCredits.setPosition( ( m_engineSharedContext.view.getSize().x /
	// 2 )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_2 ) );
	// m_sprCreditsNeedSFX = true;
	// m_sprCreditsButtonHot = false;
	// m_fontCreditsText.loadFromFile( "assets/fonts/sansation.ttf" );
	// m_textCredits.setFont( m_fontCreditsText );
	// m_textCredits.setCharacterSize( 28u );
	// m_textCredits.setFillColor( sf::Color::Black );
	// m_textCredits.setString( "credits   (C)" );
	// centerOrigin( m_textCredits );
	// m_textCredits.setPosition( ( m_engineSharedContext.view.getSize().x /
	// 2 )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_2 ) );
	//// =====================================

	//// QuitMenuButton ======================
	// m_sprQuit.setTexture( m_textureWhite );
	// m_sprQuit.setTextureRect( sf::IntRect( 0, 0, CONST_MENU_BOX_WIDTH
	// , CONST_MENU_BOX_HEIGHT ) );
	// m_sprQuit.setOrigin( CONST_MENU_BOX_WIDTH / 2.f
	// , CONST_MENU_BOX_HEIGHT / 2.f );
	// m_sprQuit.setPosition( ( m_engineSharedContext.view.getSize().x / 2 )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_3 ) );
	// m_sprQuitNeedSFX = true;
	// m_sprQuitButtonHot = false;
	// m_fontQuitText.loadFromFile( "assets/fonts/sansation.ttf" );
	// m_textQuit.setFont( m_fontQuitText );
	// m_textQuit.setCharacterSize( 28u );
	// m_textQuit.setFillColor( sf::Color::Black );
	// m_textQuit.setString( "quit   (Q)" );
	// centerOrigin( m_textQuit );
	// m_textQuit.setPosition( ( m_engineSharedContext.view.getSize().x / 2
	// )
	// , ( m_engineSharedContext.view.getSize().y *
	// CONST_MENU_BUTTON_3 ) );
	//// =====================================

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

// void MainMenuState::buttonCollisionDetectRespond( void ) noexcept
// {
//// DETECT CURSOR & BUTTON COLLISION

//// We shouldn't do this if window has no focus.
// if ( !m_engineSharedContext.pWindow->hasFocus() ) {

//// Window IS NOT focused, quit
// return;
// }

//// DETECT CURSOR & BUTTON COLLISION
// m_mousePos = sf::Mouse::getPosition( m_window );
//// Begin MenuButton: Play ====================
// if ( sf::Mouse::getPosition( m_window ).x >
// m_sprPlay.getGlobalBounds().left
// && sf::Mouse::getPosition( m_window ).x <
// ( m_sprPlay.getGlobalBounds().left +
// m_sprPlay.getGlobalBounds().width )
// && sf::Mouse::getPosition( m_window ).y >
// m_sprPlay.getGlobalBounds().top
// && sf::Mouse::getPosition( m_window ).y <
// ( m_sprPlay.getGlobalBounds().top +
// m_sprPlay.getGlobalBounds().height ) ) {
// m_textPlay.setCharacterSize( 36u );
// centerOrigin( m_textPlay );
// m_textPlay.setPosition(
// ( m_engineSharedContext.view.getSize().x / 2
// )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_1 ) );
// m_sprPlayButtonHot = true;
// if ( m_sprPlayNeedSFX ) {
// m_sMouseOver.play();
// m_sprPlayNeedSFX = false;
// }
// } else {
// m_sprPlayButtonHot = false;
// m_sprPlayNeedSFX = true;
// m_textPlay.setCharacterSize( 28u );
// centerOrigin( m_textPlay );
// m_textPlay.setPosition(
// ( m_engineSharedContext.view.getSize().x / 2
// )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_1 ) );
// }
//// End MenuButton: Play ====================

//// Begin MenuButton: Credits ====================
// if ( sf::Mouse::getPosition( m_window ).x >
// m_sprCredits.getGlobalBounds().left
// && sf::Mouse::getPosition( m_window ).x <
// ( m_sprCredits.getGlobalBounds().left +
// m_sprCredits.getGlobalBounds().width )
// && sf::Mouse::getPosition( m_window ).y >
// m_sprCredits.getGlobalBounds().top
// && sf::Mouse::getPosition( m_window ).y <
// ( m_sprCredits.getGlobalBounds().top +
// m_sprCredits.getGlobalBounds().height ) ) {
// m_textCredits.setCharacterSize( 36u );
// centerOrigin( m_textCredits );
// m_textCredits.setPosition(
// ( m_engineSharedContext.view.getSize().x / 2 )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_3 ) );
// m_sprCreditsButtonHot = true;
// if ( m_sprCreditsNeedSFX ) {
// m_sMouseOver.play();
// m_sprCreditsNeedSFX = false;
// }
// } else {
// m_sprCreditsButtonHot = false;
// m_sprCreditsNeedSFX = true;
// m_textCredits.setCharacterSize( 28u );
// centerOrigin( m_textCredits );
// m_textCredits.setPosition(
// ( m_engineSharedContext.view.getSize().x / 2 )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_3 ) );
// }
//// End MenuButton: Credits ====================

//// Begin MenuButton: Quit ====================
// if ( sf::Mouse::getPosition( m_window ).x >
// m_sprQuit.getGlobalBounds().left
// && sf::Mouse::getPosition( m_window ).x <
// ( m_sprQuit.getGlobalBounds().left +
// m_sprQuit.getGlobalBounds().width )
// && sf::Mouse::getPosition( m_window ).y >
// m_sprQuit.getGlobalBounds().top
// && sf::Mouse::getPosition( m_window ).y <
// ( m_sprQuit.getGlobalBounds().top +
// m_sprQuit.getGlobalBounds().height ) ) {
// m_textQuit.setCharacterSize( 36u );
// centerOrigin( m_textQuit );
// m_textQuit.setPosition( (
// m_engineSharedContext.view.getSize().x / 2 )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_3 ) );
// m_sprQuitButtonHot = true;
// if ( m_sprQuitNeedSFX ) {
// m_sMouseOver.play();
// m_sprQuitNeedSFX = false;
// }
// } else {
// m_sprQuitButtonHot = false;
// m_sprQuitNeedSFX = true;
// m_textQuit.setCharacterSize( 28u );
// centerOrigin( m_textQuit );
// m_textQuit.setPosition(
// ( m_engineSharedContext.view.getSize().x / 2
// )
// , ( m_engineSharedContext.view.getSize().y *
// CONST_MENU_BUTTON_3 ) );
// }
//// End MenuButton: Quit ====================
// }

void MainMenuState::processEvents()
{
	// fetch events
	sf::Event evt;

	// process events
	while ( m_window.pollEvent( evt ) ) {
		switch ( evt.type ) {
			case sf::Event::Closed:
				std::cout << "Quitting on close event."
				" Goodbye!\n";
				m_machine.quit();
			case sf::Event::Resized:
				// onResize();
				m_engineSharedContext.view = getLetterboxView(
						m_engineSharedContext.view
						, evt.size.width
						, evt.size.height );
				break;
			// comment out button
			// case sf::Event::MouseButtonPressed:
			// if ( m_sprPlayButtonHot ) {
			//// we will be destroyed soon but
			//// we can request PS to play it for us
			// m_engineSharedContext.reqSndPlyFromPlay
			// = 1;
			// m_next = StateMachine::build <PlayState>
			// ( m_machine
			// , m_window
			// , m_engineSharedContext
			// , true );
			// break;
			// } else if ( m_sprCreditsButtonHot ) {
			// m_engineSharedContext.reqSndPlyFromPlay
			// = 1;
			// m_next = StateMachine::build <PlayState>
			// ( m_machine
			// , m_window
			// , m_engineSharedContext
			// , true );
			// break;
			// } else if ( m_sprQuitButtonHot ) {
			// std::cout <<
			// "Quitting on mouse click. Goodbye!\n";
			// m_machine.quit();
			// break;
			// }
			// break;
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

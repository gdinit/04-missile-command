/* en_main_menu_state.cc */
// ===================================80 chars=================================|

#include "en_main_menu_state.h"

MainMenuState::MainMenuState( StateMachine &machine
	, sf::RenderWindow &window
	, EngineSharedContext &context
	, bool replace )
	: State{ machine, window, context, replace }, m_myObjNameStr(
		"MainMenuState" )
{
	// Get size of window.
	m_windowSize = m_window.getSize();
	std::cout << "m_windowSize.x is: " << m_windowSize.x <<
	"\t m_windowSize.y is: " << m_windowSize.y << "\n";
	initializeState();
}

MainMenuState::~MainMenuState()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed state:\t" << m_myObjNameStr << "\n";
	#endif
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
	m_urgentUpdateNeeded = 10;
	// debug overlay font
	m_font.loadFromFile( "assets/fonts/sansation.ttf" );
	m_statisticsText.setFont( m_font );
	m_statisticsText.setPosition( 5.f, 5.f );
	m_statisticsText.setCharacterSize( 12u );
	m_statisticsText.setFillColor( sf::Color::White );
	updateDebugOverlayTextIfEnabled( true );
	////////////////////////////////////////
	// SFML::ImGui Tests
	deltaClock.restart();
	ImGui::SFML::Init( m_window );
	m_clicked = 0;
	////////////////////////////////////////
	m_bgColor = sf::Color::Black;
	m_tintColor = sf::Color::Black;
	m_tex1Play.loadFromFile( "assets/textures/menu-1-play.png" );
	m_tex2Cred.loadFromFile( "assets/textures/menu-2-cred.png" );
	m_tex3Exit.loadFromFile( "assets/textures/menu-3-exit.png" );
}

void MainMenuState::update()
{
	sf::Time m_elapsedTime = m_clock.restart();
	m_timeSinceLastUpdate += m_elapsedTime;

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
}

void MainMenuState::draw()
{
	m_engineSharedContext.frameID++;
	m_window.clear();
	m_window.setView( m_engineSharedContext.view );
	ImGui::SFML::Update( m_window, deltaClock.restart() );
	// =====================================================================
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	// window_flags |= ImGuiWindowFlags_MenuBar;
	// window_flags |= ImGuiWindowFlags_ShowBorders;
	//
	// ImGui::SetNextWindowPos( ImVec2( m_windowSize.x / 2, m_windowSize.y
	/// 2 ), ImGuiCond_Always );
	//
	// FIXME hardcoded value. not safe. should be calculated
	ImGui::SetNextWindowSize( ImVec2( 160, 160 ), ImGuiCond_Always );
	ImGui::SetNextWindowPosCenter( ImGuiCond_Always );
	bool b = true;
	ImGui::Begin( " ", &b, window_flags );
	// =====================================================================
	if ( ImGui::ImageButton( m_tex1Play, -1, sf::Color::Green
		     , sf::Color::White ) ) {
		m_next = StateMachine::build <PlayState> ( m_machine, m_window
				, m_engineSharedContext, true );
	}
	// =====================================================================
	if ( ImGui::ImageButton( m_tex2Cred, -1, sf::Color::Green
		     , sf::Color::White ) ) {
		m_next = StateMachine::build <PlayState> ( m_machine, m_window
				, m_engineSharedContext, true );
	}
	// =====================================================================
	if ( ImGui::ImageButton( m_tex3Exit, -1, sf::Color::Green
		     , sf::Color::White ) ) {
		m_machine.quit();
	}
	// =====================================================================
	ImGui::End();
	ImGui::SFML::Render( m_window );
	// =====================================================================
	if ( SETTINGS->inGameOverlay ) {
		m_window.draw( m_statisticsText );
	}
	m_window.display();
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

void MainMenuState::processEvents()
{
	// fetch events
	sf::Event evt;

	// process events
	while ( m_window.pollEvent( evt ) ) {
		ImGui::SFML::ProcessEvent( evt );
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

// ===================================80 chars=================================|
/* EOF */


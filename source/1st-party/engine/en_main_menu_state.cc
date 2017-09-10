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
	// SET UP SPRITE
	m_spr1Play.setOrigin( m_dimension.x / 2.f, m_dimension.y / 2.f );
	m_spr1Play.setPosition( m_windowSize.x / 2, m_windowSize.y / 2 );

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
	// m_shape.setFillColor( sf::Color::Green );
	// m_shape.setRadius( 5 );
	// m_shape.setOutlineColor( sf::Color::Red );
	// m_shape.setOutlineThickness( 1 );
	// m_shape.setPosition( 10, 80 );
	////////////////////////////////////////

	m_bgColor = sf::Color::Black;
	m_tintColor = sf::Color::Black;
	makeButtonPlay();
	makeButtonCred();
	makeButtonExit();
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
	m_window.clear();
	m_window.setView( m_engineSharedContext.view );

	////////////////////////////////////////
	ImGui::SFML::Update( m_window, deltaClock.restart() );
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoTitleBar;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoScrollbar;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	// window_flags |= ImGuiWindowFlags_MenuBar;
	// window_flags |= ImGuiWindowFlags_ShowBorders;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoMove;
	ImGui::SetNextWindowSize( ImVec2( m_windowSize.x / 2
			, m_windowSize.y / 2 ), ImGuiCond_Always );
	// ImGui::Begin( " ", ( bool* )true, window_flags );
	// ImGui::Begin( " ", std::make_unique <bool> ( true ).get(),
	// window_flags );
	bool b = true;
	ImGui::Begin( " ", &b, window_flags );

	// ImGui::ImageButton( m_tex1Play, 1 )
	// ImGui::ImageButton(const sf::Texture& texture, const int framePadding
	// = -1, const sf::Color& bgColor = sf::Color::Transparent, const
	// sf::Color& tintColor = sf::Color::White);
	// ImGui::ImageButton( m_tex1Play, 1, sf::Color::Transparent,
	// sf::Color::White );
	// =====================================================================
	if ( ImGui::ImageButton( m_tex1Play, 1, sf::Color::Transparent
		     , sf::Color::White ) ) {
		// ImGui::ImageButton( m_tex1Play, 1 )
		#if defined DBG
		std::cout << "[DEBUG] (" << m_myObjNameStr << ") button " <<
		"clicked.\n";
		#endif
		m_next = StateMachine::build <PlayState> ( m_machine
				, m_window
				, m_engineSharedContext, true );
	}
	// =====================================================================
	if ( ImGui::ImageButton( m_tex2Cred, 1 ) ) {
		#if defined DBG
		std::cout << "[DEBUG] (" << m_myObjNameStr << ") button " <<
		"clicked.\n";
		#endif
		// TODO add CREDITS action here
		m_next = StateMachine::build <PlayState> ( m_machine, m_window
				, m_engineSharedContext, true );
	}
	// =====================================================================
	if ( ImGui::ImageButton( m_tex3Exit, 1 ) ) {
		#if defined DBG
		std::cout << "[DEBUG] (" << m_myObjNameStr << ") button " <<
		"clicked.\n";
		#endif
		m_machine.quit();
	}
	// =====================================================================
	ImGui::End();
	ImGui::SFML::Render( m_window );
	////////////////////////////////////////

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

void MainMenuState::makeButtonPlay() noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a button...\n";
	#endif

	// std::ifstream	i( "data/defines.json" );
	// nlohmann::json	j;
	// i >> j;
	// for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	// ++it ) {
	// if ( it.key() == "terrainXPosRatio" ) {
	// m_btnPlayXPosRatio = it.value();
	// } else if ( it.key() == "terrainYPosRatio" ) {
	// m_btnPlayYPosRatio = it.value();
	// } else if ( it.key() == "terrainWidthRatio" ) {
	// m_btnPlayWidthRatio = it.value();
	// } else if ( it.key() == "terrainHeightRatio" ) {
	// m_btnPlayHeightRatio = it.value();
	// }
	// }
	// i.close();

	m_btnPlayXPosRatio = 0.5;
	m_btnPlayYPosRatio = 0.2;
	m_btnPlayWidthRatio = 0.15;
	m_btnPlayHeightRatio = 0.05;

	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_btnPlayXPosRatio is: " << m_btnPlayXPosRatio <<
	"\t m_btnPlayYPosRatio is: " << m_btnPlayYPosRatio << "\n";
	#endif
	PASSERT(        ( m_btnPlayXPosRatio > 0 )
		, "ERROR: m_btnPlayXPosRatio must be > 0!\tIt is: " <<
		m_btnPlayXPosRatio << "\n" );
	PASSERT(        ( m_btnPlayYPosRatio > 0 )
		, "ERROR: m_btnPlayYPosRatio must be > 0!\tIt is: " <<
		m_btnPlayYPosRatio << "\n" );
	m_position.x = m_windowSize.x * m_btnPlayXPosRatio;
	m_position.y = m_windowSize.y * m_btnPlayYPosRatio;
	m_dimension.x = m_windowSize.x * m_btnPlayWidthRatio;
	m_dimension.y = m_windowSize.y * m_btnPlayHeightRatio;
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated Play" <<
	" position as: " << m_position.x << "," << m_position.y << "\t"	<<
	"[DEBUG]\tCalculated Play size as w: " << m_dimension.x << "\t h: " <<
	m_dimension.y << "\n";
	#endif
	m_tex1Play.loadFromFile( "assets/textures/menu-1-play.png" );
	m_spr1Play.setTexture( m_tex1Play, true );
	m_spr1Play.setPosition( m_position.x, m_position.y );
}

void MainMenuState::makeButtonCred() noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a button...\n";
	#endif

	m_btnCredXPosRatio = 0.5;
	m_btnCredYPosRatio = 0.2;
	m_btnCredWidthRatio = 0.15;
	m_btnCredHeightRatio = 0.05;

	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_btnCredXPosRatio is: " << m_btnCredXPosRatio <<
	"\t m_btnCredYPosRatio is: " << m_btnCredYPosRatio << "\n";
	#endif
	PASSERT(        ( m_btnCredXPosRatio > 0 )
		, "ERROR: m_btnCredXPosRatio must be > 0!\tIt is: " <<
		m_btnCredXPosRatio << "\n" );
	PASSERT(        ( m_btnCredYPosRatio > 0 )
		, "ERROR: m_btnCredYPosRatio must be > 0!\tIt is: " <<
		m_btnCredYPosRatio << "\n" );
	m_position.x = m_windowSize.x * m_btnCredXPosRatio;
	m_position.y = m_windowSize.y * m_btnCredYPosRatio;
	m_dimension.x = m_windowSize.x * m_btnCredWidthRatio;
	m_dimension.y = m_windowSize.y * m_btnCredHeightRatio;
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated Cred" <<
	" position as: " << m_position.x << "," << m_position.y << "\t"	<<
	"[DEBUG]\tCalculated Cred size as w: " << m_dimension.x << "\t h: " <<
	m_dimension.y << "\n";
	#endif
	m_tex2Cred.loadFromFile( "assets/textures/menu-2-cred.png" );
	m_spr2Cred.setTexture( m_tex2Cred, true );
	m_spr2Cred.setPosition( m_position.x, m_position.y );
}

void MainMenuState::makeButtonExit() noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a button...\n";
	#endif

	m_btnExitXPosRatio = 0.5;
	m_btnExitYPosRatio = 0.2;
	m_btnExitWidthRatio = 0.15;
	m_btnExitHeightRatio = 0.05;

	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_btnExitXPosRatio is: " << m_btnExitXPosRatio <<
	"\t m_btnExitYPosRatio is: " << m_btnExitYPosRatio << "\n";
	#endif
	PASSERT(        ( m_btnExitXPosRatio > 0 )
		, "ERROR: m_btnExitXPosRatio must be > 0!\tIt is: " <<
		m_btnExitXPosRatio << "\n" );
	PASSERT(        ( m_btnExitYPosRatio > 0 )
		, "ERROR: m_btnExitYPosRatio must be > 0!\tIt is: " <<
		m_btnExitYPosRatio << "\n" );
	m_position.x = m_windowSize.x * m_btnExitXPosRatio;
	m_position.y = m_windowSize.y * m_btnExitYPosRatio;
	m_dimension.x = m_windowSize.x * m_btnExitWidthRatio;
	m_dimension.y = m_windowSize.y * m_btnExitHeightRatio;
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated Exit" <<
	" position as: " << m_position.x << "," << m_position.y << "\t"	<<
	"[DEBUG]\tCalculated Exit size as w: " << m_dimension.x << "\t h: " <<
	m_dimension.y << "\n";
	#endif
	m_tex3Exit.loadFromFile( "assets/textures/menu-3-exit.png" );
	m_spr3Exit.setTexture( m_tex3Exit, true );
	m_spr3Exit.setPosition( m_position.x, m_position.y );
}

// ===================================80 chars==================================
/* EOF */


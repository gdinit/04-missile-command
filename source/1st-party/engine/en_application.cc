/* en_application.cc */
// ===================================80 chars==================================

#include "en_application.h"

// TODO remove this
extern std::unique_ptr <Settings>	SETTINGS;
// TODO remove this
extern std::unique_ptr <Globals>	GLOBALS;

Application::Application()
	: m_myObjNameStr( "Application" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

Application::~Application()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

sf::View getLetterboxView( sf::View view, int windowWidth, int windowHeight ) {
	// Compares the aspect ratio of the window to the aspect ratio of the
	// view, and sets the view's viewport accordingly in order to archieve
	// a letterbox effect. A new view (with a new viewport set) is returned.
	float	windowRatio = windowWidth / ( float )windowHeight;
	float	viewRatio = view.getSize().x / ( float )view.getSize().y;
	float	sizeX = 1;
	float	sizeY = 1;
	float	posX = 0;
	float	posY = 0;
	bool	horizontalSpacing = true;
	if ( windowRatio < viewRatio ) {
		horizontalSpacing = false;
	}
	// If horizontalSpacing is true, the black bars will appear on the left
	// and right side. Otherwise, will appear at the top and bottom.
	if ( horizontalSpacing ) {
		sizeX = viewRatio / windowRatio;
		posX = ( 1 - sizeX ) / 2.f;
	} else {
		sizeY = windowRatio / viewRatio;
		posY = ( 1 - sizeY ) / 2.f;
	}
	view.setViewport( sf::FloatRect( posX, posY, sizeX, sizeY ) );

	return view;
}

void Application::createWindow()
{
	sf::VideoMode	desktopVM = sf::VideoMode::getDesktopMode();

	int32		w = 0, h = 0;
	w = CONST_EN_SCREENRES_W;
	h = CONST_EN_SCREENRES_W / 1.333333333333333;
	if ( CONST_WIN_FULLSCREEN ) {
		// use:	fixed-res & fullscreen
		#if defined DBG
		std::cout << "[DEBUG]\tFixed Resolution"
		" with Fullscreen Mode. Requested: " << w << "," << h <<
		"\t Detected bpp is: " << desktopVM.bitsPerPixel << "\n";
		#endif
		m_window.create( sf::VideoMode( w, h, desktopVM.bitsPerPixel )
			, CONST_GAME_NAME
			, sf::Style::Fullscreen );
	} else {
		// use:	fixed-res & windowed (no fullscreen)
		#if defined DBG
		std::cout << "[DEBUG]\tFixed Resolution Windowed mode."
		" Requested: " << w << "," << h << "\t Detected bpp is: " <<
		desktopVM.bitsPerPixel << "\n";
		#endif
		m_window.create( sf::VideoMode( w, h, desktopVM.bitsPerPixel )
			, CONST_GAME_NAME
			, sf::Style::Default );
	}
	m_engineSharedContext.view.setSize( w, h );
	m_engineSharedContext.view.setCenter(
		m_engineSharedContext.view.getSize().x / 2
		, m_engineSharedContext.view.getSize().y / 2 );
	m_engineSharedContext.view = getLetterboxView(
			m_engineSharedContext.view, w, h );
	m_engineSharedContext.pWindow = &m_window;
}

void Application::loadSettings()
{
	// TODO move this somewhere in Game
	SETTINGS->inGameOverlay = C_DEBUG_SHOW_OVERLAY;
	SETTINGS->debugPrintToConsole = C_D_CO;
	SETTINGS->debugPrintToConsoleFPS = C_D_DFPS_CO;
}

void Application::run()
{
	loadSettings();

	// Create render window
	sf::ContextSettings windowSettings;
	createWindow();
	windowSettings.antialiasingLevel = 8;
	m_window.setFramerateLimit( CONST_DESIRED_FPS_INT );
	m_window.setKeyRepeatEnabled( false );

	m_machine.run( StateMachine::build <IntroState> ( m_machine
			, m_window
			, m_engineSharedContext
			, true ) );

	// Main Loop
	while ( m_machine.running() ) {
		m_machine.nextState();
		m_machine.update();
		if ( m_engineSharedContext.gameIsPaused ) {
			m_machine.drawPrevious();
		}
		m_machine.draw();
	}
}

// ===================================80 chars==================================
/* EOF */


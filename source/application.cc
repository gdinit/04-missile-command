/* application.cc */
// ===================================80 chars==================================

#include "application.h"

extern std::unique_ptr <Settings>	SETTINGS;
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

	// TODO	really 'detect' this from desktop mode
	m_sCtxt.m_desktopResY = 1080.f;

	int32		w = 0, h = 0;
	h = C_WIN_H;
	w = C_WIN_W;
	if ( C_WIN_FULLSCREEN ) {
		// use:	fixed-res & fullscreen
		#if defined DBG
		std::cout << "[DEBUG]\tFixed Resolution"
		" with Fullscreen requested: " << h << "," << w <<
		" Detected bpp is: " << desktopVM.bitsPerPixel << "\n";
		#endif

		m_window.create( sf::VideoMode( w, h
				, desktopVM.bitsPerPixel )
			, C_WIN_TITLETEXT
			, sf::Style::Fullscreen );
	} else {
		// use:	fixed-res & windowed (no fullscreen)
		#if defined DBG
		std::cout << "[DEBUG]\tFixed Resolution Windowed mode"
		" Requested: " << w << "," << h << "," <<
		" Detected bpp is: " << desktopVM.bitsPerPixel << "\n";
		#endif

		m_window.create( sf::VideoMode( w, h
				, desktopVM.bitsPerPixel )
			, C_WIN_TITLETEXT
			, sf::Style::Default );
	}

	m_sCtxt.view.setSize( w, h );
	m_sCtxt.view.setCenter( m_sCtxt.view.getSize().x / 2
		, m_sCtxt.view.getSize().y / 2 );
	m_sCtxt.view = getLetterboxView( m_sCtxt.view, w, h );
	m_sCtxt.pWindow = &m_window;
}

void Application::loadSettings()
{
	SETTINGS->inGameOverlay = C_DEBUG_SHOW_OVERLAY;
	SETTINGS->debugPrintToConsole = C_D_CO;
	SETTINGS->debugPrintToConsoleFPS = C_D_DFPS_CO;
	SETTINGS->ballSpeed = C_BALL_SPEED;
}

void Application::loadGlobals()
{
	// Nothing here -- TODO remove this?
}

void Application::run()
{
	loadSettings();
	loadGlobals();

	// Create render window
	sf::ContextSettings windowSettings;
	createWindow();
	windowSettings.antialiasingLevel = 8;
	m_window.setFramerateLimit( C_DESIRED_FPS_INT );
	m_window.setKeyRepeatEnabled( false );

	m_machine.run( StateMachine::build <IntroState> ( m_machine
			, m_window
			, m_sCtxt
			, true ) );

	// Main Loop
	while ( m_machine.running() ) {
		m_machine.nextState();
		m_machine.update();
		if ( m_sCtxt.gameIsPaused ) {
			m_machine.drawPrevious();
		}
		m_machine.draw();
	}
}

// ===================================80 chars==================================
/* EOF */


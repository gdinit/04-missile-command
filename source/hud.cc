/* hud.cc */
// ===================================80 chars==================================

#include "hud.h"

// Required for HUD Text	TOOD remove this global
extern std::unique_ptr <Globals> GLOBALS;

Hud::Hud()
	: m_myObjNameStr( "Hud" )
	// Hud::Hud( SharedContext &context )
	// : m_sCtxt( context )
	// , m_myObjNameStr( "Hud" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif

	// HUD TEXT
	m_hudTextFont.loadFromFile( "assets/fonts/atic.ttf" );
	m_hudText.setFont( m_hudTextFont );
	m_hudText.setCharacterSize( 36u );
	m_hudText.setFillColor( sf::Color::White );
	m_hudText.setString( GLOBALS->gameHudText );
	// NOTE: setPos will be done by newRound
}

Hud::~Hud()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Hud::update( sf::Time timeSinceLastUpdate )
{
	std::string	old_string = std::to_string( GLOBALS->currentScore );
	int		n_zero = 3;
	GLOBALS->currentScoreText = std::string( n_zero - old_string.length()
			, '0' ) + old_string;

	m_hudText.setString( GLOBALS->currentScoreText + "      " +
		std::	to_string( GLOBALS->livesLeft )	+ "      " +
		std::	to_string(
			GLOBALS->gameLevel ) );
	centerOrigin( m_hudText );
}

void Hud::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target.draw( m_hudText );
}

void Hud::newRound( sf::Vector2f res )
{
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif

	// HUD Resets
	GLOBALS->currentScore = 0;
	GLOBALS->currentScoreText = std::to_string( GLOBALS->currentScore );
	GLOBALS->livesLeft = C_LIVES;
	GLOBALS->gameLevel = 1;
	m_hudText.setPosition( ( res.x / 2 ), ( res.y * 0.10f ) );
}

// ===================================80 chars==================================
/* EOF */


/* arena.cc */
// ===================================80 chars==================================

#include "arena.h"

// Required for lives etc.	TOOD remove this global
extern std::unique_ptr <Globals> GLOBALS;

// For ImpactZone debug cout
template<typename T>
std::ostream & operator <<( typename std::enable_if <std::is_enum <T>::value
		, std::ostream>::type &stream, const T &e )
{
	return stream << static_cast <typename
	std::underlying_type <T>::type> ( e );
}

Arena::Arena()
	: m_myObjNameStr( "Arena" )
	// , m_hgPaddle{ 0 }
	// , m_hgTopBar{ 0 }
	// , m_hgLeftBar{ 0 }
	// , m_hgRightBar{ 0 }
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	std::cout << "[DEBUG]\tIN PROGRESS: Loading textures..." <<
	m_myObjNameStr << "\n";
	#endif
	// if ( !m_squareTexture.loadFromFile(
	// "assets/textures/texturepak.png" ) ) {
	// std::cout << "\nERROR while attempting to load a resource!\n";
	// exit( EXIT_FAILURE );
	// }
	#if defined DBG
	// std::cout << "[DEBUG]\tSUCCESS: Loaded textures." << m_myObjNameStr
	// <<
	// "\n";
	// std::cout << "[DEBUG]\tIN PROGRESS: Loading sounds..." <<
	// m_myObjNameStr << "\n";
	#endif
	// if ( !m_sndbfColPaddle.loadFromFile(
	// "assets/sounds/collision1.wav" ) ) {
	// std::cout << "\nERROR while attempting to load a resource!\n";
	// exit( EXIT_FAILURE );
	// }
	// m_soundColPaddle.setBuffer( m_sndbfColPaddle );
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Loaded sounds." << m_myObjNameStr <<
	"\n";
	#endif
}

Arena::~Arena() {
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Arena::update( sf::Time timeSinceLastUpdate, sf::Vector2f res, Direction
	dir ) {
	//// Hourglass decrements
	// if ( m_hgPaddle > 0 ) {
	// --m_hgPaddle;
	// }
	// if ( m_hgTopBar > 0 ) {
	// --m_hgTopBar;
	// }
	// if ( m_hgLeftBar > 0 ) {
	// --m_hgLeftBar;
	// }
	// if ( m_hgRightBar > 0 ) {
	// --m_hgRightBar;
	// }
	// paddle.update( timeSinceLastUpdate, res, dir, leftBar.getRight()
	// , rightBar.getLeft() );
	AAGAimPointer.update( timeSinceLastUpdate, res, dir, topBar.getBottom()
		, leftBar.getRight(), bottomBar.getTop(), rightBar.getLeft() );
	// ball.update( timeSinceLastUpdate, res );
	// paintCells();
	// colDetRespond();
}

void Arena::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target. draw(	AAGAimPointer.m_sprite );
	target. draw(	topBar.m_sprite );
	target. draw(	leftBar.m_sprite );
	target. draw(	bottomBar.m_sprite );
	target. draw(	rightBar.m_sprite );
	// target. draw(	paddle.m_sprite );
	// for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
	// if ( m_cDetDB [ n ].HP > 0 && m_cDetDB [ n ].visible &&
	// m_cDetDB [ n ].phantom != 1 ) {
	// target.draw( m_cSDB [ n ] );
	// }
	// }
	// target.draw( ball.m_sprite );
}

void Arena::newRound( sf::Vector2f res, int32 level ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tLevel is: " << level << "\n";
	#endif
	// m_tmpRes = res;
	topBar.newRound( res );
	leftBar.newRound( res );
	bottomBar.newRound( res );
	rightBar.newRound( res );
	AAGAimPointer.newRound( res );
	// createCells( res, level );
	// paddle.newRound( res );
	// ball.newRound( res );
	//// Hourglass resets
	// m_hgPaddle = 0;
	// m_hgTopBar = 0;
	// m_hgLeftBar = 0;
	// m_hgRightBar = 0;
}

void Arena::createCells( sf::Vector2f res, int32 level ) {
}

void Arena::paintCells( void )
{
}

// COLLISION:	DETECT & RESPOND
void Arena::colDetRespond( void )
{
	// colDetRespondBallWall();
	// colDetRespondBallPaddle();
	// colDetRespondBallGoal();
	// colDetRespondBallCell();
}

// Collision Detection & Response:	Ball->Wall
void Arena::colDetRespondBallWall( void )
{
}

// Collision Detection & Response:	Ball->Paddle
void Arena::colDetRespondBallPaddle( void )
{
}

// Collision Detection & Response:	Ball->Goal line
void Arena::colDetRespondBallGoal( void )
{
}

// Collision Detection & Response:	Ball->Cell
void Arena::colDetRespondBallCell( void )
{
}

// ===================================80 chars==================================
/* EOF */


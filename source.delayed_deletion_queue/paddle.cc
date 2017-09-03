/* paddle.cc */
// ===================================80 chars==================================

#include "paddle.h"

Paddle::Paddle()
	: m_myObjNameStr( "Paddle" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif

	// SET UP SPRITE
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( 0, 0, C_PADDLE_W, C_PADDLE_H ) );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( C_PADDLE_W / 2.f, C_PADDLE_H / 2.f );
	m_sprite.setPosition( 0, 0 );
}

Paddle::~Paddle()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Paddle::update( sf::Time timeSinceLastUpdate, sf::Vector2f	r, Direction
	dir, float leftBarRE, float rightBarLE )
{
	manageMovement( r, dir, leftBarRE, rightBarLE );
	// #if defined DBG
	// std::cout << "Paddle bottom: " << getBottom() << "\n";
	// #endif
}

void Paddle::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	// draw will be done by Arena
}

void Paddle::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\n";
	#endif

	////////////////////////////////////////
	// place the object for new round -- reset paddle position

	// todo - do this in one step?
	m_position.x = res.x / 2;
	m_position.y = res.y * 0.8608058608058608f;
	m_sprite.setPosition( m_position );
	#if defined DBG
	std::cout << "[DEBUG]\tsetPos'd sprite. New location: " <<
	m_position.x << "," << m_position.y << " //" << m_myObjNameStr << "\n";
	#endif

	// m_sprite.setPosition((SETTINGS->currentScreenSizeWidth -
	// SETTINGS->paddleIndent), SETTINGS->currentScreenSizeHeight / 2.f);
	/*
	sf::Vector2f centreOfScreen {
	        ( centreOfScreen.x = SETTINGS->currentScreenSizeWidth / 2 )
	        , ( centreOfScreen.y = SETTINGS->currentScreenSizeHeight / 2 )
	};

	m_sprite.setPosition( centreOfScreen );
	*/
}

void Paddle::manageMovement( sf::Vector2f res, Direction dir, float leftBarRE
	, float rightBarLE )
{
	// Notes:
	// 1. maybe we will move, maybe we wont...
	// 2. SinglePlayer game demo scene can have a computerControlled paddle
	// 3. instructed by player or AI don't matter, in any case a request is
	// passed or not
	m_requestedMoveDistance.x = ( 0.f );
	m_requestedMoveDistance.y = ( 0.f );

	// TODO add a meaning ful enum here
	switch ( dir ) {
		case Direction::LEFT:
			// move left requested. validate & action (if legal!)
			m_requestedMoveDistance.x = C_PADDLE_MOVSTEP * -1.f;
			valAndActionMove( res, dir, leftBarRE, rightBarLE );
			break;
		case Direction::RIGHT:
			// move right requested. validate & action (if legal!)
			m_requestedMoveDistance.x = C_PADDLE_MOVSTEP;
			valAndActionMove( res, dir, leftBarRE, rightBarLE );
			break;
		case Direction::NONE:
		default:
			// no movement
			break;
	}
}

void Paddle::valAndActionMove( sf::Vector2f res, Direction dir, float leftBarRE
	, float rightBarLE ) {
	DASSERT( ( dir == Direction::LEFT || dir == Direction::RIGHT )
		, "dir can be LEFT or RIGHT!\n" );
	if ( dir == Direction::LEFT ) {
		if ( ( getX() - ( C_PADDLE_W / 2 ) ) > leftBarRE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::RIGHT ) {
		if ( getRight() < rightBarLE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	}
}

float Paddle::getX() const noexcept { return m_sprite.getPosition().x; }

float Paddle::getY() const noexcept { return m_sprite.getPosition().y; }

float Paddle::getTop() const noexcept { return getY() - ( C_PADDLE_H / 2.f ); }

float Paddle::getBottom() const noexcept {
	return getY() + ( C_PADDLE_H / 2.f );
}

float Paddle::getLeft() const noexcept { return getX() - ( C_PADDLE_W / 2.f ); }

float Paddle::getRight() const noexcept {
	return getX() + ( C_PADDLE_W / 2.f );
}

// ===================================80 chars==================================
/* EOF */


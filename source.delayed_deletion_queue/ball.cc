/* ball.cc */
// ===================================80 chars==================================

#include "ball.h"

// TODO remove extern Settings & pass ballSpeed as a function parameter
extern std::unique_ptr <Settings> SETTINGS;

Ball::Ball()
	: m_myObjNameStr( "Ball" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif

	// SET UP SPRITE
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( 0, 0, C_BALL_W, C_BALL_H ) );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( C_BALL_W / 2.f, C_BALL_H / 2.f );
	m_sprite.setPosition( 0, 0 );
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;

	// LOAD SOUND
	if ( !m_sbuffCol.loadFromFile( "assets/sounds/collision1.wav" ) ) {
		exit( EXIT_FAILURE );
	}
	m_soundCol.setBuffer( m_sbuffCol );
}

Ball::~Ball()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Ball::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
	// calculate next step
	sf::Vector2f	moveDistance;
	moveDistance.x = ( m_velocity.x * SETTINGS->ballSpeed ) *
		timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( m_velocity.y * SETTINGS->ballSpeed ) *
		timeSinceLastUpdate.asMilliseconds();

	// 'normal' values go as high as 4.8
	float		CLAMPMAXVALPOS = 5.f;
	float		CLAMPMAXVALNEG = -5.f;
	// clamp X
	if ( moveDistance.x > CLAMPMAXVALPOS ) {
		// #if defined DBG
		// std::cout << "move distance.x was " << moveDistance.x <<
		// " clamping to " << CLAMPMAXVALPOS << " // " << m_myObjNameStr
		// <<
		// "\n";
		// #endif
		moveDistance.x = CLAMPMAXVALPOS;
	} else if ( moveDistance.x < CLAMPMAXVALNEG ) {
		// #if defined DBG
		// std::cout << "move distance.x was " << moveDistance.x <<
		// " clamping to " << CLAMPMAXVALNEG << " // " << m_myObjNameStr
		// <<
		// "\n";
		// #endif
		moveDistance.x = CLAMPMAXVALNEG;
	}
	// clamp Y
	if ( moveDistance.y > CLAMPMAXVALPOS ) {
		// #if defined DBG
		// std::cout << "move distance.y was " << moveDistance.y <<
		// " clamping to " << CLAMPMAXVALPOS << " // " << m_myObjNameStr
		// <<
		// "\n";
		// #endif
		moveDistance.y = CLAMPMAXVALPOS;
	} else if ( moveDistance.y < CLAMPMAXVALNEG ) {
		// #if defined DBG
		// std::cout << "move distance.y was " << moveDistance.y <<
		// " clamping to " << CLAMPMAXVALNEG << " // " << m_myObjNameStr
		// <<
		// "\n";
		// #endif
		moveDistance.y = CLAMPMAXVALNEG;
	}

	// Now, we can move.
	m_sprite.move( moveDistance );

	// #if defined DBG
	// std::cout << "Ball curPos: " << m_sprite.getPosition().x << ","	<<
	// m_sprite.getPosition().y << "\tBall vel: " << m_velocity.x << "," <<
	// m_velocity.y << "\n";
	// #endif
}

void Ball::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	// draw will be done by Arena
}

void Ball::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " << "newRound(" <<
	res.x << "," << res.y << ") has been triggered.\n";
	#endif
	// place the object for new round -- ball goes to the centre
	m_sprite.setPosition( res.x / 2.f, res.y * 0.75f );
	throwRandomly( res );
}

float Ball::getX() const noexcept { return m_sprite.getPosition().x; }

float Ball::getY() const noexcept { return m_sprite.getPosition().y; }

float Ball::getTop() const noexcept { return getY() - ( C_BALL_H / 2.f ); }

float Ball::getBottom() const noexcept { return getY() + ( C_BALL_H / 2.f ); }

// float Ball::getLeft() const noexcept { return getX() - (C_BALL_W / 2.f); }
// float Ball::getRight() const noexcept { return getX() + (C_BALL_W / 2.f); }

void Ball::throwRandomly( sf::Vector2f res ) {
	// calculate new ball velocity
	sf::Vector2f				ballNewVel;
	// to be randomly chosen
	float					throwTargetX = 0;
	// static for now
	float					throwTargetY = 0;

	// throw upwards but randomize destinationX
	std::mt19937				mt1;
	auto					seed1 =
		std::chrono::high_resolution_clock::now().time_since_epoch().
		count();
	mt1.seed( ( unsigned long )seed1 );
	std::uniform_real_distribution <>	dist1( 0, res.x );
	throwTargetX = dist1( mt1 );
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"randomly chosen throwTarget is: " << throwTargetX << "," <<
	throwTargetY << "\n";
	#endif

	// calculate new velocity from currentPosition to destinationPosition
	// std::cout << m_sprite.getPosition().y << "\n\n\n";
	ballNewVel.x = throwTargetX - m_sprite.getPosition().x;
	ballNewVel.y = throwTargetY - m_sprite.getPosition().y;

	// normalize the velocity vector & assign it to the object
	sf::Vector2f ballNewVelNormalized = normalize( ballNewVel );
	m_velocity = ballNewVelNormalized;

	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"ballNewVelNormalized is: " << ballNewVelNormalized.x << "," <<
	ballNewVelNormalized.y << "\n";
	#endif
}

// ===================================80 chars==================================
/* EOF */


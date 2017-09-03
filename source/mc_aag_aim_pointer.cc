/* mc_aag_aim_pointer.cc */
// ===================================80 chars==================================

#include "mc_aag_aim_pointer.h"

// TODO use JSON & remove these
#define MC_AAG_POINTER_W 40
#define MC_AAG_POINTER_H MC_AAG_POINTER_W
#define MC_AAG_POINTER_V 1

AAGAimPointer::AAGAimPointer()
	: m_myObjNameStr( "AAGAimPointer" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
	// SET UP SPRITE
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( 0, 0, MC_AAG_POINTER_W
			, MC_AAG_POINTER_H ) );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( MC_AAG_POINTER_W / 2.f, MC_AAG_POINTER_H / 2.f );
	m_sprite.setPosition( 0, 0 );
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}

AAGAimPointer::~AAGAimPointer()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void AAGAimPointer::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
	// calculate next step
	sf::Vector2f	moveDistance;
	moveDistance.x = ( m_velocity.x * MC_AAG_POINTER_V ) *
		timeSinceLastUpdate.asMilliseconds();
	moveDistance.y = ( m_velocity.y * MC_AAG_POINTER_V ) *
		timeSinceLastUpdate.asMilliseconds();

	// 'normal' values go as low|high as N
	float		CLAMPMAXVALPOS = 5.f;
	float		CLAMPMAXVALNEG = -5.f;
	// clamp X
	if ( moveDistance.x > CLAMPMAXVALPOS ) {
		moveDistance.x = CLAMPMAXVALPOS;
	} else if ( moveDistance.x < CLAMPMAXVALNEG ) {
		moveDistance.x = CLAMPMAXVALNEG;
	}
	// clamp Y
	if ( moveDistance.y > CLAMPMAXVALPOS ) {
		moveDistance.y = CLAMPMAXVALPOS;
	} else if ( moveDistance.y < CLAMPMAXVALNEG ) {
		moveDistance.y = CLAMPMAXVALNEG;
	}

	// Now, we can move.
	m_sprite.move( moveDistance );
}

void AAGAimPointer::draw( sf::RenderTarget &target, sf::RenderStates states )
const {
	// draw to be done by Arena
}

void AAGAimPointer::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " << "newRound(" <<
	res.x << "," << res.y << ") has been triggered.\n";
	#endif
	// place the object for new round -- ball goes to the centre
	m_sprite.setPosition( res.x / 2.f, res.y * 0.75f );
}

float AAGAimPointer::getX() const noexcept {
	return m_sprite.getPosition().x;
}

float AAGAimPointer::getY() const noexcept {
	return m_sprite.getPosition().y;
}

float AAGAimPointer::getTop() const noexcept {
	return getY() - (
		MC_AAG_POINTER_H / 2.f );
}

float AAGAimPointer::getBottom() const noexcept {
	return getY() + (
		MC_AAG_POINTER_H / 2.f );
}

float AAGAimPointer::getLeft() const noexcept {
	return getX() - ( MC_AAG_POINTER_W / 2.f );
}

float AAGAimPointer::getRight() const noexcept {
	return getX() + ( MC_AAG_POINTER_W / 2.f );
}

// ===================================80 chars==================================
/* EOF */


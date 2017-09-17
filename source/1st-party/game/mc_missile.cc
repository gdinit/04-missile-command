/* mc_missile.cc */
// ===================================80 chars=================================|

#include "mc_missile.h"

// TODO -- CHANGE ME TO JSON
// "missileW": 9,
// "missileH": 14,
// "missileV": 5,

// TODO -- CHANGE ME TO JSON
#define MC_CONS_MISSILE_W 9
#define MC_CONS_MISSILE_H 14
#define MC_CONS_MISSILE_V 5

Missile::Missile()
	: m_myObjNameStr( "Unnamed Missile" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

Missile::Missile( t_objectName name )
	: m_myObjNameStr( name )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

Missile::~Missile()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Missile::update( sf::Time timeSinceLastUpdate )
{
	std::cout << "a missile is now updating 1 2 3...\n";
}

void Missile::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
	// std::cout << "a missile is now updating...\tmyPos = " << getX() <<
	// "," << getY() << "\n";
}

void Missile::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target.draw( m_sprite );
}

void Missile::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	m_texture.loadFromFile( "assets/textures/missile_9x14.png" );
	m_sprite.setTexture( m_texture );

	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
		if ( it.key() == "missileL1XPosRatio" ) {
			PDASSERT( it.value() > 0
				, "missileL1XPosRatio must be > 0\t It is: " <<
				it.value() << "\n" );
			m_missileL1XPosRatio = it.value();
		} else if ( it.key() == "missileL1YPosRatio" ) {
			m_missileL1YPosRatio = it.value();
		} else if ( it.key() == "missileL2XPosRatio" ) {
			m_missileL2XPosRatio = it.value();
		} else if ( it.key() == "missileL2YPosRatio" ) {
			m_missileL2YPosRatio = it.value();
		}
	}
	i.close();

	if ( m_myObjNameStr == "missileL1" ) {
		m_sprite.setPosition( res.x * m_missileL1XPosRatio
			, res.y * m_missileL1YPosRatio );
	} else if ( m_myObjNameStr == "missileL2" ) {
		m_sprite.setPosition( res.x * m_missileL2XPosRatio
			, res.y * m_missileL2YPosRatio );
		// m_sprite.setPosition( res.x * m_city3XPosRatio
		// , res.y * m_city3YPosRatio );
		// } else if ( m_myObjNameStr == "city4" ) {
		// m_sprite.setPosition( res.x * m_city4XPosRatio
		// , res.y * m_city4YPosRatio );
		// } else if ( m_myObjNameStr == "city5" ) {
		// m_sprite.setPosition( res.x * m_city5XPosRatio
		// , res.y * m_city5YPosRatio );
		// } else if ( m_myObjNameStr == "city6" ) {
		// m_sprite.setPosition( res.x * m_city6XPosRatio
		// , res.y * m_city6YPosRatio );
	}
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

float Missile::getX() const noexcept { return m_sprite.getPosition().x; }

float Missile::getY() const noexcept { return m_sprite.getPosition().y; }

float Missile::getTop() const noexcept {
	return getY() - ( MC_CONS_MISSILE_H / 2.f );
}

float Missile::getBottom() const noexcept {
	return getY() + ( MC_CONS_MISSILE_H / 2.f );
}

float Missile::getLeft() const noexcept {
	return getX();
}

float Missile::getRight() const noexcept {
	// TODO FIXME

	// return getX() + m_width;
	return 0;
}

// ===================================80 chars=================================|
/* EOF */


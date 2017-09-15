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
	std::cout << "a missile is now updating...\n";
	std::cout << "myPos = " << getX() << "," << getY() <<
	" a missile is now updating...\n";
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
		if ( it.key() == "missileL1XPosRatiho" ) {
			m_missileL1XPosRatio = it.value();
		} else if ( it.key() == "missileL1YPosRatio" ) {
			m_missileL1YPosRatio = it.value();
			// } else if ( it.key() == "city2XPosRatio" ) {
			// m_city2XPosRatio = it.value();
			// } else if ( it.key() == "city2YPosRatio" ) {
			// m_city2YPosRatio = it.value();
			// } else if ( it.key() == "city3XPosRatio" ) {
			// m_city3XPosRatio = it.value();
			// } else if ( it.key() == "city3YPosRatio" ) {
			// m_city3YPosRatio = it.value();
			// } else if ( it.key() == "city4XPosRatio" ) {
			// m_city4XPosRatio = it.value();
			// } else if ( it.key() == "city4YPosRatio" ) {
			// m_city4YPosRatio = it.value();
			// } else if ( it.key() == "city5XPosRatio" ) {
			// m_city5XPosRatio = it.value();
			// } else if ( it.key() == "city5YPosRatio" ) {
			// m_city5YPosRatio = it.value();
			// } else if ( it.key() == "city6XPosRatio" ) {
			// m_city6XPosRatio = it.value();
			// } else if ( it.key() == "city6YPosRatio" ) {
			// m_city6YPosRatio = it.value();
		}
	}
	i.close();

	if ( m_myObjNameStr == "missileL1" ) {
		m_sprite.setPosition( res.x * m_missileL1XPosRatio + 65
			, res.y * m_missileL1YPosRatio );
		// } else if ( m_myObjNameStr == "city2" ) {
		// m_sprite.setPosition( res.x * m_city2XPosRatio
		// , res.y * m_city2YPosRatio );
		// } else if ( m_myObjNameStr == "city3" ) {
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


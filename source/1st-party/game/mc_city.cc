/* mc_city.cc */
// ===================================80 chars=================================|

#include "mc_city.h"

City::City()
	: m_myObjNameStr( "Unnamed City" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

// TODO	color also should be passed while creating
City::City( t_objectName name )
	: m_myObjNameStr( name )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

City::~City()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void City::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
}

void City::draw( sf::RenderTarget &target, sf::RenderStates
	states ) const {
	target.draw( m_sprite );
}

void City::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	// m_texture.loadFromFile( "assets/textures/45x26_city.png" );
	m_texture.loadFromFile( "assets/textures/city_blue_42x24.png" );
	m_sprite.setTexture( m_texture );

	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
		if ( it.key() == "city1XPosRatio" ) {
			m_city1XPosRatio = it.value();
		} else if ( it.key() == "city1YPosRatio" ) {
			m_city1YPosRatio = it.value();
		} else if ( it.key() == "city2XPosRatio" ) {
			m_city2XPosRatio = it.value();
		} else if ( it.key() == "city2YPosRatio" ) {
			m_city2YPosRatio = it.value();
		} else if ( it.key() == "city3XPosRatio" ) {
			m_city3XPosRatio = it.value();
		} else if ( it.key() == "city3YPosRatio" ) {
			m_city3YPosRatio = it.value();
		} else if ( it.key() == "city4XPosRatio" ) {
			m_city4XPosRatio = it.value();
		} else if ( it.key() == "city4YPosRatio" ) {
			m_city4YPosRatio = it.value();
		} else if ( it.key() == "city5XPosRatio" ) {
			m_city5XPosRatio = it.value();
		} else if ( it.key() == "city5YPosRatio" ) {
			m_city5YPosRatio = it.value();
		} else if ( it.key() == "city6XPosRatio" ) {
			m_city6XPosRatio = it.value();
		} else if ( it.key() == "city6YPosRatio" ) {
			m_city6YPosRatio = it.value();
		}
	}
	i.close();

	if ( m_myObjNameStr == "city1" ) {
		m_sprite.setPosition( res.x * m_city1XPosRatio
			, res.y * m_city1YPosRatio );
	} else if ( m_myObjNameStr == "city2" ) {
		m_sprite.setPosition( res.x * m_city2XPosRatio
			, res.y * m_city2YPosRatio );
	} else if ( m_myObjNameStr == "city3" ) {
		m_sprite.setPosition( res.x * m_city3XPosRatio
			, res.y * m_city3YPosRatio );
	} else if ( m_myObjNameStr == "city4" ) {
		m_sprite.setPosition( res.x * m_city4XPosRatio
			, res.y * m_city4YPosRatio );
	} else if ( m_myObjNameStr == "city5" ) {
		m_sprite.setPosition( res.x * m_city5XPosRatio
			, res.y * m_city5YPosRatio );
	} else if ( m_myObjNameStr == "city6" ) {
		m_sprite.setPosition( res.x * m_city6XPosRatio
			, res.y * m_city6YPosRatio );
	}
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

float City::getX() const noexcept { return m_sprite.getPosition().x; }

float City::getY() const noexcept { return m_sprite.getPosition().y; }

float City::getTop() const noexcept {
	return getY() - ( MC_CONS_CITY_H / 2.f );
}

float City::getBottom() const noexcept {
	return getY() + ( MC_CONS_CITY_H / 2.f );
}

float City::getLeft() const noexcept {
	return getX();
}

float City::getRight() const noexcept {
	// TODO fix this

	// return getX() + m_width;
	return 0;
}

// ===================================80 chars=================================|
/* EOF */


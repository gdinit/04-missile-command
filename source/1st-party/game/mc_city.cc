/* mc_city.cc */
// ===================================80 chars==================================

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
	if ( m_myObjNameStr == "city1" ) {
		m_sprite.setPosition( res.x * 0.15320, res.y * 0.826667 );
	} else if ( m_myObjNameStr == "city2" ) {
		m_sprite.setPosition( res.x * 0.25, res.y * 0.824167 );
	} else if ( m_myObjNameStr == "city3" ) {
		m_sprite.setPosition( res.x * 0.351125, res.y * 0.835 );
	} else if ( m_myObjNameStr == "city4" ) {
		m_sprite.setPosition( res.x * 0.546875, res.y * 0.822167 );
	} else if ( m_myObjNameStr == "city5" ) {
		m_sprite.setPosition( res.x * 0.6675, res.y * 0.811333 );
	} else if ( m_myObjNameStr == "city6" ) {
		m_sprite.setPosition( res.x * 0.7875, res.y * 0.829167 );
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

	// return getX() + m_width;
	return 0;
}

// ===================================80 chars==================================
/* EOF */


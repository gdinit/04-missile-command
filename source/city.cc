/* city.cc */
// ===================================80 chars==================================

#include "city.h"

City::City()
	: m_myObjNameStr( "Unnamed City" )
	, m_width( 1.f )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

// TODO	color also should be passed while creating
City::City( t_objectName name )
	: m_myObjNameStr( name )
	, m_width( 1.f )
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

// called as:
// leftCity.draw(target, sf::RenderStates::Default);
void City::draw( sf::RenderTarget &target, sf::RenderStates
	states ) const {
	target.draw( m_sprite );
}

void City::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	// int32	posL = 100;
	// int32	posT = 100;
	// int32	sizeW = 45;
	// int32	sizeH = 26;
	if ( m_myObjNameStr == "leftCity" ) {
		m_texture.loadFromFile( "assets/textures/45x26_city.png" );
		m_sprite.setTexture( m_texture );
		m_sprite.setPosition( ( res.x / 5 ) * 1, ( res.y / 10 ) * 8 );
	} else if ( m_myObjNameStr == "middleCity" ) {
		m_texture.loadFromFile( "assets/textures/45x26_city.png" );
		m_sprite.setTexture( m_texture );
		m_sprite.setPosition( ( res.x / 5 ) * 3, ( res.y / 10 ) * 7.5 );
	} else if ( m_myObjNameStr == "rightCity" ) {
		m_texture.loadFromFile( "assets/textures/45x26_city.png" );
		m_sprite.setTexture( m_texture );
		m_sprite.setPosition( ( res.x / 5 ) * 3.8, ( res.y / 10 ) * 8 );
	}
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;

	// REMOVE THIS /////////////////////////////////////////////////////////
	// m_width = sizeW;
	// #if defined DBG
	// std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
	// "\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
	// m_myObjNameStr << "\n";
	// #endif
	// } else if ( m_myObjNameStr == "middleCity" ) {
	// m_width = sizeW;
	// #if defined DBG
	// std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
	// "\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
	// m_myObjNameStr << "\n";
	// #endif
	// } else if ( m_myObjNameStr == "rightCity" ) {
	// m_width = sizeW;
	// #if defined DBG
	// std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
	// "\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
	// m_myObjNameStr << "\n";
	// #endif
	// }
	// #if defined DBG
	// std::cout << "[DEBUG]\tCalculated position as: " << posL << "," <<
	// posT << "\n" <<	"[DEBUG]\tCalculated " << m_myObjNameStr <<
	// " size as: " << sizeW << "," << sizeH << "\n";
	// #endif
	// REMOVE THIS /////////////////////////////////////////////////////////
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
	return getX() + m_width;
}

// ===================================80 chars==================================
/* EOF */


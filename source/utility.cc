/* utility.cc */
// ===================================80 chars==================================

#include "utility.h"

void centerOrigin( sf::Text &text )
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin( std::floor( bounds.left + bounds.width / 2.f )
		, std::floor( bounds.top + bounds.height / 2.f ) );
}

// find length (or Magnitude)
float magnitude( sf::Vector2f v )
{
	return std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) );
}

int magnitude( int x, int y )
{
	return( std::sqrt( x * x + y * y ) );
}

float magnitude( float x, float y )
{
	return( std::sqrt( x * x + y * y ) );
}

int magnitudeSquared( int x, int y )
{
	return( x * x + y * y );
}

float magnitudeSquared( float x, float y )
{
	return( x * x + y * y );
}

sf::Vector2f normalize( sf::Vector2f v )
{
	float length = std::sqrt( ( v.x * v.x ) + ( v.y * v.y ) );
	if ( length != 0 ) {
		return sf::Vector2f( v.x / length, v.y / length );
	} else {
		return v;
	}
}

// ===================================80 chars==================================
/* EOF */


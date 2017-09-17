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
		} else if ( it.key() == "missileL3XPosRatio" ) {
			m_missileL3XPosRatio = it.value();
		} else if ( it.key() == "missileL3YPosRatio" ) {
			m_missileL3YPosRatio = it.value();
		} else if ( it.key() == "missileL4XPosRatio" ) {
			m_missileL4XPosRatio = it.value();
		} else if ( it.key() == "missileL4YPosRatio" ) {
			m_missileL4YPosRatio = it.value();
		} else if ( it.key() == "missileL5XPosRatio" ) {
			m_missileL5XPosRatio = it.value();
		} else if ( it.key() == "missileL5YPosRatio" ) {
			m_missileL5YPosRatio = it.value();
		} else if ( it.key() == "missileL6XPosRatio" ) {
			m_missileL6XPosRatio = it.value();
		} else if ( it.key() == "missileL6YPosRatio" ) {
			m_missileL6YPosRatio = it.value();
		} else if ( it.key() == "missileL7XPosRatio" ) {
			m_missileL7XPosRatio = it.value();
		} else if ( it.key() == "missileL7YPosRatio" ) {
			m_missileL7YPosRatio = it.value();
		} else if ( it.key() == "missileL8XPosRatio" ) {
			m_missileL8XPosRatio = it.value();
		} else if ( it.key() == "missileL8YPosRatio" ) {
			m_missileL8YPosRatio = it.value();
		} else if ( it.key() == "missileL9XPosRatio" ) {
			m_missileL9XPosRatio = it.value();
		} else if ( it.key() == "missileL9YPosRatio" ) {
			m_missileL9YPosRatio = it.value();
		} else if ( it.key() == "missileL0XPosRatio" ) {
			m_missileL0XPosRatio = it.value();
		} else if ( it.key() == "missileL0YPosRatio" ) {
			m_missileL0YPosRatio = it.value();
		} else if ( it.key() == "missileC1XPosRatio" ) {
			m_missileC1XPosRatio = it.value();
		} else if ( it.key() == "missileC1YPosRatio" ) {
			m_missileC1YPosRatio = it.value();
		} else if ( it.key() == "missileC2XPosRatio" ) {
			m_missileC2XPosRatio = it.value();
		} else if ( it.key() == "missileC2YPosRatio" ) {
			m_missileC2YPosRatio = it.value();
		} else if ( it.key() == "missileC3XPosRatio" ) {
			m_missileC3XPosRatio = it.value();
		} else if ( it.key() == "missileC3YPosRatio" ) {
			m_missileC3YPosRatio = it.value();
		} else if ( it.key() == "missileC4XPosRatio" ) {
			m_missileC4XPosRatio = it.value();
		} else if ( it.key() == "missileC4YPosRatio" ) {
			m_missileC4YPosRatio = it.value();
		} else if ( it.key() == "missileC5XPosRatio" ) {
			m_missileC5XPosRatio = it.value();
		} else if ( it.key() == "missileC5YPosRatio" ) {
			m_missileC5YPosRatio = it.value();
		} else if ( it.key() == "missileC6XPosRatio" ) {
			m_missileC6XPosRatio = it.value();
		} else if ( it.key() == "missileC6YPosRatio" ) {
			m_missileC6YPosRatio = it.value();
		} else if ( it.key() == "missileC7XPosRatio" ) {
			m_missileC7XPosRatio = it.value();
		} else if ( it.key() == "missileC7YPosRatio" ) {
			m_missileC7YPosRatio = it.value();
		} else if ( it.key() == "missileC8XPosRatio" ) {
			m_missileC8XPosRatio = it.value();
		} else if ( it.key() == "missileC8YPosRatio" ) {
			m_missileC8YPosRatio = it.value();
		} else if ( it.key() == "missileC9XPosRatio" ) {
			m_missileC9XPosRatio = it.value();
		} else if ( it.key() == "missileC9YPosRatio" ) {
			m_missileC9YPosRatio = it.value();
		} else if ( it.key() == "missileC0XPosRatio" ) {
			m_missileC0XPosRatio = it.value();
		} else if ( it.key() == "missileC0YPosRatio" ) {
			m_missileC0YPosRatio = it.value();
		} else if ( it.key() == "missileR1XPosRatio" ) {
			m_missileR1XPosRatio = it.value();
		} else if ( it.key() == "missileR1YPosRatio" ) {
			m_missileR1YPosRatio = it.value();
		} else if ( it.key() == "missileR2XPosRatio" ) {
			m_missileR2XPosRatio = it.value();
		} else if ( it.key() == "missileR2YPosRatio" ) {
			m_missileR2YPosRatio = it.value();
		} else if ( it.key() == "missileR3XPosRatio" ) {
			m_missileR3XPosRatio = it.value();
		} else if ( it.key() == "missileR3YPosRatio" ) {
			m_missileR3YPosRatio = it.value();
		} else if ( it.key() == "missileR4XPosRatio" ) {
			m_missileR4XPosRatio = it.value();
		} else if ( it.key() == "missileR4YPosRatio" ) {
			m_missileR4YPosRatio = it.value();
		} else if ( it.key() == "missileR5XPosRatio" ) {
			m_missileR5XPosRatio = it.value();
		} else if ( it.key() == "missileR5YPosRatio" ) {
			m_missileR5YPosRatio = it.value();
		} else if ( it.key() == "missileR6XPosRatio" ) {
			m_missileR6XPosRatio = it.value();
		} else if ( it.key() == "missileR6YPosRatio" ) {
			m_missileR6YPosRatio = it.value();
		} else if ( it.key() == "missileR7XPosRatio" ) {
			m_missileR7XPosRatio = it.value();
		} else if ( it.key() == "missileR7YPosRatio" ) {
			m_missileR7YPosRatio = it.value();
		} else if ( it.key() == "missileR8XPosRatio" ) {
			m_missileR8XPosRatio = it.value();
		} else if ( it.key() == "missileR8YPosRatio" ) {
			m_missileR8YPosRatio = it.value();
		} else if ( it.key() == "missileR9XPosRatio" ) {
			m_missileR9XPosRatio = it.value();
		} else if ( it.key() == "missileR9YPosRatio" ) {
			m_missileR9YPosRatio = it.value();
		} else if ( it.key() == "missileR0XPosRatio" ) {
			m_missileR0XPosRatio = it.value();
		} else if ( it.key() == "missileR0YPosRatio" ) {
			m_missileR0YPosRatio = it.value();
		}
	}
	i.close();

	if ( m_myObjNameStr == "missileL1" ) {
		m_sprite.setPosition( res.x * m_missileL1XPosRatio, res.y *
			m_missileL1YPosRatio );
	} else if ( m_myObjNameStr == "missileL2" ) {
		m_sprite.setPosition( res.x * m_missileL2XPosRatio, res.y *
			m_missileL2YPosRatio );
	} else if ( m_myObjNameStr == "missileL3" ) {
		m_sprite.setPosition( res.x * m_missileL3XPosRatio, res.y *
			m_missileL3YPosRatio );
	} else if ( m_myObjNameStr == "missileL4" ) {
		m_sprite.setPosition( res.x * m_missileL4XPosRatio, res.y *
			m_missileL4YPosRatio );
	} else if ( m_myObjNameStr == "missileL5" ) {
		m_sprite.setPosition( res.x * m_missileL5XPosRatio, res.y *
			m_missileL5YPosRatio );
	} else if ( m_myObjNameStr == "missileL6" ) {
		m_sprite.setPosition( res.x * m_missileL6XPosRatio, res.y *
			m_missileL6YPosRatio );
	} else if ( m_myObjNameStr == "missileL7" ) {
		m_sprite.setPosition( res.x * m_missileL7XPosRatio, res.y *
			m_missileL7YPosRatio );
	} else if ( m_myObjNameStr == "missileL8" ) {
		m_sprite.setPosition( res.x * m_missileL8XPosRatio, res.y *
			m_missileL8YPosRatio );
	} else if ( m_myObjNameStr == "missileL9" ) {
		m_sprite.setPosition( res.x * m_missileL9XPosRatio, res.y *
			m_missileL9YPosRatio );
	} else if ( m_myObjNameStr == "missileL0" ) {
		m_sprite.setPosition( res.x * m_missileL0XPosRatio, res.y *
			m_missileL0YPosRatio );
	} else if ( m_myObjNameStr == "missileC1" ) {
		m_sprite.setPosition( res.x * m_missileC1XPosRatio, res.y *
			m_missileC1YPosRatio );
	} else if ( m_myObjNameStr == "missileC2" ) {
		m_sprite.setPosition( res.x * m_missileC2XPosRatio, res.y *
			m_missileC2YPosRatio );
	} else if ( m_myObjNameStr == "missileC3" ) {
		m_sprite.setPosition( res.x * m_missileC3XPosRatio, res.y *
			m_missileC3YPosRatio );
	} else if ( m_myObjNameStr == "missileC4" ) {
		m_sprite.setPosition( res.x * m_missileC4XPosRatio, res.y *
			m_missileC4YPosRatio );
	} else if ( m_myObjNameStr == "missileC5" ) {
		m_sprite.setPosition( res.x * m_missileC5XPosRatio, res.y *
			m_missileC5YPosRatio );
	} else if ( m_myObjNameStr == "missileC6" ) {
		m_sprite.setPosition( res.x * m_missileC6XPosRatio, res.y *
			m_missileC6YPosRatio );
	} else if ( m_myObjNameStr == "missileC7" ) {
		m_sprite.setPosition( res.x * m_missileC7XPosRatio, res.y *
			m_missileC7YPosRatio );
	} else if ( m_myObjNameStr == "missileC8" ) {
		m_sprite.setPosition( res.x * m_missileC8XPosRatio, res.y *
			m_missileC8YPosRatio );
	} else if ( m_myObjNameStr == "missileC9" ) {
		m_sprite.setPosition( res.x * m_missileC9XPosRatio, res.y *
			m_missileC9YPosRatio );
	} else if ( m_myObjNameStr == "missileC0" ) {
		m_sprite.setPosition( res.x * m_missileC0XPosRatio, res.y *
			m_missileC0YPosRatio );
	} else if ( m_myObjNameStr == "missileR1" ) {
		m_sprite.setPosition( res.x * m_missileR1XPosRatio, res.y *
			m_missileR1YPosRatio );
	} else if ( m_myObjNameStr == "missileR2" ) {
		m_sprite.setPosition( res.x * m_missileR2XPosRatio, res.y *
			m_missileR2YPosRatio );
	} else if ( m_myObjNameStr == "missileR3" ) {
		m_sprite.setPosition( res.x * m_missileR3XPosRatio, res.y *
			m_missileR3YPosRatio );
	} else if ( m_myObjNameStr == "missileR4" ) {
		m_sprite.setPosition( res.x * m_missileR4XPosRatio, res.y *
			m_missileR4YPosRatio );
	} else if ( m_myObjNameStr == "missileR5" ) {
		m_sprite.setPosition( res.x * m_missileR5XPosRatio, res.y *
			m_missileR5YPosRatio );
	} else if ( m_myObjNameStr == "missileR6" ) {
		m_sprite.setPosition( res.x * m_missileR6XPosRatio, res.y *
			m_missileR6YPosRatio );
	} else if ( m_myObjNameStr == "missileR7" ) {
		m_sprite.setPosition( res.x * m_missileR7XPosRatio, res.y *
			m_missileR7YPosRatio );
	} else if ( m_myObjNameStr == "missileR8" ) {
		m_sprite.setPosition( res.x * m_missileR8XPosRatio, res.y *
			m_missileR8YPosRatio );
	} else if ( m_myObjNameStr == "missileR9" ) {
		m_sprite.setPosition( res.x * m_missileR9XPosRatio, res.y *
			m_missileR9YPosRatio );
	} else if ( m_myObjNameStr == "missileR0" ) {
		m_sprite.setPosition( res.x * m_missileR0XPosRatio, res.y *
			m_missileR0YPosRatio );
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


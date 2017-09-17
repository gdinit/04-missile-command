/* mc_hq_blue.cc */
// ===================================80 chars=================================|

#include "mc_hq_blue.h"

HQBlue::HQBlue()
	: m_myObjNameStr( "Unnamed HQBlue" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

HQBlue::HQBlue( t_objectName name )
	: m_myObjNameStr( name )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

HQBlue::~HQBlue()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void HQBlue::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
	city1.update( timeSinceLastUpdate, res );
	city2.update( timeSinceLastUpdate, res );
	city3.update( timeSinceLastUpdate, res );
	city4.update( timeSinceLastUpdate, res );
	city5.update( timeSinceLastUpdate, res );
	city6.update( timeSinceLastUpdate, res );
	missileL1.update( timeSinceLastUpdate, res );
	missileL2.update( timeSinceLastUpdate, res );
	missileL3.update( timeSinceLastUpdate, res );
	missileL4.update( timeSinceLastUpdate, res );
	missileL5.update( timeSinceLastUpdate, res );
	missileL6.update( timeSinceLastUpdate, res );
	missileL7.update( timeSinceLastUpdate, res );
	missileL8.update( timeSinceLastUpdate, res );
	missileL9.update( timeSinceLastUpdate, res );
	missileL0.update( timeSinceLastUpdate, res );
}

void HQBlue::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	city1.draw( target, sf::RenderStates::Default );
	city2.draw( target, sf::RenderStates::Default );
	city3.draw( target, sf::RenderStates::Default );
	city4.draw( target, sf::RenderStates::Default );
	city5.draw( target, sf::RenderStates::Default );
	city6.draw( target, sf::RenderStates::Default );
	missileL1.draw( target, sf::RenderStates::Default );
	missileL2.draw( target, sf::RenderStates::Default );
	missileL3.draw( target, sf::RenderStates::Default );
	missileL4.draw( target, sf::RenderStates::Default );
	missileL5.draw( target, sf::RenderStates::Default );
	missileL6.draw( target, sf::RenderStates::Default );
	missileL7.draw( target, sf::RenderStates::Default );
	missileL8.draw( target, sf::RenderStates::Default );
	missileL9.draw( target, sf::RenderStates::Default );
	missileL0.draw( target, sf::RenderStates::Default );
}

void HQBlue::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	city1.newRound( res );
	city2.newRound( res );
	city3.newRound( res );
	city4.newRound( res );
	city5.newRound( res );
	city6.newRound( res );
	missileL1.newRound( res );
	missileL2.newRound( res );
	missileL3.newRound( res );
	missileL4.newRound( res );
	missileL5.newRound( res );
	missileL6.newRound( res );
	missileL7.newRound( res );
	missileL8.newRound( res );
	missileL9.newRound( res );
	missileL0.newRound( res );

	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

// ===================================80 chars=================================|
/* EOF */


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
	missileC1.update( timeSinceLastUpdate, res );
	missileC2.update( timeSinceLastUpdate, res );
	missileC3.update( timeSinceLastUpdate, res );
	missileC4.update( timeSinceLastUpdate, res );
	missileC5.update( timeSinceLastUpdate, res );
	missileC6.update( timeSinceLastUpdate, res );
	missileC7.update( timeSinceLastUpdate, res );
	missileC8.update( timeSinceLastUpdate, res );
	missileC9.update( timeSinceLastUpdate, res );
	missileC0.update( timeSinceLastUpdate, res );
	missileR1.update( timeSinceLastUpdate, res );
	missileR2.update( timeSinceLastUpdate, res );
	missileR3.update( timeSinceLastUpdate, res );
	missileR4.update( timeSinceLastUpdate, res );
	missileR5.update( timeSinceLastUpdate, res );
	missileR6.update( timeSinceLastUpdate, res );
	missileR7.update( timeSinceLastUpdate, res );
	missileR8.update( timeSinceLastUpdate, res );
	missileR9.update( timeSinceLastUpdate, res );
	missileR0.update( timeSinceLastUpdate, res );
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
	missileC1.draw( target, sf::RenderStates::Default );
	missileC2.draw( target, sf::RenderStates::Default );
	missileC3.draw( target, sf::RenderStates::Default );
	missileC4.draw( target, sf::RenderStates::Default );
	missileC5.draw( target, sf::RenderStates::Default );
	missileC6.draw( target, sf::RenderStates::Default );
	missileC7.draw( target, sf::RenderStates::Default );
	missileC8.draw( target, sf::RenderStates::Default );
	missileC9.draw( target, sf::RenderStates::Default );
	missileC0.draw( target, sf::RenderStates::Default );
	missileR1.draw( target, sf::RenderStates::Default );
	missileR2.draw( target, sf::RenderStates::Default );
	missileR3.draw( target, sf::RenderStates::Default );
	missileR4.draw( target, sf::RenderStates::Default );
	missileR5.draw( target, sf::RenderStates::Default );
	missileR6.draw( target, sf::RenderStates::Default );
	missileR7.draw( target, sf::RenderStates::Default );
	missileR8.draw( target, sf::RenderStates::Default );
	missileR9.draw( target, sf::RenderStates::Default );
	missileR0.draw( target, sf::RenderStates::Default );
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
	missileC1.newRound( res );
	missileC2.newRound( res );
	missileC3.newRound( res );
	missileC4.newRound( res );
	missileC5.newRound( res );
	missileC6.newRound( res );
	missileC7.newRound( res );
	missileC8.newRound( res );
	missileC9.newRound( res );
	missileC0.newRound( res );
	missileR1.newRound( res );
	missileR2.newRound( res );
	missileR3.newRound( res );
	missileR4.newRound( res );
	missileR5.newRound( res );
	missileR6.newRound( res );
	missileR7.newRound( res );
	missileR8.newRound( res );
	missileR9.newRound( res );
	missileR0.newRound( res );

	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

// ===================================80 chars=================================|
/* EOF */


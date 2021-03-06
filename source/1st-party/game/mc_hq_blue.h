/* mc_hq_blue.h */
// ===================================80 chars=================================|

#ifndef MC_HQ_BLUE_H
#define MC_HQ_BLUE_H

#include "en_essentials.h"
#include "mc_city.h"
#include "mc_missile.h"

#include <SFML/Graphics.hpp>

// For object name
#include <string>
// TODO remove this -- Required for debugging for now
#include <iostream>

class HQBlue : public sf::Transformable, public sf::Drawable
	, private sf::NonCopyable
{
public:
	HQBlue();
	HQBlue( t_objectName name );
	virtual ~HQBlue();
	void		update( sf::Time timeSinceLastUpdate );
	void		update( sf::Time timeSinceLastUpdate
	, sf::Vector2f res );
	virtual void	draw( sf::RenderTarget &target
	, sf::RenderStates states ) const;
	void		newRound( sf::Vector2f res );

protected:

private:
	const t_objectName	m_myObjNameStr;
	sf::Vector2u		m_windowSize = { 0, 0 };
	City			city1 = { "city1" };
	City			city2 = { "city2" };
	City			city3 = { "city3" };
	City			city4 = { "city4" };
	City			city5 = { "city5" };
	City			city6 = { "city6" };
	Missile			missileL1 = { "missileL1" };
	Missile			missileL2 = { "missileL2" };
	Missile			missileL3 = { "missileL3" };
	Missile			missileL4 = { "missileL4" };
	Missile			missileL5 = { "missileL5" };
	Missile			missileL6 = { "missileL6" };
	Missile			missileL7 = { "missileL7" };
	Missile			missileL8 = { "missileL8" };
	Missile			missileL9 = { "missileL9" };
	Missile			missileL0 = { "missileL0" };
	Missile			missileC1 = { "missileC1" };
	Missile			missileC2 = { "missileC2" };
	Missile			missileC3 = { "missileC3" };
	Missile			missileC4 = { "missileC4" };
	Missile			missileC5 = { "missileC5" };
	Missile			missileC6 = { "missileC6" };
	Missile			missileC7 = { "missileC7" };
	Missile			missileC8 = { "missileC8" };
	Missile			missileC9 = { "missileC9" };
	Missile			missileC0 = { "missileC0" };
	Missile			missileR1 = { "missileR1" };
	Missile			missileR2 = { "missileR2" };
	Missile			missileR3 = { "missileR3" };
	Missile			missileR4 = { "missileR4" };
	Missile			missileR5 = { "missileR5" };
	Missile			missileR6 = { "missileR6" };
	Missile			missileR7 = { "missileR7" };
	Missile			missileR8 = { "missileR8" };
	Missile			missileR9 = { "missileR9" };
	Missile			missileR0 = { "missileR0" };
};

// MC_HQ_BLUE_H
#endif

// ===================================80 chars=================================|
/* EOF */


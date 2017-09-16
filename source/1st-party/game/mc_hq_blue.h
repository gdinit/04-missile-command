/* mc_hq_blue.h */
// ===================================80 chars=================================|

#ifndef MC_HQ_BLUE_H
#define MC_HQ_BLUE_H

#include "en_essentials.h"

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
};

// MC_HQ_BLUE_H
#endif

// ===================================80 chars=================================|
/* EOF */


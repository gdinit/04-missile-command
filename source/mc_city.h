/* mc_city.h */
// ===================================80 chars==================================

#ifndef MC_CITY_H
#define MC_CITY_H

#include "en_essentials.h"
#include "config.h"
#include "mc_constants.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// For object name
#include <string>
// TOOD: remove this debug line
#include <iostream>

class City : public sf::Transformable
	   , public sf::Drawable
	   , private sf::NonCopyable
{
	public:
		City();
		City( t_objectName name );
		virtual ~City();
		void	update( sf::Time timeSinceLastUpdate
		, sf::Vector2f res );
		void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void	newRound( sf::Vector2f res );
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;
		float	getLeft()    const noexcept;
		float	getRight()   const noexcept;

	protected:
		friend class Arena;

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Texture		m_texture;
		sf::Vector2f		m_position;
		float			m_width;
		sf::Vector2u		m_windowSize = { 0, 0 };
};

#endif	// MC_CITY_H

// ===================================80 chars==================================
/* EOF */


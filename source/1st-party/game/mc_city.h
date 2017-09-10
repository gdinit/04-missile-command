/* mc_city.h */
// ===================================80 chars==================================

#ifndef MC_CITY_H
#define MC_CITY_H

#include "en_essentials.h"
#include "mc_constants.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Required for JSON
#include "3rd-party/json-nlohmann/v.2.1.1/json.hpp"
// Required for JSON
#include <fstream>

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
		sf::Vector2u		m_windowSize = { 0, 0 };
		//
		float			m_city1XPosRatio = { 0 };
		float			m_city1YPosRatio = { 0 };
		float			m_city2XPosRatio = { 0 };
		float			m_city2YPosRatio = { 0 };
		float			m_city3XPosRatio = { 0 };
		float			m_city3YPosRatio = { 0 };
		float			m_city4XPosRatio = { 0 };
		float			m_city4YPosRatio = { 0 };
		float			m_city5XPosRatio = { 0 };
		float			m_city5YPosRatio = { 0 };
		float			m_city6XPosRatio = { 0 };
		float			m_city6YPosRatio = { 0 };
};

// MC_CITY_H
#endif

// ===================================80 chars==================================
/* EOF */


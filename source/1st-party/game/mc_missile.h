/* mc_missile.h */
// ===================================80 chars=================================|

#ifndef MC_MISSILE_H
#define MC_MISSILE_H

#include "en_essentials.h"

#include <SFML/Graphics.hpp>

// Required for JSON
#include "3rd-party/json-nlohmann/v.2.1.1/json.hpp"
// Required for JSON
#include <fstream>

// For object name
#include <string>
// TODO remove this -- Required for debugging for now
#include <iostream>

class Missile : public sf::Transformable, public sf::Drawable
	      , private sf::NonCopyable
{
	public:
		Missile();
		Missile( t_objectName name );
		virtual ~Missile();
		void		update( sf::Time timeSinceLastUpdate );
		void		update( sf::Time timeSinceLastUpdate
		, sf::Vector2f res );
		virtual void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void		newRound( sf::Vector2f res );
		float		getX()       const noexcept;
		float		getY()       const noexcept;
		float		getTop()     const noexcept;
		float		getBottom()  const noexcept;
		float		getLeft()    const noexcept;
		float		getRight()   const noexcept;

	protected:

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Texture		m_texture;
		sf::Vector2f		m_position;
		sf::Vector2u		m_windowSize = { 0, 0 };
		float			m_missileL1XPosRatio = { 0 };
		float			m_missileL1YPosRatio = { 0 };
		float			m_missileL2XPosRatio = { 0 };
		float			m_missileL2YPosRatio = { 0 };
		float			m_missileL3XPosRatio = { 0 };
		float			m_missileL3YPosRatio = { 0 };
		float			m_missileL4XPosRatio = { 0 };
		float			m_missileL4YPosRatio = { 0 };
		float			m_missileL5XPosRatio = { 0 };
		float			m_missileL5YPosRatio = { 0 };
		float			m_missileL6XPosRatio = { 0 };
		float			m_missileL6YPosRatio = { 0 };
		float			m_missileL7XPosRatio = { 0 };
		float			m_missileL7YPosRatio = { 0 };
		float			m_missileL8XPosRatio = { 0 };
		float			m_missileL8YPosRatio = { 0 };
		float			m_missileL9XPosRatio = { 0 };
		float			m_missileL9YPosRatio = { 0 };
		float			m_missileL0XPosRatio = { 0 };
		float			m_missileL0YPosRatio = { 0 };
};

// MC_MISSILE_H
#endif

// ===================================80 chars=================================|
/* EOF */


/* mc_play_area_bar.h */
// ===================================80 chars==================================

#ifndef MC_PLAY_AREA_BAR_H
#define MC_PLAY_AREA_BAR_H

#include "en_essentials.h"
#include "config.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
#include <memory>
// For object name
#include <string>
// TOOD: remove this debug line
#include <iostream>
// Required for RNG
#include <random>
// Required for RNG
#include <chrono>

class PlayAreaBar : public sf::Transformable
		  , public sf::Drawable
		  , private sf::NonCopyable
{
	public:
		PlayAreaBar();
		PlayAreaBar( t_objectName name );
		virtual ~PlayAreaBar();
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
};

#endif	// MC_PLAY_AREA_BAR_H

// ===================================80 chars==================================
/* EOF */


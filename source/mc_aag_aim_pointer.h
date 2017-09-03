/* mc_aag_aim_pointer.h */
// ===================================80 chars==================================

#ifndef MC_AAG_AIM_POINTER_H
#define MC_AAG_AIM_POINTER_H

#include "essentials.h"
#include "config.h"
//// For normalization
// #include "utility.h"
//// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
// #include "make_unique.h"

#include <SFML/Graphics.hpp>

//// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
// #include <memory>
//// For object name
// #include <string>
//// Required for RNG
// #include <chrono>

class AAGAimPointer : public sf::Transformable
		    , public sf::Drawable
		    , private sf::NonCopyable
{
	public:
		AAGAimPointer();
		virtual ~AAGAimPointer();
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
		res );
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
		sf::Vector2f		m_velocity;
};

#endif	// MC_AAG_AIM_POINTER_H

// ===================================80 chars==================================
/* EOF */


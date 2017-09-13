/* mc_terrain.h */
// ===================================80 chars==================================

#ifndef MC_TERRAIN_H
#define MC_TERRAIN_H

// TODO move to JSON
// DELETE THIS #define MC_GUN_INDICATOR_MOVSTEP 7.9f
#define MC_GUN_AIM_POINTER_W 60.f

#include "en_essentials.h"
//// For normalization
// #include "en_util_utility.h"
//// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
// #include "en_util_make_unique.h"

// #include <SFML/Graphics/Sprite.hpp>
// #include <SFML/Graphics/Texture.hpp>

#include <SFML/Graphics.hpp>
// Required for JSON
#include "3rd-party/json-nlohmann/v.2.1.1/json.hpp"
// Required for JSON
#include <fstream>

class Terrain : public sf::Transformable
	      , public sf::Drawable
	      , private sf::NonCopyable
{
	public:
		// Anti Aircraft Gun Aim Pointer
		Terrain();
		virtual ~Terrain();
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
		res );
		void	update( sf::Time timeSinceLastUpdate
		, sf::Vector2f r, Direction dir, float topBarBottomEdge
		, float leftBarRightEdge, float bottomBarTopEdge, float
		rightBarLeftEdgeftEdge );

		void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void	newRound( sf::Vector2f res );
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;
		float	getLeft()    const noexcept;
		float	getRight()   const noexcept;
		void	makeTerrain( sf::Vector2f res ) noexcept;

	protected:
		friend class Arena;

	private:
		const t_objectName	m_myObjNameStr;
		sf::Texture		m_texture;
		sf::Sprite		m_sprite;
		sf::Vector2f		m_position = { 0, 0 };
		sf::Vector2f		m_dimension = { 0, 0 };
		sf::Vector2f		m_requestedMoveDistance;
		sf::Vector2u		m_windowSize = { 0, 0 };
		float			m_terrainXPosRatio = 0;
		float			m_terrainYPosRatio = 0;
		float			m_terrainWidthRatio = 0;
		float			m_terrainHeightRatio = 0;
};

// MC_TERRAIN_H
#endif

// ===================================80 chars==================================
/* EOF */


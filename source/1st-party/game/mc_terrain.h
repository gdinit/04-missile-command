#ifndef MC_TERRAIN_H
#define MC_TERRAIN_H

// // TODO move to JSON
// // DELETE THIS #define MC_GUN_INDICATOR_MOVSTEP 7.9f
// #define MC_GUN_AIM_POINTER_W 60.f

// #include "en_essentials.h"
// //// For normalization
// // #include "en_util_utility.h"
// //// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
// // #include "en_util_make_unique.h"
// // ================= BEGIN: Production Assert Handling =================
// #include <assert.h>

// #ifndef EMSCRIPTEN
// #define BREAK_ACTION exit( 1 )
// #else
// #define BREAK_ACTION raise( SIGTRAP )
// #endif

// #define PASSERT( condition, message ) \
// 	do \
// 	{ \
// 		if ( !( condition ) ) { \
// 			std::cerr << "Assertion `"#condition "` failed in " << \
// 			__FILE__ << " function " << __func__ << " line " << \
// 			__LINE__ << ": " << message << std::endl; \
// 			BREAK_ACTION; \
// 		} \
// 	} while ( false )
// // ================= END: Production Assert Handling =================

// #include <SFML/Graphics.hpp>
// #include "3rd-party/json-nlohmann/v.2.1.1/json.hpp"

// //// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
// // #include <memory>
// //// For object name
// // #include <string>
// //// Required for RNG
// // #include <chrono>
// // Required for ifstream for JSON
// #include <fstream>

// class GunIndicator : public sf::Transformable
// 		   , public sf::Drawable
// 		   , private sf::NonCopyable
// {
// 	public:
// 		// Anti Aircraft Gun Aim Pointer
// 		GunIndicator();
// 		virtual ~GunIndicator();
// 		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
// 		res );
// 		// void	update( sf::Time timeSinceLastUpdate
// 		// , sf::Vector2f r, Direction dir, float leftBarRightEdge,
// 		// float
// 		// rightBarLeftEdgeftEdge );
// 		void	update( sf::Time timeSinceLastUpdate
// 		, sf::Vector2f r, Direction dir, float topBarBottomEdge
// 		, float leftBarRightEdge, float bottomBarTopEdge, float
// 		rightBarLeftEdgeftEdge );

// 		void	draw( sf::RenderTarget &target
// 		, sf::RenderStates states ) const;
// 		void	newRound( sf::Vector2f res );
// 		void	manageMovement( sf::Vector2f res, Direction dir, float
// 		topBarBottomEdge, float leftBarRightEdge, float
// 		bottomBarTopEdge, float rightBarLeftEdgeftEdge );
// 		void	valAndActionMove( sf::Vector2f res, Direction dir
// 		, float topBarBottomEdge, float leftBarRightEdge
// 		, float bottomBarTopEdge, float rightBarLeftEdgeftEdge );
// 		float	getX()       const noexcept;
// 		float	getY()       const noexcept;
// 		float	getTop()     const noexcept;
// 		float	getBottom()  const noexcept;
// 		float	getLeft()    const noexcept;
// 		float	getRight()   const noexcept;

// 	protected:
// 		friend class Arena;

// 	private:
// 		const t_objectName	m_myObjNameStr;
// 		sf::Sprite		m_sprite;
// 		sf::Texture		m_texture;
// 		sf::Vector2f		m_velocity;
// 		float			m_gunIndicatorW = -1;
// 		float			m_defAAGPointerV = -1;
// 		float			m_defAAGPointerH = -1;
// 		sf::Vector2f		m_requestedMoveDistance;
// 		sf::Vector2u		m_windowSize = { 0, 0 };
// 		float			m_gunIndicatorMovStep = -1.f;
// };

// MC_TERRAIN_H
#endif

// ===================================80 chars==================================
/* EOF */


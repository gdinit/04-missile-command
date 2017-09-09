/* mc_play_area_bar.h */
// ===================================80 chars==================================

#ifndef MC_PLAY_AREA_BAR_H
#define MC_PLAY_AREA_BAR_H

#include "en_essentials.h"
#include "en_globals.h"
// ================= BEGIN: Production Assert Handling =================
#include <assert.h>

#ifndef EMSCRIPTEN
#define BREAK_ACTION exit( 1 )
#else
#define BREAK_ACTION raise( SIGTRAP )
#endif

#define PASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
// ================= END: Production Assert Handling =================

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
// Required for reading bar ratios from JSON db
#include "3rd-party/json-nlohmann/v.2.1.1/json.hpp"
// Required for ifstream for JSON
#include <fstream>

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
		void	makeTopBar( sf::Vector2f res ) noexcept;
		void	makeLeftBar( sf::Vector2f res ) noexcept;
		void	makeBottomBar( sf::Vector2f res ) noexcept;
		void	makeRightBar( sf::Vector2f res ) noexcept;

	protected:
		friend class Arena;

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Texture		m_texture;
		sf::Vector2f		m_position;
		sf::Vector2f		m_dimension = { 0, 0 };
		float			m_width = 0;
		float			m_height = 0;
		sf::Vector2u		m_windowSize = { 0, 0 };
		float			m_topBarXPosRatio = 0;
		float			m_topBarYPosRatio = 0;
		float			m_topBarWidthRatio = 0;
		float			m_topBarHeightRatio = 0;
		float			m_leftBarXPosRatio = 0;
		float			m_leftBarYPosRatio = 0;
		float			m_leftBarWidthRatio = 0;
		float			m_leftBarHeightRatio = 0;
		float			m_bottomBarXPosRatio = 0;
		float			m_bottomBarYPosRatio = 0;
		float			m_bottomBarWidthRatio = 0;
		float			m_bottomBarHeightRatio = 0;
		float			m_rightBarXPosRatio = 0;
		float			m_rightBarYPosRatio = 0;
		float			m_rightBarWidthRatio = 0;
		float			m_rightBarHeightRatio = 0;
};

// MC_PLAY_AREA_BAR_H
#endif

// ===================================80 chars==================================
/* EOF */


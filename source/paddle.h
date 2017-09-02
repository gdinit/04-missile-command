/* paddle.h */
// ===================================80 chars==================================

#ifndef  PADDLE_H
#define  PADDLE_H

#include "config.h"
#include "essentials.h"

#include <SFML/Graphics.hpp>

// TODO	remove this
#include <iostream>
// For texture open failure reporting printf
// #include <stdio.h>

//////////////////// begin: assert handling ////////////////////
#if defined DBG
#include <assert.h>

#ifndef EMSCRIPTEN
#define BREAK_ACTION exit( 1 )
#else
#define BREAK_ACTION raise( SIGTRAP )
#endif

#   define DASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
#else
#   define DASSERT( condition, message ) do {} while ( false )
#endif
//////////////////// end: assert handling ////////////////////

class Paddle : public sf::Transformable
	     , public sf::Drawable
	     , private sf::NonCopyable
{
	public:
		Paddle();
		virtual ~Paddle();
		void		update( sf::Time timeSinceLastUpdate
		, sf::Vector2f res
		, Direction dir
		, float leftBarRE
		, float rightBarLE );
		virtual void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void		newRound( sf::Vector2f res );
		void		manageMovement( sf::Vector2f res, Direction dir
		, float leftBarRE, float rightBarLE );
		void		valAndActionMove( sf::Vector2f res, Direction
		dir, float leftBarRE, float rightBarLE );
		float		getX()       const noexcept;
		float		getY()       const noexcept;
		float		getLeft()    const noexcept;
		float		getRight()   const noexcept;
		// Top & Bottom is for debugging only
		float		getTop()     const noexcept;
		float		getBottom()  const noexcept;
		bool			m_computerControlled = true;

	protected:
		friend class Arena;

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Vector2f		m_position;
		sf::Texture		m_texture;
		sf::Vector2f		m_requestedMoveDistance;
};

#endif	// PADDLE_H

// ===================================80 chars==================================
/* EOF */


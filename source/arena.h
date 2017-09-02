/* arena.h */
// ===================================80 chars==================================

#ifndef ARENA_H
#define ARENA_H

#include "essentials.h"
#include "config.h"
#include "ball.h"
#include "paddle.h"
#include "play_area_bar.h"
// For GLOBALS & SETTINGS (for now, till we move them to play_state)
#include "make_unique.h"

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

// TOOD: remove this debug line
#include <iostream>
// for playBar object name
#include <string>
// For GLOBALS & SETTINGS (for now, till we move them to play_state)
#include <memory>

#define BR_BOUNCE_CHANCE_LOWN -0.24
#define BR_BOUNCE_CHANCE_LOWP 0.24
#define BR_BOUNCE_CHANCE_HIGHN -0.48
#define BR_BOUNCE_CHANCE_HIGHP 0.48

class Arena : public sf::Transformable, public sf::Drawable
	    , private sf::NonCopyable
{
	public:
		Arena();
		virtual ~Arena();
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
		res );
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
		, Direction dir );
		void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void	newRound( sf::Vector2f res, int32 level );
		void	createCells( sf::Vector2f res, int32 level );
		void	colDetRespond( void );
		void	colDetRespondBallPaddle( void );
		void	colDetRespondBallWall( void );
		void	colDetRespondBallGoal( void );
		void	colDetRespondBallCell( void );
		void	paintCells( void );

	protected:

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Texture		m_texture;
		sf::Vector2f		m_position;
		sf::Vector2f		m_velocity;
		sf::SoundBuffer		m_sndbfColPaddle;
		sf::Sound		m_soundColPaddle;
		Ball			ball;
		Paddle			paddle;
		PlayAreaBar		topBar = { "topBar" };
		PlayAreaBar		leftBar = { "leftBar" };
		PlayAreaBar		rightBar = { "rightBar" };
		// TODO make this enum class
		enum {
			CELLTYPE0 = 0
			, CELLTYPE1
			, CELLTYPE2
			, CELLTYPE3
			, CELLTYPE4
			, CELLTYPE5
		};
		enum class Color : char {
			PINK = 1
			, ORANGE = 2
			, BROWN = 3
			, YELLOW = 4
			, GREEN = 5
			, BLUE = 6
		};
		struct CellDetails {
			int32 cellNumericId;
			int32 cellType;
			Color color;
			// Cell will get destroyed with a single hit
			int32 HP = 1;
			// Not visible means hidden but ball can collide
			bool visible = 1;
			// Phantom means hidden AND ball cannot collide
			bool phantom = 0;
			sf::Vector2f pos;
		};
		enum class ImpactZone {
			LEFT
			, CENTER
			, RIGHT
			, NONE
		};
		// Cell Details DB
		std::vector <CellDetails>	m_cDetDB;
		// Cell Sprite Database
		std::vector <sf::Sprite>	m_cSDB;
		sf::Texture			m_squareTexture;
		sf::Vector2f			m_brickSize;
		// Hourglasses to prevent multiple successive quick hits
		int				m_hgPaddle;
		int				m_hgTopBar;
		int				m_hgLeftBar;
		int				m_hgRightBar;
		// TODO	remove this redundant storage. dynamically obtain res.
		sf::Vector2f			m_tmpRes;
};

#endif	// ARENA_H

// ===================================80 chars==================================
/* EOF */


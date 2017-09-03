/* arena.h */
// ===================================80 chars==================================

#ifndef ARENA_H
#define ARENA_H

#include "essentials.h"
#include "config.h"
#include "play_area_bar.h"
#include "mc_aag_aim_pointer.h"
// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
#include "make_unique.h"

#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>

// TOOD: remove this debug line
#include <iostream>
// for playBar object name
// #include <string>
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
		, Direction dir );
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f );
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
		AAGAimPointer		AAGAimPointer;
		// AAGAimPointer		AAGAimPointer = { 100, 100 };
		PlayAreaBar		topBar = { "topBar" };
		PlayAreaBar		leftBar = { "leftBar" };
		PlayAreaBar		rightBar = { "rightBar" };
};

#endif	// ARENA_H

// ===================================80 chars==================================
/* EOF */


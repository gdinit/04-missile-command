/* mc_arena.h */
// ===================================80 chars==================================

#ifndef MC_ARENA_H
#define MC_ARENA_H

#include "en_essentials.h"
// TODO remove this #include "mc_config.h"
#include "mc_play_area_bar.h"
#include "mc_city.h"
#include "mc_gun_indicator.h"
// For GLOBALS & SETTINGS (for now, till they are moved to play_state)
#include "en_util_make_unique.h"

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
		GunIndicator		gunIndicator;
		PlayAreaBar		topBar = { "topBar" };
		PlayAreaBar		leftBar = { "leftBar" };
		PlayAreaBar		bottomBar = { "bottomBar" };
		PlayAreaBar		rightBar = { "rightBar" };
		City			leftCity = { "leftCity" };
		City			middleCity = { "middleCity" };
		City			rightCity = { "rightCity" };
};

// MC_ARENA_H
#endif

// ===================================80 chars==================================
/* EOF */


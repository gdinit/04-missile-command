/* ball.h */
// ===================================80 chars==================================

#ifndef BALL_H
#define BALL_H

#include "essentials.h"
#include "config.h"
// For normalizing ballNewVel
#include "utility.h"
// For GLOBALS & SETTINGS (for now, till we move them to play_state)
#include "make_unique.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// For GLOBALS & SETTINGS (for now, till we move them to play_state)
#include <memory>
// For object name
#include <string>
// TOOD: remove this debug line
#include <iostream>
// Required for RNG
#include <random>
// Required for RNG
#include <chrono>

class Ball : public sf::Transformable
	   , public sf::Drawable
	   , private sf::NonCopyable
{
	public:
		Ball();
		virtual ~Ball();
		void	update( sf::Time timeSinceLastUpdate, sf::Vector2f
		res );
		void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void	newRound( sf::Vector2f res );
		void	throwRandomly( sf::Vector2f res );
		float	getX()       const noexcept;
		float	getY()       const noexcept;
		float	getTop()     const noexcept;
		float	getBottom()  const noexcept;

	protected:
		friend class Arena;

	private:
		const t_objectName	m_myObjNameStr;
		sf::Sprite		m_sprite;
		sf::Texture		m_texture;
		sf::Vector2f		m_velocity;
		sf::SoundBuffer		m_sbuffCol;
		sf::Sound		m_soundCol;
};

#endif	// BALL_H

// ===================================80 chars==================================
/* EOF */


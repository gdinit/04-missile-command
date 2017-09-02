/* hud.h */
// ===================================80 chars==================================

// Class to cover hud objects between play & pause states
// e.g.: background, borders, top text (score, lives etc.)

#ifndef  HUD_H
#define  HUD_H

#include "essentials.h"
#include "config.h"
// Required for HUD Text
#include "globals.h"
// Required for centerOrigin
#include "utility.h"

#include <SFML/Graphics.hpp>

// Required for unique_ptr
#include <memory>
// Required for debugging -- TODO REMOVE THIS
#include <iostream>

class Hud : public sf::Transformable, public sf::Drawable
	  , private sf::NonCopyable
{
	public:
		Hud();
		/// Hud( SharedContext &context );
		virtual ~Hud();
		void		update( sf::Time timeSinceLastUpdate );
		virtual void	draw( sf::RenderTarget &target
		, sf::RenderStates states ) const;
		void		newRound( sf::Vector2f res );

	protected:

	private:
		const t_objectName	m_myObjNameStr;
		sf::Font		m_hudTextFont;
		sf::Text		m_hudText;
		sf::Vector2i		m_screenSize;

		sf::Texture		m_texturePak;
		sf::Sprite		m_blueBackground;
};

#endif	// HUD_H

// ===================================80 chars==================================
/* EOF */


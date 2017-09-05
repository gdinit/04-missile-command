/* en_arena.h */
// ===================================80 chars==================================

////////////////////////////////////////////////////////////////////////////////
// CONTENTS OF THIS FILE HAS BEEN DELETED TO ENABLE SIMPLEST POSSIBLE
// (BLACK BOX)  STATE.
//
// ALL COMMENTS & BLOCKED OUT CODE HAS BEEN REMOVED.
// ACTUAL CONTENTS MOVED TO GAME FILE.
////////////////////////////////////////////////////////////////////////////////

#ifndef EN_ARENA_H
#define EN_ARENA_H
#include "en_essentials.h"
#include "en_make_unique.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
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

	protected:

	private:
};

#endif	// EN_ARENA_H

// ===================================80 chars==================================
/* EOF */


/* mc_play_area_bar_makebottombar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

void PlayAreaBar::makeBottomBar( sf::Vector2f res ) noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a bar...\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	      ++it ) {
		if ( it.key() == "bottomBarXPosRatio" ) {
			m_bottomBarXPosRatio = it.value();
		} else if ( it.key() == "bottomBarYPosRatio" ) {
			m_bottomBarYPosRatio = it.value();
		} else if ( it.key() == "bottomBarWidthRatio" ) {
			m_bottomBarWidthRatio = it.value();
		} else if ( it.key() == "bottomBarHeightRatio" ) {
			m_bottomBarHeightRatio = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_bottomBarXPosRatio is: " << m_bottomBarXPosRatio <<
	"\t m_bottomBarYPosRatio is: " << m_bottomBarYPosRatio << "\n";
	#endif
	PDASSERT(       ( m_bottomBarXPosRatio > 0 )
		, "ERROR: m_bottomBarXPosRatio must be > 0!\tIt is: " <<
		m_bottomBarXPosRatio << "\n" );
	PDASSERT(       ( m_bottomBarYPosRatio > 0 )
		, "ERROR: m_bottomBarYPosRatio must be > 0!\tIt is: " <<
		m_bottomBarYPosRatio << "\n" );

	m_position.x = m_windowSize.x * m_bottomBarXPosRatio;
	m_position.y = m_windowSize.y - ( m_windowSize.y *
					  m_bottomBarYPosRatio );
	m_dimension.x = m_windowSize.x * m_bottomBarWidthRatio;
	m_dimension.y = m_windowSize.y * m_bottomBarHeightRatio;
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated" <<
	" position as: " << m_position.x << "," << m_position.y << "\t"	<<
	"[DEBUG]\tCalculated " << m_myObjNameStr << " size as w: " <<
	m_dimension.x << "\t h: " << m_dimension.y << "\n";
	#endif
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( m_position.x, m_position.y
			, m_dimension.x, m_dimension.y ) );
	m_sprite.setPosition( m_position.x, m_position.y );
	m_sprite.setColor( sf::Color( sf::Color::Green ) );
}

// ===================================80 chars==================================
/* EOF */


/* mc_play_area_bar_makerightbar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

void PlayAreaBar::makeRightBar( sf::Vector2f res ) noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a bar...\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	      ++it ) {
		if ( it.key() == "rightBarXPosRatio" ) {
			m_rightBarXPosRatio = it.value();
		} else if ( it.key() == "rightBarYPosRatio" ) {
			m_rightBarYPosRatio = it.value();
		} else if ( it.key() == "rightBarWidthRatio" ) {
			m_rightBarWidthRatio = it.value();
		} else if ( it.key() == "rightBarHeightRatio" ) {
			m_rightBarHeightRatio = it.value();
		} else if ( it.key() == "topBarYPosRatio" ) {
			m_topBarYPosRatio = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_rightBarXPosRatio is: " << m_rightBarXPosRatio <<
	"\t m_rightBarYPosRatio is: " << m_rightBarYPosRatio << "\n";
	#endif
	// PASSERT(        ( m_rightBarXPosRatio > 0 )
	// , "ERROR: m_rightBarXPosRatio must be > 0!\tIt is: " <<
	// m_rightBarXPosRatio << "\n" );
	// PASSERT(        ( m_rightBarYPosRatio > 0 )
	// , "ERROR: m_rightBarYPosRatio must be > 0!\tIt is: " <<
	// m_rightBarYPosRatio << "\n" );
	// m_position.x = m_windowSize.x - ( m_windowSize.x *
	// m_rightBarXPosRatio );
	m_position.x = m_windowSize.x - 1;
	m_position.y = m_windowSize.y * m_rightBarYPosRatio;
	m_dimension.x = m_windowSize.x * m_rightBarWidthRatio;
	m_dimension.y = m_windowSize.y - ( m_windowSize.y *
					   ( m_topBarYPosRatio * 2 ) );
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


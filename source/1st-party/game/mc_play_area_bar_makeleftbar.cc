/* mc_play_area_bar_makeleftbar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

void PlayAreaBar::makeLeftBar( sf::Vector2f res ) noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a bar...\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	      ++it ) {
		if ( it.key() == "leftBarXPosRatio" ) {
			m_leftBarXPosRatio = it.value();
		} else if ( it.key() == "leftBarYPosRatio" ) {
			m_leftBarYPosRatio = it.value();
		} else if ( it.key() == "leftBarWidthRatio" ) {
			m_leftBarWidthRatio = it.value();
		} else if ( it.key() == "leftBarHeightRatio" ) {
			m_leftBarHeightRatio = it.value();
		} else if ( it.key() == "topBarYPosRatio" ) {
			m_topBarYPosRatio = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_leftBarXPosRatio  is: " << m_leftBarXPosRatio <<
	"\t m_leftBarYPosRatio is: " << m_leftBarYPosRatio << "\n";
	#endif
	PASSERT(        ( m_leftBarXPosRatio > 0 )
		, "ERROR: m_leftBarXPosRatio must be > 0!\tIt is: " <<
		m_leftBarXPosRatio << "\n" );
	PASSERT(        ( m_leftBarYPosRatio > 0 )
		, "ERROR: m_leftBarYPosRatio must be > 0!\tIt is: " <<
		m_leftBarYPosRatio << "\n" );
	// m_position.x = m_windowSize.x * m_leftBarXPosRatio;
	m_position.x = 1;
	m_position.y = m_windowSize.y * m_leftBarYPosRatio;
	m_dimension.x = m_windowSize.x * m_leftBarWidthRatio;
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


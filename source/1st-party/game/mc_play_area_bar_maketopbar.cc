/* mc_play_area_bar_maketopbar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

void PlayAreaBar::makeTopBar( sf::Vector2f res ) noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making a bar...\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	      ++it ) {
		if ( it.key() == "topBarXPosRatio" ) {
			m_topBarXPosRatio = it.value();
		} else if ( it.key() == "topBarYPosRatio" ) {
			m_topBarYPosRatio = it.value();
		} else if ( it.key() == "topBarWidthRatio" ) {
			m_topBarWidthRatio = it.value();
		} else if ( it.key() == "topBarHeightRatio" ) {
			m_topBarHeightRatio = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_topBarXPosRatio is: " << m_topBarXPosRatio	<<
	"\t m_topBarYPosRatio is: " << m_topBarYPosRatio << "\n";
	#endif
	PDASSERT(       ( m_topBarXPosRatio > 0 )
		, "ERROR: m_topBarXPosRatio must be > 0!\tIt is: " <<
		m_topBarXPosRatio << "\n" );
	PDASSERT(       ( m_topBarYPosRatio > 0 )
		, "ERROR: m_topBarYPosRatio must be > 0!\tIt is: " <<
		m_topBarYPosRatio << "\n" );
	m_position.x = m_windowSize.x * m_topBarXPosRatio;
	m_position.y = m_windowSize.y * m_topBarYPosRatio;
	m_dimension.x = m_windowSize.x * m_topBarWidthRatio;
	m_dimension.y = m_windowSize.y * m_topBarHeightRatio;
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


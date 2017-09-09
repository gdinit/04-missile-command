/* mc_play_area_bar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

PlayAreaBar::PlayAreaBar()
	: m_myObjNameStr( "Unnamed PlayAreaBar" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
	// SET UP SPRITE
	m_sprite.setColor( sf::Color( sf::Color::Red ) );
	m_sprite.setOrigin( 50 / 2.f, 70 / 2.f );
	m_sprite.setPosition( m_windowSize.x / 3, m_windowSize.y / 2 );
}

// TODO	color also should be passed while creating
PlayAreaBar::PlayAreaBar( t_objectName name )
	: m_myObjNameStr( name )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

PlayAreaBar::~PlayAreaBar()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void PlayAreaBar::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
}

void PlayAreaBar::draw( sf::RenderTarget &target, sf::RenderStates
	states ) const {
	target.draw( m_sprite );
}

void PlayAreaBar::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	// This must happen before makeXBar().
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
	if ( m_myObjNameStr == "topBar" ) {
		makeTopBar( res );
	} else if ( m_myObjNameStr == "leftBar" ) {
		makeLeftBar( res );
	} else if ( m_myObjNameStr == "bottomBar" ) {
		makeBottomBar( res );
	} else if ( m_myObjNameStr == "rightBar" ) {
		makeRightBar( res );
	}
}

float PlayAreaBar::getX() const noexcept {
	return m_sprite.getPosition().x;
}

float PlayAreaBar::getY() const noexcept {
	return m_sprite.getPosition().y;
}

float PlayAreaBar::getTop() const noexcept {
	// return getY() - ( C_BALL_H / 2.f );
}

float PlayAreaBar::getBottom() const noexcept {
	// return getY() + ( C_BALL_H / 2.f );
}

float PlayAreaBar::getLeft() const noexcept {
	// return getX();
}

float PlayAreaBar::getRight() const noexcept {
	// return getX() + m_width;
}

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
	PASSERT(        ( m_topBarXPosRatio > 0 )
		, "ERROR: m_topBarXPosRatio must be > 0!\tIt is: " <<
		m_topBarXPosRatio << "\n" );
	PASSERT(        ( m_topBarYPosRatio > 0 )
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
	m_position.x = m_windowSize.x * m_leftBarXPosRatio;
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
	PASSERT(        ( m_bottomBarXPosRatio > 0 )
		, "ERROR: m_bottomBarXPosRatio must be > 0!\tIt is: " <<
		m_bottomBarXPosRatio << "\n" );
	PASSERT(        ( m_bottomBarYPosRatio > 0 )
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
	PASSERT(        ( m_rightBarXPosRatio > 0 )
		, "ERROR: m_rightBarXPosRatio must be > 0!\tIt is: " <<
		m_rightBarXPosRatio << "\n" );
	PASSERT(        ( m_rightBarYPosRatio > 0 )
		, "ERROR: m_rightBarYPosRatio must be > 0!\tIt is: " <<
		m_rightBarYPosRatio << "\n" );
	m_position.x = m_windowSize.x - ( m_windowSize.x *
					  m_rightBarXPosRatio );
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


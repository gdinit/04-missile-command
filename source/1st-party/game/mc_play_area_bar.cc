/* mc_play_area_bar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

// extern std::unique_ptr <Settings>	SETTINGS;
// extern std::unique_ptr <Globals>	GLOBALS;

//// OBJECT SIZE RATIOS
//// TODO: MOVE TO DEFINES
// constexpr double	CEXPR_TBXRATIO { 0.10 };
//// constexpr double			CEXPR_TBYRATIO { 0.15 };
// constexpr double	CEXPR_TBYRATIO { 0.05 };
// constexpr double	CEXPR_TBWRATIO { 0.78 };
//// constexpr double			CEXPR_TBHRATIO { 0.06 };
// constexpr double	CEXPR_TBHRATIO { 0.00398406374501992 };
// constexpr double	CEXPR_LBXRATIO { 0.10 };
// constexpr double	CEXPR_LBYRATIO { 0.15 };
// constexpr double	CEXPR_LBHRATIO { 0.06 };
// constexpr double	CEXPR_BBYRATIO { 0.92 };
// constexpr double	CEXPR_RBXRATIO { 0.10 };
// constexpr double	CEXPR_RBYRATIO { 0.15 };
// constexpr double	CEXPR_RBWRATIO { 0.4347826086956522 };
// constexpr double	CEXPR_RBHRATIO { 0.06 };
//// constexpr double			CEXPR_VBWRATIO { 23.0 };
//// constexpr double			CEXPR_VBWRATIO { 0.00398406374501992 };
// constexpr double	CEXPR_VBWRATIO { 0.003985 };
//// constexpr double			CEXPR_VBHRATIO { 1.347290640394089 };
// constexpr double	CEXPR_VBHRATIO { 1.15 };
// constexpr float		CEXPR_BRHRATIO {
// 0.02564102564102564f
// };
// constexpr float		CEXPR_BRPYRATIO {
// 0.3113553113553114f
// };
// constexpr float		CEXPR_BRWRATIO { 0.0461f };
// constexpr float		CEXPR_BRPXRATIO { 0.1293f };
//// TODO rename or remove this
// constexpr float		C_BALL_H { 7.f };

PlayAreaBar::PlayAreaBar()
	: m_myObjNameStr( "Unnamed PlayAreaBar" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif

	// SET UP SPRITE
	// m_sprite.setTexture( m_texture );
	// m_sprite.setTextureRect( sf::IntRect( 0, 0, 50, 70 ) );
	// m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setColor( sf::Color( sf::Color::Red ) );
	m_sprite.setOrigin( 50 / 2.f, 70 / 2.f );
	// m_sprite.setPosition( 0, 0 );
	m_sprite.setPosition( m_windowSize.x / 3, m_windowSize.y / 2 );
	// m_velocity.x = 0.f;
	// m_velocity.y = 0.f;
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

	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;

	// #if defined DBG
	// std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	// "newRound() has been triggered.\tres:" << res.x << "," << res.y <<
	// "\n";
	// #endif

	// Position from Left & Top
	int32			posL = -999;
	int32			posT = -888;
	int32			sizeW = -777;
	int32			sizeH = -666;
	constexpr double	CEXPR_VBHRATIO { 1.15 };

	////////////////////////////////////////////////////////////////////////
	// TODO remove this bit because we will not base it on top bar!
	// int32	topBarPosL = res.x * ( ( 1.f - CEXPR_TBWRATIO ) / 2.f );
	// int32	topBarSizeW = res.x * CEXPR_TBWRATIO;
	////////////////////////////////////////////////////////////////////////

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
	// Production Assert - ensure JSON loaded fine
	PASSERT(        ( m_topBarXPosRatio > 0 )
		, "ERROR: m_topBarXPosRatio must be > 0!\tIt is: " <<
		m_topBarXPosRatio << "\n" );
	PASSERT(        ( m_topBarYPosRatio > 0 )
		, "ERROR: m_topBarYPosRatio must be > 0!\tIt is: " <<
		m_topBarYPosRatio << "\n" );

	m_position.x = m_windowSize.x * m_topBarXPosRatio;
	m_position.y = m_windowSize.y * m_topBarYPosRatio;
	// m_width = m_windowSize.x * m_topBarWidthRatio;
	// m_height = m_windowSize.y * m_topBarHeightRatio;
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
	// Production Assert - ensure JSON loaded fine
	PASSERT(        ( m_leftBarXPosRatio > 0 )
		, "ERROR: m_leftBarXPosRatio must be > 0!\tIt is: " <<
		m_leftBarXPosRatio << "\n" );
	PASSERT(        ( m_leftBarYPosRatio > 0 )
		, "ERROR: m_leftBarYPosRatio must be > 0!\tIt is: " <<
		m_leftBarYPosRatio << "\n" );

	m_position.x = m_windowSize.x * m_leftBarXPosRatio;
	m_position.y = m_windowSize.y * m_leftBarYPosRatio;
	// m_width = m_windowSize.x * m_leftBarWidthRatio;
	// m_height = m_windowSize.y * m_leftBarHeightRatio;
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
	// Production Assert - ensure JSON loaded fine
	PASSERT(        ( m_bottomBarXPosRatio > 0 )
		, "ERROR: m_bottomBarXPosRatio must be > 0!\tIt is: " <<
		m_bottomBarXPosRatio << "\n" );
	PASSERT(        ( m_bottomBarYPosRatio > 0 )
		, "ERROR: m_bottomBarYPosRatio must be > 0!\tIt is: " <<
		m_bottomBarYPosRatio << "\n" );

	m_position.x = m_windowSize.x * m_bottomBarXPosRatio;
	m_position.y = m_windowSize.y - ( m_windowSize.y *
					  m_bottomBarYPosRatio );
	// m_width = m_windowSize.x * m_bottomBarWidthRatio;
	// m_height = m_windowSize.y * m_bottomBarHeightRatio;
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
	// Production Assert - ensure JSON loaded fine
	PASSERT(        ( m_rightBarXPosRatio > 0 )
		, "ERROR: m_rightBarXPosRatio must be > 0!\tIt is: " <<
		m_rightBarXPosRatio << "\n" );
	PASSERT(        ( m_rightBarYPosRatio > 0 )
		, "ERROR: m_rightBarYPosRatio must be > 0!\tIt is: " <<
		m_rightBarYPosRatio << "\n" );

	m_position.x = m_windowSize.x - ( m_windowSize.x *
					  m_rightBarXPosRatio );
	m_position.y = m_windowSize.y * m_rightBarYPosRatio;
	// m_width = m_windowSize.x * m_rightBarWidthRatio;
	// m_height = m_windowSize.y * m_rightBarHeightRatio;
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


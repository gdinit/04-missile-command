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
	, m_width( 11.f )
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
	, m_width( 11.f )
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
		// -----------------
		#if defined DBG
		std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
		"just hit >>>> m_myObjNameStr == topBar <<<<<<<\n";
		#endif
		// JSON work here: get topBarXRatio & topBarYRatio
		std::ifstream	i( "data/defines.json" );
		nlohmann::json	j;
		i >> j;
		for ( nlohmann::json::iterator it = j.begin(); it != j.end();
		      ++it ) {
			if ( it.key() == "topBarXRatio" ) {
				m_topBarXRatio = it.value();
				// std::cout <<
				// "found topBarXRatio!\t value is: " <<
				// it.value() << "\n";
			} else if ( it.key() == "topBarYRatio" ) {
				m_topBarYRatio = it.value();
			} else {
				std::cout << "just hit else!\n";
			}
		}
		i.close();
		// TODO remove TMP couts
		std::cout << "[TMP]\t m_topBarXRatio is: " << m_topBarXRatio <<
		"\n";
		std::cout << "[TMP]\t m_topBarYRatio is: " << m_topBarYRatio <<
		"\n";
		// Production Assert - ensure JSON loaded fine
		PASSERT(        ( m_topBarXRatio > 0 )
			, "ERROR: m_topBarXRatio must be > 0!\tIt is: "	<<
			m_topBarXRatio << "\n" );
		PASSERT(        ( m_topBarYRatio > 0 )
			, "ERROR: m_topBarYRatio must be > 0!\tIt is: "	<<
			m_topBarYRatio << "\n" );
		//// posL = topBarPosL;
		//// posT = res.y * CEXPR_TBYRATIO;
		//// sizeW = topBarSizeW;
		//// m_width = sizeW;
		//// sizeH = res.y * CEXPR_TBHRATIO;
		//// #if defined DBG
		//// std::cout << "[DEBUG]\tposL: " << posL << "\tposT:
		/// "
		//// << posT <<
		//// "\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "//
		/// "
		//// <<
		//// m_myObjNameStr << "\n";
		//// #endif
		////// -----------------
	} else if ( m_myObjNameStr == "leftBar" ) {
		// this is ok
		// sizeW = res.x * .20f;
		// m_width = sizeW;
		// posL = 0;
		// posT = 0;
		// sizeH = res.y / CEXPR_VBHRATIO;

		// JSON
		std::ifstream	i( "data/defines.json" );
		nlohmann::json	j;
		i >> j;
		for ( nlohmann::json::iterator it = j.begin(); it != j.end();
		      ++it ) {
			if ( it.key() == "leftBarXRatio" ) {
				m_leftBarXRatio = it.value();
				std::cout << "found a XRatio!\t value is: " <<
				it.value() << "\n";
			} else if ( it.key() == "leftBarYRatio" ) {
				m_leftBarYRatio = it.value();
				std::cout << "found a YRatio!\t value is: " <<
				it.value() << "\n";
			} else {
				std::cout << "just hit else!\n";
			}
		}
		i.close();
		// TODO remove TMP couts
		std::cout << "[TMP]\t m_leftBarXRatio is: " <<
		m_leftBarXRatio	<< "\n";
		std::cout << "[TMP]\t m_leftBarYRatio is: " <<
		m_leftBarYRatio	<< "\n";
		// Production Assert - ensure JSON loaded fine
		PASSERT(        ( m_leftBarXRatio > 0 )
			, "ERROR: m_leftBarXRatio must be > 0!\tIt is: " <<
			m_leftBarXRatio << "\n" );
		PASSERT(        ( m_leftBarYRatio > 0 )
			, "ERROR: m_leftBarYRatio must be > 0!\tIt is: " <<
			m_leftBarYRatio << "\n" );

		sizeW = res.x * .20f;
		m_width = sizeW;
		posL = 0;
		posT = 0;
		sizeH = res.y / m_leftBarYRatio;
	} else if ( m_myObjNameStr == "bottomBar" ) {
		// posL = topBarPosL;
		// posT = res.y * CEXPR_BBYRATIO;
		// sizeW = topBarSizeW;
		// m_width = sizeW;
		// sizeH = res.y * CEXPR_TBHRATIO;
		// #if defined DBG
		// std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " <<	posT
		// <<
		// "\tsizeW: " << sizeW << "\tsizeH: " << sizeH <<	"// " <<
		// m_myObjNameStr << "\n";
		// #endif
	} else if ( m_myObjNameStr == "rightBar" ) {
		// sizeW = res.x * CEXPR_VBWRATIO;
		// m_width = sizeW;
		// posL = ( topBarPosL + topBarSizeW ) - sizeW / 2.f;
		// posT = res.y * CEXPR_TBYRATIO;
		// sizeH = res.y / CEXPR_VBHRATIO;
	}
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated" <<
	" position as: " << posL << "," << posT << "\n"	<<
	"[DEBUG]\tCalculated " << m_myObjNameStr << " size as: " << sizeW <<
	"," << sizeH << "\n";
	#endif
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( posL, posT, sizeW, sizeH ) );
	m_sprite.setPosition( posL, posT );
	// m_sprite.setPosition( res.x / 3.f, res.y / 3.f );
	// m_sprite.setColor( sf::Color( 120, 104, 112 ) );
	m_sprite.setColor( sf::Color( sf::Color::Red ) );
	// =========================== reviewed 4 MC ===========================
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
	// =========================== reviewed 4 MC ===========================
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

// ===================================80
// chars==================================
/* EOF */


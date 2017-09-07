/* mc_play_area_bar.cc */
// ===================================80 chars==================================

#include "mc_play_area_bar.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;

// OBJECT SIZE RATIOS
// TODO: MOVE TO DEFINES
constexpr double			CEXPR_TBXRATIO { 0.10 };
// constexpr double			CEXPR_TBYRATIO { 0.15 };
constexpr double			CEXPR_TBYRATIO { 0.05 };
constexpr double			CEXPR_TBWRATIO { 0.78 };
// constexpr double			CEXPR_TBHRATIO { 0.06 };
constexpr double			CEXPR_TBHRATIO { 0.00398406374501992 };
constexpr double			CEXPR_LBXRATIO { 0.10 };
constexpr double			CEXPR_LBYRATIO { 0.15 };
constexpr double			CEXPR_LBHRATIO { 0.06 };
constexpr double			CEXPR_BBYRATIO { 0.92 };
constexpr double			CEXPR_RBXRATIO { 0.10 };
constexpr double			CEXPR_RBYRATIO { 0.15 };
constexpr double			CEXPR_RBWRATIO { 0.4347826086956522 };
constexpr double			CEXPR_RBHRATIO { 0.06 };
// constexpr double			CEXPR_VBWRATIO { 23.0 };
// constexpr double			CEXPR_VBWRATIO { 0.00398406374501992 };
constexpr double			CEXPR_VBWRATIO { 0.003985 };
// constexpr double			CEXPR_VBHRATIO { 1.347290640394089 };
constexpr double			CEXPR_VBHRATIO { 1.15 };
constexpr float				CEXPR_BRHRATIO { 0.02564102564102564f };
constexpr float				CEXPR_BRPYRATIO { 0.3113553113553114f };
constexpr float				CEXPR_BRWRATIO { 0.0461f };
constexpr float				CEXPR_BRPXRATIO { 0.1293f };
// TODO rename or remove this
constexpr float				C_BALL_H { 7.f };

PlayAreaBar::PlayAreaBar()
	: m_myObjNameStr( "Unnamed PlayAreaBar" )
	, m_width( 1.f )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

// TODO	color also should be passed while creating
PlayAreaBar::PlayAreaBar( t_objectName name )
	: m_myObjNameStr( name )
	, m_width( 1.f )
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
	int32	posL = -999;
	int32	posT = -888;
	int32	sizeW = -777;
	int32	sizeH = -666;
	int32	topBarPosL = res.x * ( ( 1.f - CEXPR_TBWRATIO ) / 2.f );
	int32	topBarSizeW = res.x * CEXPR_TBWRATIO;
	if ( m_myObjNameStr == "topBar" ) {
		posL = topBarPosL;
		posT = res.y * CEXPR_TBYRATIO;
		sizeW = topBarSizeW;
		m_width = sizeW;
		sizeH = res.y * CEXPR_TBHRATIO;
		#if defined DBG
		std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
		"\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
		m_myObjNameStr << "\n";
		#endif
	} else if ( m_myObjNameStr == "leftBar" ) {
		sizeW = res.x * CEXPR_VBWRATIO;
		m_width = sizeW;
		posL = topBarPosL - ( sizeW / 2.f );
		posT = res.y * CEXPR_TBYRATIO;
		sizeH = res.y / CEXPR_VBHRATIO;
	} else if ( m_myObjNameStr == "bottomBar" ) {
		// m_width = sizeW;
		// posL = topBarPosL;
		// posT = res.y * CEXPR_BBYRATIO;
		// sizeH = res.y * CEXPR_TBHRATIO;
		posL = topBarPosL;
		// posT = res.y * CEXPR_TBYRATIO;
		posT = res.y * CEXPR_BBYRATIO;
		sizeW = topBarSizeW;
		m_width = sizeW;
		sizeH = res.y * CEXPR_TBHRATIO;
		#if defined DBG
		std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
		"\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
		m_myObjNameStr << "\n";
		#endif
	} else if ( m_myObjNameStr == "rightBar" ) {
		sizeW = res.x * CEXPR_VBWRATIO;
		m_width = sizeW;
		posL = ( topBarPosL + topBarSizeW ) - sizeW / 2.f;
		posT = res.y * CEXPR_TBYRATIO;
		sizeH = res.y / CEXPR_VBHRATIO;
	}
	#if defined DBG
	std::cout << "[DEBUG]\tCalculated position as: " << posL << "," <<
	posT << "\n" <<	"[DEBUG]\tCalculated " << m_myObjNameStr <<
	" size as: " << sizeW << "," << sizeH << "\n";
	#endif
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( posL, posT, sizeW, sizeH ) );
	m_sprite.setPosition( posL, posT );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );
}

float PlayAreaBar::getX() const noexcept { return m_sprite.getPosition().x; }

float PlayAreaBar::getY() const noexcept { return m_sprite.getPosition().y; }

float PlayAreaBar::getTop() const noexcept {
	return getY() - ( C_BALL_H / 2.f );
}

float PlayAreaBar::getBottom() const noexcept {
	return getY() + ( C_BALL_H / 2.f );
}

float PlayAreaBar::getLeft() const noexcept {
	return getX();
}

float PlayAreaBar::getRight() const noexcept {
	return getX() + m_width;
}

// ===================================80 chars==================================
/* EOF */


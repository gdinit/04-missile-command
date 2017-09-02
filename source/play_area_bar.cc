/* play_area_bar.cc */
// ===================================80 chars==================================

#include "play_area_bar.h"

extern std::unique_ptr <Settings>	SETTINGS;
extern std::unique_ptr <Globals>	GLOBALS;

PlayAreaBar::PlayAreaBar()
	: m_myObjNameStr( "unnamed PlayAreaBar" )
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
		sizeW = res.x / CEXPR_VBWRATIO;
		m_width = sizeW;
		posL = topBarPosL - ( sizeW / 2.f );
		posT = res.y * CEXPR_TBYRATIO;
		sizeH = res.y / CEXPR_VBHRATIO;
	} else if ( m_myObjNameStr == "rightBar" ) {
		sizeW = res.x / CEXPR_VBWRATIO;
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


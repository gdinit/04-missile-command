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
	// TODO  change this to this style (divide height)

	// return getY() + ( C_BALL_H / 2.f );
	return getY();
}

float PlayAreaBar::getBottom() const noexcept {
	// TODO  change this to this style (divide height)

	// return getY() + ( C_BALL_H / 2.f );
	return getY();
}

float PlayAreaBar::getLeft() const noexcept {
	return getX();
}

float PlayAreaBar::getRight() const noexcept {
	return getX() + m_width;
}

// ===================================80 chars==================================
/* EOF */


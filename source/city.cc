/* city.cc */
// ===================================80 chars==================================

#include "city.h"

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

City::City()
	: m_myObjNameStr( "Unnamed City" )
	, m_width( 1.f )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

// TODO	color also should be passed while creating
City::City( t_objectName name )
	: m_myObjNameStr( name )
	, m_width( 1.f )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
}

City::~City()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void City::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
}

void City::draw( sf::RenderTarget &target, sf::RenderStates
	states ) const {
	target.draw( m_sprite );

	// TODO REMOVE THIS DEBUG COUT
	std::cout << "hit city draw\n";
}

void City::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tres:" << res.x << "," << res.y << "\n";
	#endif
	int32	posL = 100;
	int32	posT = 100;
	int32	sizeW = 45;
	int32	sizeH = 26;
	if ( m_myObjNameStr == "leftCity" ) {
		m_width = sizeW;
		#if defined DBG
		std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
		"\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
		m_myObjNameStr << "\n";
		#endif
	} else if ( m_myObjNameStr == "middleCity" ) {
		m_width = sizeW;
		#if defined DBG
		std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
		"\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
		m_myObjNameStr << "\n";
		#endif
	} else if ( m_myObjNameStr == "rightCity" ) {
		m_width = sizeW;
		#if defined DBG
		std::cout << "[DEBUG]\tposL: " << posL << "\tposT: " << posT <<
		"\tsizeW: " << sizeW << "\tsizeH: " << sizeH << "// " <<
		m_myObjNameStr << "\n";
		#endif
	}
	#if defined DBG
	std::cout << "[DEBUG]\tCalculated position as: " << posL << "," <<
	posT << "\n" <<	"[DEBUG]\tCalculated " << m_myObjNameStr <<
	" size as: " << sizeW << "," << sizeH << "\n";
	#endif
	m_texture.loadFromFile( "assets/textures/45x26_city.png" );
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( posL, posT, sizeW, sizeH ) );
	m_sprite.setPosition( posL, posT );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

float City::getX() const noexcept { return m_sprite.getPosition().x; }

float City::getY() const noexcept { return m_sprite.getPosition().y; }

float City::getTop() const noexcept {
	return getY() - ( C_BALL_H / 2.f );
}

float City::getBottom() const noexcept {
	return getY() + ( C_BALL_H / 2.f );
}

float City::getLeft() const noexcept {
	return getX();
}

float City::getRight() const noexcept {
	return getX() + m_width;
}

// ===================================80 chars==================================
/* EOF */


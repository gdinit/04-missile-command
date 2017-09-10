/* mc_terrain.cc */
// ===================================80 chars==================================

#include "mc_terrain.h"

Terrain::Terrain()
	: m_myObjNameStr( "terrain" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
	// SET UP SPRITE
	// m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( m_dimension.x / 2.f, m_dimension.y / 2.f );
	m_sprite.setPosition( m_windowSize.x / 2, m_windowSize.y / 2 );
}

Terrain::~Terrain()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Terrain::update( sf::Time timeSinceLastUpdate, sf::Vector2f res )
{
}

void Terrain::update( sf::Time timeSinceLastUpdate, sf::Vector2f r
	, Direction dir, float topBarBottomEdge, float leftBarRightEdge, float
	bottomBarTopEdge
	, float
	rightBarLE )
{
	#if defined DBG
	std::cout << "Terrain x,y: " << getX() << "," << getY() <<
	"\t xMultiplierRatio = " << ( getX() / m_windowSize.x )	<<
	"\t\t yMultiplierRatio = " << ( getY() / m_windowSize.y ) << "\n";
	#endif
}

void Terrain::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " << "newRound(" <<
	res.x << "," << res.y << ") has been triggered.\n";
	#endif
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
	makeTerrain( res );
}

void Terrain::draw( sf::RenderTarget &target, sf::RenderStates states )
const {
	target.draw( m_sprite );
}

void Terrain::makeTerrain( sf::Vector2f res ) noexcept {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") Making terrain...\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end();
	      ++it ) {
		if ( it.key() == "terrainXPosRatio" ) {
			m_terrainXPosRatio = it.value();
		} else if ( it.key() == "terrainYPosRatio" ) {
			m_terrainYPosRatio = it.value();
		} else if ( it.key() == "terrainWidthRatio" ) {
			m_terrainWidthRatio = it.value();
		} else if ( it.key() == "terrainHeightRatio" ) {
			m_terrainHeightRatio = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") m_terrainXPosRatio is: " << m_terrainXPosRatio <<
	"\t m_terrainYPosRatio is: " << m_terrainYPosRatio << "\n";
	#endif
	PASSERT(        ( m_terrainXPosRatio > 0 )
		, "ERROR: m_terrainXPosRatio must be > 0!\tIt is: " <<
		m_terrainXPosRatio << "\n" );
	PASSERT(        ( m_terrainYPosRatio > 0 )
		, "ERROR: m_terrainYPosRatio must be > 0!\tIt is: " <<
		m_terrainYPosRatio << "\n" );
	m_position.x = m_windowSize.x * m_terrainXPosRatio;
	m_position.y = m_windowSize.y * m_terrainYPosRatio;
	m_dimension.x = m_windowSize.x * m_terrainWidthRatio;
	m_dimension.y = m_windowSize.y * m_terrainHeightRatio;
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") \tCalculated" <<
	" position as: " << m_position.x << "," << m_position.y << "\t"	<<
	"[DEBUG]\tCalculated " << m_myObjNameStr << " size as w: " <<
	m_dimension.x << "\t h: " << m_dimension.y << "\n";
	#endif
	// m_texture.loadFromFile( "assets/textures/640x64_terrain.png" );
	m_texture.loadFromFile( "assets/textures/terrain_633x63.png" );
	m_sprite.setTexture( m_texture, true );
	m_sprite.setPosition( m_position.x, m_position.y );
	// m_sprite.setColor( sf::Color( sf::Color::Black ) );
}

float Terrain::getX() const noexcept {
	return m_sprite.getPosition().x;
}

float Terrain::getY() const noexcept {
	return m_sprite.getPosition().y;
}

float Terrain::getTop() const noexcept {
	return getY() - ( m_dimension.y / 2.f );
}

float Terrain::getBottom() const noexcept {
	return getY() + ( m_dimension.y / 2.f );
}

float Terrain::getLeft() const noexcept {
	return getX() - ( m_dimension.x / 2.f );
}

float Terrain::getRight() const noexcept {
	return getX() + ( m_dimension.x / 2.f );
}

// ===================================80 chars==================================
/* EOF */


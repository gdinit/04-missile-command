#include "mc_gun_indicator.h"

GunIndicator::GunIndicator()
	: m_myObjNameStr( "GunIndicator" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
	// Assign Bad Define Values (to be caught by PASSERT if not overriden)
	m_defGunIndicatorW = -999;
	m_defAAGPointerH = -999;
	m_defAAGPointerV = -999;
	// JSON
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
		if ( it.key() == "MC_AAG_Pointer_W" ) {
			m_defGunIndicatorW = it.value();
		} else if ( it.key() == "MC_AAG_Pointer_H" ) {
			m_defAAGPointerH = it.value();
		} else if ( it.key() == "MC_AAG_Pointer_V" ) {
			m_defAAGPointerV = it.value();
		}
	}
	i.close();
	std::cout << "[TMP]\tm_defGunIndicatorW is: " << m_defGunIndicatorW << "\n";
	std::cout << "[TMP]\tm_defAAGPointerH is: " << m_defAAGPointerH << "\n";
	std::cout << "[TMP]\tm_defAAGPointerV is: " << m_defAAGPointerV << "\n";

	// Production Assert - ensure JSON loaded fine
	PASSERT(        ( m_defGunIndicatorW != -999 )
		, "ERROR: m_defGunIndicatorW cannot be -999!\n" );
	PASSERT(        ( m_defAAGPointerH != -999 )
		, "ERROR: m_defAAGPointerH cannot be -999!\n" );
	PASSERT(        ( m_defAAGPointerV != -999 )
		, "ERROR: m_defAAGPointerV cannot be -999!\n" );

	// SET UP SPRITE
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( 0, 0, m_defGunIndicatorW
			, m_defAAGPointerH ) );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( m_defAAGPointerH / 2.f, m_defGunIndicatorW / 2.f );
	// m_sprite.setPosition( 0, 0 );
	m_sprite.setPosition( m_windowSize.x / 2, m_windowSize.y / 2 );
	m_velocity.x = 0.f;
	m_velocity.y = 0.f;
}

GunIndicator::~GunIndicator()
{
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void GunIndicator::update( sf::Time timeSinceLastUpdate, sf::Vector2f r
	, Direction dir, float topBarBE, float leftBarRE, float bottomBarTE
	, float
	rightBarLE )
{
	/*
	THESE ARE COMING FROM:

	paddle.update( timeSinceLastUpdate, res, dir, leftBar.getRight()
	, rightBar.getLeft() );
	*/

	// TODO update this -- dir to be removed? to be extended?
	manageMovement( r, dir, topBarBE, leftBarRE, bottomBarTE, rightBarLE );
	//
	// #if defined DBG
	// std::cout << "Paddle bottom: " << getBottom() << "\n";
	// #endif

	//// calculate next step
	// sf::Vector2f	moveDistance;
	// moveDistance.x = ( m_velocity.x * m_defAAGPointerV ) *
	// timeSinceLastUpdate.asMilliseconds();
	// moveDistance.y = ( m_velocity.y * m_defAAGPointerV ) *
	// timeSinceLastUpdate.asMilliseconds();

	//// 'normal' values go as low|high as N
	// float		CLAMPMAXVALPOS = 5.f;
	// float		CLAMPMAXVALNEG = -5.f;
	//// clamp X
	// if ( moveDistance.x > CLAMPMAXVALPOS ) {
	// moveDistance.x = CLAMPMAXVALPOS;
	// } else if ( moveDistance.x < CLAMPMAXVALNEG ) {
	// moveDistance.x = CLAMPMAXVALNEG;
	// }
	//// clamp Y
	// if ( moveDistance.y > CLAMPMAXVALPOS ) {
	// moveDistance.y = CLAMPMAXVALPOS;
	// } else if ( moveDistance.y < CLAMPMAXVALNEG ) {
	// moveDistance.y = CLAMPMAXVALNEG;
	// }

	//// Now, we can move.
	// m_sprite.move( moveDistance );
}

void GunIndicator::manageMovement( sf::Vector2f res, Direction dir
	, float topBarBE, float leftBarRE, float bottomBarTE, float rightBarLE )
{
	// Notes:
	// 1. maybe we will move, maybe we wont...
	// 2. SinglePlayer game demo scene can have a computerControlled paddle
	// 3. instructed by player or AI don't matter, in any case a request is
	// passed or not
	m_requestedMoveDistance.x = ( 0.f );
	m_requestedMoveDistance.y = ( 0.f );

	// TODO add a meaningful enum here
	switch ( dir ) {
		case Direction::UP:
			// move up requested. validate & action (if legal!)
			m_requestedMoveDistance.y = MC_GUN_INDICATOR_MOVSTEP *
				-1.f;
			valAndActionMove( res, dir, topBarBE, leftBarRE
			, bottomBarTE, rightBarLE );
			break;
		case Direction::LEFT:
			// move left requested. validate & action (if legal!)
			m_requestedMoveDistance.x = MC_GUN_INDICATOR_MOVSTEP *
				-1.f;
			valAndActionMove( res, dir, topBarBE, leftBarRE
			, bottomBarTE, rightBarLE );
			break;
		case Direction::DOWN:
			// move up requested. validate & action (if legal!)
			m_requestedMoveDistance.y = MC_GUN_INDICATOR_MOVSTEP;
			valAndActionMove( res, dir, topBarBE, leftBarRE
			, bottomBarTE, rightBarLE );
			break;
		case Direction::RIGHT:
			// move right requested. validate & action (if legal!)
			m_requestedMoveDistance.x = MC_GUN_INDICATOR_MOVSTEP;
			valAndActionMove( res, dir, topBarBE, leftBarRE
			, bottomBarTE, rightBarLE );
			break;
		case Direction::NONE:
		default:
			// no movement
			break;
	}
}

void GunIndicator::valAndActionMove( sf::Vector2f res, Direction dir, float
	topBarBE, float leftBarRE, float bottomBarTE, float rightBarLE ) {
	PASSERT( ( dir == Direction::UP || dir == Direction::LEFT || dir ==
		   Direction::DOWN || dir == Direction::RIGHT )
		, "dir can be LEFT or RIGHT!\n" );
	if ( dir == Direction::UP ) {
		if ( getTop() > topBarBE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::LEFT ) {
		if ( getLeft() > ( leftBarRE + m_defGunIndicatorW ) ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::DOWN ) {
		if ( getBottom() < bottomBarTE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::RIGHT ) {
		if ( getRight() < rightBarLE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	}
}

void GunIndicator::draw( sf::RenderTarget &target, sf::RenderStates states )
const {
	// draw to be done by Arena
}

void GunIndicator::newRound( sf::Vector2f res ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " << "newRound(" <<
	res.x << "," << res.y << ") has been triggered.\n";
	#endif
	// place the object for new round -- ball goes to the centre
	// m_sprite.setPosition( res.x / 2.f, res.y * 0.75f );
	m_sprite.setPosition( res.x / 2.f, res.y / 2.f );
	// save for future use
	m_windowSize.x = res.x;
	m_windowSize.y = res.y;
}

float GunIndicator::getX() const noexcept {
	return m_sprite.getPosition().x;
}

float GunIndicator::getY() const noexcept {
	return m_sprite.getPosition().y;
}

float GunIndicator::getTop() const noexcept {
	return getY() - ( m_defAAGPointerH / 2.f );
}

float GunIndicator::getBottom() const noexcept {
	return getY() + ( m_defAAGPointerH / 2.f );
}

float GunIndicator::getLeft() const noexcept {
	return getX() - ( m_defGunIndicatorW / 2.f );
}

float GunIndicator::getRight() const noexcept {
	return getX() + ( m_defGunIndicatorW / 2.f );
}
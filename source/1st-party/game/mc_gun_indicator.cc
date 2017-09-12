/* mc_gun_indicator.cc */
// ===================================80 chars==================================

#include "mc_gun_indicator.h"

GunIndicator::GunIndicator()
	: m_myObjNameStr( "GunIndicator" )
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	#endif
	std::ifstream	i( "data/defines.json" );
	nlohmann::json	j;
	i >> j;
	for ( nlohmann::json::iterator it = j.begin(); it != j.end(); ++it ) {
		if ( it.key() == "gunIndicatorW" ) {
			m_gunIndicatorW = it.value();
		} else if ( it.key() == "gunIndicatorH" ) {
			m_gunIndicatorH = it.value();
		} else if ( it.key() == "gunIndicatorV" ) {
			m_gunIndicatorV = it.value();
		} else if ( it.key() == "GunIndicatorMovStep" ) {
			m_gunIndicatorMovStep = it.value();
		}
	}
	i.close();
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr <<
	") \t m_gunIndicatorW is: " << m_gunIndicatorW <<
	"\t m_gunIndicatorH: " << m_gunIndicatorH << "\t m_gunIndicatorV: " <<
	m_gunIndicatorV << "\n";
	#endif
	PASSERT(        ( m_gunIndicatorW > 0 )
		, "ERROR: m_gunIndicatorW must be > 0!\n" );
	PASSERT(        ( m_gunIndicatorH > 0 )
		, "ERROR: m_gunIndicatorH must be > 0!\n" );
	PASSERT(        ( m_gunIndicatorV > 0 )
		, "ERROR: m_gunIndicatorV must be > 0!\n" );
	// SET UP SPRITE
	m_sprite.setTexture( m_texture );
	m_sprite.setTextureRect( sf::IntRect( 0, 0, m_gunIndicatorW
			, m_gunIndicatorH ) );
	m_sprite.setColor( sf::Color( 120, 104, 112 ) );// gray-ish
	m_sprite.setOrigin( m_gunIndicatorH / 2.f, m_gunIndicatorW / 2.f );
	m_sprite.setPosition( m_windowSize.x / 3, m_windowSize.y / 2 );
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
	, Direction dir, float topBarBottomEdge, float leftBarRightEdge, float
	bottomBarTopEdge
	, float
	rightBarLE )
{
	#if defined DBG
	if ( ( getX() == m_debugGunIndicatorLastPos.x )
	     && ( getY() == m_debugGunIndicatorLastPos.y ) ) {
		// do nothing
	} else {
		m_debugGunIndicatorLastPos.x = getX();
		m_debugGunIndicatorLastPos.y = getY();
		std::cout << "GunIndicator newPos x,y: " << getX() << "," <<
		getY() << "\t xMultiplierRatio = " << ( getX() /
							m_windowSize.x ) <<
		"\t\t yMultiplierRatio = " << ( getY() /
						m_windowSize
						.
						y )
		<< "\n";
	}
	#endif

	/*
	THESE ARE COMING FROM:

	paddle.update( timeSinceLastUpdate, res, dir, leftBar.getRight()
	, rightBar.getLeft() );
	*/

	// TODO update this -- dir to be removed? to be extended?
	manageMovement( r, dir, topBarBottomEdge, leftBarRightEdge
		, bottomBarTopEdge, rightBarLE );
	//
	// #if defined DBG
	// std::cout << "Paddle bottom: " << getBottom() << "\n";
	// #endif

	//// calculate next step
	// sf::Vector2f	moveDistance;
	// moveDistance.x = ( m_velocity.x * gunIndicatorV ) *
	// timeSinceLastUpdate.asMilliseconds();
	// moveDistance.y = ( m_velocity.y * gunIndicatorV ) *
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

void GunIndicator::manageMovement( sf::Vector2f res, Direction dir
	, float topBarBottomEdge, float leftBarRightEdge, float
	bottomBarTopEdge, float rightBarLE )
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
			m_requestedMoveDistance.y = m_gunIndicatorMovStep *
				-1.f;
			valAndActionMove( res, dir, topBarBottomEdge
			, leftBarRightEdge
			, bottomBarTopEdge, rightBarLE );
			break;
		case Direction::LEFT:
			// move left requested. validate & action (if legal!)
			m_requestedMoveDistance.x = m_gunIndicatorMovStep *
				-1.f;
			valAndActionMove( res, dir, topBarBottomEdge
			, leftBarRightEdge
			, bottomBarTopEdge, rightBarLE );
			break;
		case Direction::DOWN:
			// move up requested. validate & action (if legal!)
			m_requestedMoveDistance.y = m_gunIndicatorMovStep;
			valAndActionMove( res, dir, topBarBottomEdge
			, leftBarRightEdge
			, bottomBarTopEdge, rightBarLE );
			break;
		case Direction::RIGHT:
			// move right requested. validate & action (if legal!)
			m_requestedMoveDistance.x = m_gunIndicatorMovStep;
			valAndActionMove( res, dir, topBarBottomEdge
			, leftBarRightEdge
			, bottomBarTopEdge, rightBarLE );
			break;
		case Direction::NONE:
		default:
			break;
	}
}

// THIS IS THE ACTUAL ONE WHICH DOES CHECKS. DISABLE FOR TROUBLESHOOTING
void GunIndicator::valAndActionMove( sf::Vector2f res, Direction dir, float
	topBarBottomEdge, float leftBarRightEdge, float bottomBarTopEdge, float
	rightBarLE ) {
	PASSERT( ( dir == Direction::UP || dir == Direction::LEFT || dir ==
		   Direction::DOWN || dir == Direction::RIGHT )
		, "dir can be UP, LEFT, DOWN, or RIGHT!\n" );
	if ( dir == Direction::UP ) {
		if ( getTop() > topBarBottomEdge ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::LEFT ) {
		if ( getLeft() > leftBarRightEdge ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::DOWN ) {
		if ( getBottom() < bottomBarTopEdge ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	} else if ( dir == Direction::RIGHT ) {
		if ( getRight() < rightBarLE ) {
			m_sprite.move( m_requestedMoveDistance );
		}
	}
}

//// TODO: remove this code DEBUG ONLY CODE -- MOVE WITNHOUT RESTRAINTS
// void GunIndicator::valAndActionMove( sf::Vector2f res, Direction dir, float
// topBarBottomEdge, float leftBarRightEdge, float bottomBarTopEdge, float
// rightBarLE ) {
// PASSERT( ( dir == Direction::UP || dir == Direction::LEFT || dir ==
// Direction::DOWN || dir == Direction::RIGHT )
// , "dir can be LEFT or RIGHT!\n" );
// if ( dir == Direction::UP ) {
// m_sprite.move( m_requestedMoveDistance );
// } else if ( dir == Direction::LEFT ) {
// m_sprite.move( m_requestedMoveDistance );
// } else if ( dir == Direction::DOWN ) {
// m_sprite.move( m_requestedMoveDistance );
// } else if ( dir == Direction::RIGHT ) {
// m_sprite.move( m_requestedMoveDistance );
// }
// }

void GunIndicator::draw( sf::RenderTarget &target, sf::RenderStates states )
const {
	target.draw( m_sprite );
}

float GunIndicator::getX() const noexcept {
	return m_sprite.getPosition().x;
}

float GunIndicator::getY() const noexcept {
	return m_sprite.getPosition().y;
}

float GunIndicator::getTop() const noexcept {
	return getY() - ( m_gunIndicatorH / 2.f );
}

float GunIndicator::getBottom() const noexcept {
	return getY() + ( m_gunIndicatorH / 2.f );
}

float GunIndicator::getLeft() const noexcept {
	return getX() - ( m_gunIndicatorW / 2.f );
}

float GunIndicator::getRight() const noexcept {
	return getX() + ( m_gunIndicatorW / 2.f );
}

// ===================================80 chars==================================
/* EOF */


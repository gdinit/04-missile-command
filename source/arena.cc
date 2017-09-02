/* arena.cc */
// ===================================80 chars==================================

#include "arena.h"

// Required for lives etc.	TOOD remove this global
extern std::unique_ptr <Globals> GLOBALS;

// For ImpactZone debug cout
template<typename T>
std::ostream & operator <<( typename std::enable_if <std::is_enum <T>::value
		, std::ostream>::type &stream, const T &e )
{
	return stream << static_cast <typename
	std::underlying_type <T>::type> ( e );
}

Arena::Arena()
	: m_myObjNameStr( "Arena" )
	, m_hgPaddle{ 0 }
	, m_hgTopBar{ 0 }
	, m_hgLeftBar{ 0 }
	, m_hgRightBar{ 0 }
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	std::cout << "[DEBUG]\tIN PROGRESS: Loading textures..." <<
	m_myObjNameStr << "\n";
	#endif
	if ( !m_squareTexture.loadFromFile(
		     "assets/textures/texturepak.png" ) ) {
		std::cout << "\nERROR while attempting to load a resource!\n";
		exit( EXIT_FAILURE );
	}
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Loaded textures." << m_myObjNameStr <<
	"\n";
	std::cout << "[DEBUG]\tIN PROGRESS: Loading sounds..." <<
	m_myObjNameStr << "\n";
	#endif
	if ( !m_sndbfColPaddle.loadFromFile(
		     "assets/sounds/collision1.wav" ) ) {
		std::cout << "\nERROR while attempting to load a resource!\n";
		exit( EXIT_FAILURE );
	}
	m_soundColPaddle.setBuffer( m_sndbfColPaddle );
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Loaded sounds." << m_myObjNameStr <<
	"\n";
	#endif
}

Arena::~Arena() {
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Arena::update( sf::Time timeSinceLastUpdate, sf::Vector2f res, Direction
	dir ) {
	// Hourglass decrements
	if ( m_hgPaddle > 0 ) {
		--m_hgPaddle;
	}
	if ( m_hgTopBar > 0 ) {
		--m_hgTopBar;
	}
	if ( m_hgLeftBar > 0 ) {
		--m_hgLeftBar;
	}
	if ( m_hgRightBar > 0 ) {
		--m_hgRightBar;
	}
	paddle.update( timeSinceLastUpdate, res, dir, leftBar.getRight()
		, rightBar.getLeft() );
	ball.update( timeSinceLastUpdate, res );
	paintCells();
	colDetRespond();
	for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
		if ( m_cDetDB.at( n ).visible == 0 ) {
			// TODO switch to switch statement here for efficiency?
			// TODO fix the texturepak coords -> 14,40,68,94,122,150
			if ( m_cDetDB.at( n ).cellType == 0 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 14, 0
						, 1
						, 1 ) );
			} else if ( m_cDetDB.at( n ).cellType == 1 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 40, 0
						, 1
						, 1 ) );
			} else if ( m_cDetDB.at( n ).cellType == 2 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 68, 0
						, 1
						, 1 ) );
			} else if ( m_cDetDB.at( n ).cellType == 3 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 94, 0
						, 1
						, 1 ) );
			} else if ( m_cDetDB.at( n ).cellType == 4 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 122
						, 0, 1
						, 1 ) );
			} else if ( m_cDetDB.at( n ).cellType == 5 ) {
				m_cSDB [ n ].setTextureRect( sf::IntRect( 150
						, 0, 1
						, 1 ) );
			}
		}
	}
}

void Arena::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	target. draw(	topBar.m_sprite );
	target. draw(	leftBar.m_sprite );
	target. draw(	rightBar.m_sprite );
	target. draw(	paddle.m_sprite );
	for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
		if ( m_cDetDB [ n ].HP > 0 && m_cDetDB [ n ].visible &&
		     m_cDetDB [ n ].phantom != 1 ) {
			target.draw( m_cSDB [ n ] );
		}
	}
	target.draw( ball.m_sprite );
}

void Arena::newRound( sf::Vector2f res, int32 level ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tLevel is: " << level << "\n";
	#endif
	m_tmpRes = res;
	topBar.newRound( res );
	leftBar.newRound( res );
	rightBar.newRound( res );
	createCells( res, level );
	paddle.newRound( res );
	ball.newRound( res );
	// Hourglass resets
	m_hgPaddle = 0;
	m_hgTopBar = 0;
	m_hgLeftBar = 0;
	m_hgRightBar = 0;
}

void Arena::createCells( sf::Vector2f res, int32 level ) {
	if ( level != 1 ) {
		std::cout << "\nERROR Only game level LEVEL 1 has been "
		"implemented so far. Sorry! :(	\n";
		// TODO	add a pause here (disappears in some setups e.g. VS15)
		exit( EXIT_FAILURE );
	}
	m_brickSize.x = res.x * CEXPR_BRWRATIO;
	m_brickSize.y = res.x * CEXPR_BRHRATIO;
	// CREATE LEVEL:	LEVEL 1
	////////////////////////////////////////
	// LEVEL RULES:	Level 1
	// Brick Color Policy	: Row colors top to bottom
	// Brick HP Policy	: All bricks 1 HP
	// Brick Style Variation: All bricks Type0 (not in use) TODO
	////////////////////////////////////////
	#if defined DBG
	std::cout << "[DEBUG]\tIN PROGRESS: Creating cells in the database for"
	" level=" << level << " // " << m_myObjNameStr << "\n";
	#endif
	// LOCALS
	// calculate pos for brickRow00,Column00 (left top)
	sf::Vector2f	b0000pos;
	b0000pos.x = ( res.x * CEXPR_BRPXRATIO );
	b0000pos.y = ( res.y * CEXPR_BRPYRATIO );
	// Current Brick Pos
	sf::Vector2f	cbp;
	cbp.x = 0.f;
	cbp.y = b0000pos.y;
	m_cDetDB.clear();
	m_cSDB.clear();
	int32		rowCounter = 0, curRow = 0, curColumn = 0;

	for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
		if ( rowCounter == CONFIG_COLUMNS ) {
			curRow++;
			rowCounter = 0;
		}
		curColumn = n % CONFIG_COLUMNS;
		// tr = Temporary Record
		CellDetails	tr;
		int32		tmpid = n;
		tr.cellNumericId = tmpid;
		if ( n == 0 || n < 16 ) {
			tr.cellType = CELLTYPE0;
		} else if ( n == 16 || n < 32 ) {
			tr.cellType = CELLTYPE1;
		} else if ( n == 32 || n < 48 ) {
			tr.cellType = CELLTYPE2;
		} else if ( n == 48 || n < 64 ) {
			tr.cellType = CELLTYPE3;
		} else if ( n == 64 || n < 80 ) {
			tr.cellType = CELLTYPE4;
		} else if ( n == 80 || n < 96 ) {
			tr.cellType = CELLTYPE5;
		}
		m_cDetDB.emplace_back( tr );
		m_cSDB.emplace_back( sf::Sprite( m_squareTexture ) );

		// visible while debugging // TODO fixme
		tr.HP = 1;
		// calculate X
		cbp.x = b0000pos.x + ( curColumn * m_brickSize.x );
		// calculate Y
		cbp.y = b0000pos.y + ( m_brickSize.y * curRow );

		// setColor
		m_cSDB [ n ].setTextureRect
			( sf::IntRect( 64, 0, 1, 1 ) );

		// scale
		m_cSDB [ n ].scale( ( m_brickSize.x ), ( m_brickSize.y ) );
		m_cSDB [ n ].setPosition( cbp );
		#if defined DBG
		std::cout.setf( std::ios::fixed, std::ios::floatfield );
		std::cout.precision( 3 );
		std::cout << "[DEBUG]\tCreated entry in DB:\t" << tmpid << "\t"
		"Cell type:\t" << tr.cellType << "\tcbp[" << n <<
		"] setPos to:\t" << cbp.x << "," << cbp.y << "\n";
		#endif
		++rowCounter;
	}
	#if defined DBG
	std::cout <<
	"[DEBUG]\tCOMPLETED: Creating cells in the database, for level=" <<
	level << " // " << m_myObjNameStr << "\n";
	#endif
}

void Arena::paintCells( void )
{
	for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
		if ( m_cDetDB.at( n ).cellType == 0 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 14, 0, 1
					, 1 ) );
		} else if ( m_cDetDB.at( n ).cellType == 1 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 40, 0, 1
					, 1 ) );
		} else if ( m_cDetDB.at( n ).cellType == 2 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 68, 0, 1
					, 1 ) );
		} else if ( m_cDetDB.at( n ).cellType == 3 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 94, 0, 1
					, 1 ) );
		} else if ( m_cDetDB.at( n ).cellType == 4 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 122, 0, 1
					, 1 ) );
		} else if ( m_cDetDB.at( n ).cellType == 5 ) {
			m_cSDB [ n ].setTextureRect( sf::IntRect( 150, 0, 1
					, 1 ) );
		}
	}
}

// COLLISION:	DETECT & RESPOND
void Arena::colDetRespond( void )
{
	colDetRespondBallWall();
	colDetRespondBallPaddle();
	colDetRespondBallGoal();
	colDetRespondBallCell();
}

// Collision Detection & Response:	Ball->Wall
void Arena::colDetRespondBallWall( void )
{
	// Ball hit a Wall?
	sf::FloatRect	bbBall = ball.m_sprite.getGlobalBounds();
	sf::FloatRect	bboxTopBar = topBar.m_sprite.getGlobalBounds();
	sf::FloatRect	bboxLeftBar = leftBar.m_sprite.getGlobalBounds();
	sf::FloatRect	bboxRightBar = rightBar.m_sprite.getGlobalBounds();

	if ( bbBall.intersects( bboxTopBar ) && m_hgTopBar <= 0 ) {
		// TOP BAR
		// Must not collide again for a short while
		m_hgTopBar = 10;
		m_soundColPaddle.play();
		// SIMPLISTIC BOUNCE BACK
		ball.m_velocity.y = -ball.m_velocity.y;
	} else if ( bbBall.intersects( bboxLeftBar ) && m_hgLeftBar <= 0 ) {
		// LEFT BAR
		m_hgLeftBar = 10;
		m_soundColPaddle.play();
		// SIMPLISTIC BOUNCE BACK
		ball.m_velocity.x = -ball.m_velocity.x;
	} else if ( bbBall.intersects( bboxRightBar ) && m_hgRightBar <= 0 ) {
		// RIGHT BAR
		m_hgRightBar = 10;
		m_soundColPaddle.play();
		// SIMPLISTIC BOUNCE BACK
		ball.m_velocity.x = -ball.m_velocity.x;
	}
}

// Collision Detection & Response:	Ball->Paddle
void Arena::colDetRespondBallPaddle( void )
{
	// TODO move move bit, in to a function calcuateNewMovementVector()

	// Ball hit the Paddle?
	sf::FloatRect	bbBall = ball.m_sprite.getGlobalBounds();
	sf::FloatRect	bboxPaddle = paddle.m_sprite.getGlobalBounds();

	if ( bbBall.intersects( bboxPaddle )
	     && ( m_hgPaddle <= 0 )
	     && ( ball.m_velocity.y >= 0 ) ) {
		m_soundColPaddle.play();
		// Must not collide again for a short while
		m_hgPaddle = 10;
		float		bX = ball.getX();
		float		pLeftX = paddle.getLeft();
		float		pRightX = paddle.getRight();
		float		pWidth = pRightX - pLeftX;
		// 1	     2 3	  4 5	      6
		// [ZONE LEFT][ZONE CENTRE][ZONE RIGHT]
		// [   P     A     D     D     L    E ]
		float		pZSlice = pWidth / 3.f;
		// paddleZoneLeft
		float		pZLLeftEdge = pLeftX;
		// paddleZoneCenter
		float		pZCLeftEdge = pLeftX + pZSlice;
		// paddleZoneRight
		float		pZRLeftEdge = pLeftX + pZSlice + pZSlice;
		float		pZRRightEdge = pRightX;

		// Which zone did the ball hit?
		ImpactZone	iZone = ImpactZone::NONE;
		if ( bX >= pZLLeftEdge && bX < pZCLeftEdge ) {
			iZone = ImpactZone::LEFT;
		} else if ( bX >= pZCLeftEdge && bX < pZRLeftEdge ) {
			iZone = ImpactZone::CENTER;
		} else if ( bX >= pZRLeftEdge && bX <= pZRRightEdge ) {
			iZone = ImpactZone::RIGHT;
		}
		#if defined DBG
		std::cout << "[DEBUG]\tImpact Zone is: " << iZone << "\tbX=" <<
		bX << "\n";
		switch ( iZone ) {
			// left & right = 6 degree variation to left/right
			// center = 3 degree variation to left/right
			case ImpactZone::LEFT:
				std::cout <<
				"[DEBUG]\tBall hit the LEFT zone!\n";
				break;
			case ImpactZone::CENTER:
				std::cout <<
				"[DEBUG]\tBall hit the CENTER zone!\n";
				break;
			case ImpactZone::RIGHT:
				std::cout <<
				"[DEBUG]\tBall hit the RIGHT zone!\n";
				break;
			default:
				break;
		}
		sf::Vector2f				ballOldVel =
			ball.m_velocity;
		std::cout << "[DEBUG]\tballOldVel: " << ballOldVel.y << "\n";
		#endif
		sf::Vector2f				ballNewVel =
			ball.m_velocity;
		std::mt19937				mt1;
		auto					seed1 =
			std::chrono::high_resolution_clock::now().
			time_since_epoch().
			count();
		mt1.seed( ( unsigned long )seed1 );
		std::uniform_real_distribution <>	dist1(
			BR_BOUNCE_CHANCE_HIGHN, BR_BOUNCE_CHANCE_HIGHP );
		std::uniform_real_distribution <>	dist2(
			BR_BOUNCE_CHANCE_LOWN, BR_BOUNCE_CHANCE_LOWP );
		/*
		std::uniform_real_distribution <> dist1( BR_BOUNCE_CHANCE_LOWN,
		BR_BOUNCE_CHANCE_LOWP );
		*/
		// BOUNCE BACK
		switch ( iZone ) {
			// left & right = 6 degree variation to left/right
			// center = 3 degree variation to left/right
			case ImpactZone::LEFT:
				ballNewVel.y = ballNewVel.y + dist1( mt1 );
				// Now, reverse the Y direction:
				ballNewVel.y *= -1;
				ball.m_velocity = ballNewVel;
				break;
			case ImpactZone::CENTER:
				ballNewVel.y = ballNewVel.y + dist2( mt1 );
				// Now, reverse the Y direction:
				ballNewVel.y *= -1;
				ball.m_velocity = ballNewVel;
				break;
			case ImpactZone::RIGHT:
				ballNewVel.y = ballNewVel.y + dist1( mt1 );
				// Now, reverse the Y direction:
				ballNewVel.y *= -1;
				ball.m_velocity = ballNewVel;
				break;
			default:
				break;
		}
		#if defined DBG
		std::cout << "[DEBUG]\tballNewVel: " << ballNewVel.y << "\n";
		#endif
		// normalize the velocity vector
		sf::Vector2f ballNewVelNormalized = normalize( ballNewVel );
		ball.m_velocity = ballNewVelNormalized;
		#if defined DBG
		std::cout << "[DEBUG]\tballNewVelNormalized: " <<
		ballNewVelNormalized.y << "\tX is:" << ballNewVelNormalized.x <<
		"\n\n";
		#endif
	}
}

// Collision Detection & Response:	Ball->Goal line
void Arena::colDetRespondBallGoal( void )
{
	if ( ball.getY() > paddle.getBottom() ) {
		m_soundColPaddle.play();

		if ( GLOBALS->livesLeft > 0 ) {
			GLOBALS->livesLeft--;
			newRound( m_tmpRes, 1 );
		} else {
			// Game over!
			GLOBALS->returnToMainMenuRequested = 1;
		}
	}
}

// Collision Detection & Response:	Ball->Cell
void Arena::colDetRespondBallCell( void )
{
	bool		noHitsYet = 1;
	sf::FloatRect	bbBall = ball.m_sprite.getGlobalBounds();
	// check each relevant cell, until a hit is found
	for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL && noHitsYet;
	      ++n ) {
		// to collide, cell must be alive (HP>0) && must NOT be phantom
		if ( m_cDetDB [ n ].HP > 0 && m_cDetDB [ n ].phantom != 1 ) {
			sf::FloatRect bbCell = m_cSDB [ n ].getGlobalBounds();
			if ( bbBall.intersects( bbCell ) ) {
				// TODO consider adding hourglass here
				m_soundColPaddle.play();
				// SIMPLISTIC BOUNCE BACK
				ball.m_velocity.y = -ball.m_velocity.y;
				// kill this cell
				m_cDetDB [ n ].HP = 0;
				GLOBALS->currentScore++;
				noHitsYet = 0;
			}
		}
	}
}

// ===================================80 chars==================================
/* EOF */


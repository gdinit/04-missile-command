/* mc_arena.cc */
// ===================================80 chars==================================

#include "mc_arena.h"

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
{
	#if defined DBG
	std::cout << "[DEBUG]\tCreated object:\t\t" << m_myObjNameStr << "\n";
	std::cout << "[DEBUG]\tIN PROGRESS: Loading textures..." <<
	m_myObjNameStr << "\n";
	#endif
	// if ( !m_squareTexture.loadFromFile(
	// "assets/textures/texturepak.png" ) ) {
	// std::cout << "\nERROR while attempting to load a resource!\n";
	// exit( EXIT_FAILURE );
	// }
	#if defined DBG
	// std::cout << "[DEBUG]\tSUCCESS: Loaded textures." << m_myObjNameStr
	// <<
	// "\n";
	// std::cout << "[DEBUG]\tIN PROGRESS: Loading sounds..." <<
	// m_myObjNameStr << "\n";
	#endif
	// if ( !m_sndbfColPaddle.loadFromFile(
	// "assets/sounds/collision1.wav" ) ) {
	// std::cout << "\nERROR while attempting to load a resource!\n";
	// exit( EXIT_FAILURE );
	// }
	// m_soundColPaddle.setBuffer( m_sndbfColPaddle );
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Loaded sounds." << m_myObjNameStr <<
	"\n";
	#endif

	// ECS Test
	// ecsTest2();
	std::cout << "EntityComponentSystem Test #2" << std::endl <<
	"==========================" << std::endl;

	{
		using namespace ECS;

		class TestSystem : public EntitySystem, public
				 EventSubscriber <Events::OnEntityCreated>
				 , public
				 EventSubscriber <Events::OnEntityDestroyed>
				 , public
				 EventSubscriber <SomeEvent>
		{
			public:
				virtual ~TestSystem() {}

				virtual void configure( class
					World* world ) override
				{
					world-> subscribe <Events::
						OnEntityCreated> (	this );
					world-> subscribe <Events::
						OnEntityDestroyed> (	this );
					world-> subscribe <SomeEvent> (
						this );
				}

				virtual void unconfigure( class
					World* world ) override
				{
					world->unsubscribeAll( this );
				}

				virtual void tick( class World* world, float
					deltaTime )
				override {
					world->each <Position, Rotation>
						( [ & ] ( Entity* ent
							  , ComponentHandle <
								  Position> pos
							  , ComponentHandle <
								  Rotation> rot )
						-> void
						{
							pos->x += deltaTime;
							pos->y += deltaTime;
							rot->angle +=
								deltaTime * 2;
						}
						);
				}

				virtual void receive( class World* world, const
					Events::OnEntityCreated &event )
				override
				{
					std::cout << "An entity was created!" <<
					std::endl;
				}

				virtual void receive( class World* world, const
					Events::OnEntityDestroyed &event )
				override
				{
					std::cout <<
					"An entity was destroyed!" << std::endl;
				}

				virtual void receive( class World* world, const
					SomeEvent &event ) override
				{
					std::cout <<
					"I received SomeEvent with value " <<
					event.num << "!" << std::endl;
					world->all( [ & ] (
							Entity* ent ) {
							if ( ent->getEntityId()
							     + 1 ==
							     event.num ) {
								world->destroy(
									world->
									getById(
										event
										.
										num ) );
							}
							if (
								ent->getEntityId()
								==
								event.num ) {
								std::cout <<
								"Woah, we " <<
								"shouldn't get here!"
								<< "\n";
							}
						} );
				}
		};

		ECS::World*	world = World::createWorld();

		world->registerSystem( new TestSystem() );

		Entity*		ent = world->create();
		auto		pos = ent->assign <Position> ( 0.f, 0.f );
		auto		rot = ent->assign <Rotation> ( 0.f );
		std::cout << "We have " << world->getCount() <<
		" entities right now." << std::endl;
	}
}

Arena::~Arena() {
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Arena::update( sf::Time timeSinceLastUpdate, sf::Vector2f res, Direction
	dir ) {
	//// Hourglass decrements
	// if ( m_hgPaddle > 0 ) {
	// --m_hgPaddle;
	// }
	// if ( m_hgTopBar > 0 ) {
	// --m_hgTopBar;
	// }
	// if ( m_hgLeftBar > 0 ) {
	// --m_hgLeftBar;
	// }
	// if ( m_hgRightBar > 0 ) {
	// --m_hgRightBar;
	// }
	// paddle.update( timeSinceLastUpdate, res, dir, leftBar.getRight()
	// , rightBar.getLeft() );
	gunIndicator.update( timeSinceLastUpdate, res, dir, topBar.getBottom()
		, leftBar.getRight(), bottomBar.getTop(), rightBar.getLeft() );
	// ball.update( timeSinceLastUpdate, res );
	// paintCells();
	// colDetRespond();
}

void Arena::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	// target. draw(	gunIndicator.m_sprite );
	// target. draw(	topBar.m_sprite );
	// target. draw(	bottomBar.m_sprite );
	// target. draw(	rightBar.m_sprite );
	// target. draw(	leftCity.m_sprite, sf::RenderStates::Default );

	leftCity.draw( target, sf::RenderStates::Default );
	middleCity.draw( target, sf::RenderStates::Default );
	rightCity.draw( target, sf::RenderStates::Default );
	topBar.draw( target, sf::RenderStates::Default );
	leftBar.draw( target, sf::RenderStates::Default );
	bottomBar.draw( target, sf::RenderStates::Default );
	rightBar.draw( target, sf::RenderStates::Default );
	gunIndicator.draw( target, sf::RenderStates::Default );
	// target. draw(	paddle.m_sprite );
	// for ( int32 n = CONFIG_FIRSTCELL; n < CONFIG_LASTCELL; ++n ) {
	// if ( m_cDetDB [ n ].HP > 0 && m_cDetDB [ n ].visible &&
	// m_cDetDB [ n ].phantom != 1 ) {
	// target.draw( m_cSDB [ n ] );
	// }
	// }
	// target.draw( ball.m_sprite );
}

void Arena::newRound( sf::Vector2f res, int32 level ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tLevel is: " << level << "\n";
	#endif
	// m_tmpRes = res;
	topBar.newRound( res );
	leftBar.newRound( res );
	bottomBar.newRound( res );
	rightBar.newRound( res );
	gunIndicator.newRound( res );
	leftCity.newRound( res );
	middleCity.newRound( res );
	rightCity.newRound( res );
	gunIndicator.newRound( res );
	// createCells( res, level );
	// paddle.newRound( res );
	// ball.newRound( res );
	//// Hourglass resets
	// m_hgPaddle = 0;
	// m_hgTopBar = 0;
	// m_hgLeftBar = 0;
	// m_hgRightBar = 0;
}

void Arena::createCells( sf::Vector2f res, int32 level ) {
}

void Arena::paintCells( void )
{
}

// COLLISION:	DETECT & RESPOND
void Arena::colDetRespond( void )
{
	// colDetRespondBallWall();
	// colDetRespondBallPaddle();
	// colDetRespondBallGoal();
	// colDetRespondBallCell();
}

// Collision Detection & Response:	Ball->Wall
void Arena::colDetRespondBallWall( void )
{
}

// Collision Detection & Response:	Ball->Paddle
void Arena::colDetRespondBallPaddle( void )
{
}

// Collision Detection & Response:	Ball->Goal line
void Arena::colDetRespondBallGoal( void )
{
}

// Collision Detection & Response:	Ball->Cell
void Arena::colDetRespondBallCell( void )
{
}

// ===================================80 chars==================================
/* EOF */


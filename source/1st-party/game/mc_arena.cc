/* mc_arena.cc */
// ===================================80 chars=================================|

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
	#if defined DBG
	#endif
	#if defined DBG
	std::cout << "[DEBUG]\tSUCCESS: Loaded sounds." << m_myObjNameStr <<
	"\n";
	#endif

	#if defined DBG
	// ECS Test
	// ecsTest2();
	std::cout << "EntityComponentSystem Test #2" << std::endl <<
	"==========================" << std::endl;
	#endif

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
				#if defined DBG
				std::cout << "An entity was created!\n";
				#endif
			}

			virtual void receive( class World* world, const
				Events::OnEntityDestroyed &event )
			override
			{
				std::cout << "An entity was destroyed!" <<
				std::endl;
			}

			virtual void receive( class World* world, const
				SomeEvent &event ) override
			{
				std::cout <<
				"I received SomeEvent with value " <<
				event.num << "!" << std::endl;
				world->all( [ & ] (
						Entity* ent ) {
						if ( ent->getEntityId() + 1 ==
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
							std::cout << "Woah, we " << "shouldn't get here!" << "\n";
						}
					} );
			}
		};

		ECS::World*	world = World::createWorld();

		world->registerSystem( new TestSystem() );

		Entity*		ent = world->create();
		auto		pos = ent->assign <Position> ( 0.f, 0.f );
		auto		rot = ent->assign <Rotation> ( 0.f );
		#if defined DBG
		std::cout << "We have " << world->getCount() <<
		" entities right now.\n";
		#endif
	}
}

Arena::~Arena() {
	#if defined DBG
	std::cout << "[DEBUG]\tDestructed object:\t" << m_myObjNameStr << "\n";
	#endif
}

void Arena::update( sf::Time timeSinceLastUpdate, sf::Vector2f res, Direction
	dir ) {
	gunIndicator.update( timeSinceLastUpdate, res, dir, topBar.getBottom()
		, leftBar.getRight(), bottomBar.getTop(), rightBar.getLeft() );
	terrain.update( timeSinceLastUpdate, res );
	hqBlue.update( timeSinceLastUpdate, res );
}

void Arena::draw( sf::RenderTarget &target, sf::RenderStates states ) const {
	terrain.draw( target, sf::RenderStates::Default );
	hqBlue.draw( target, sf::RenderStates::Default );
	topBar.draw( target, sf::RenderStates::Default );
	// leftBar.draw( target, sf::RenderStates::Default );
	bottomBar.draw( target, sf::RenderStates::Default );
	// rightBar.draw( target, sf::RenderStates::Default );
	gunIndicator.draw( target, sf::RenderStates::Default );
}

void Arena::newRound( sf::Vector2f res, int32 level ) {
	#if defined DBG
	std::cout << "[DEBUG] (" << m_myObjNameStr << ") " <<
	"newRound() has been triggered.\tLevel is: " << level << "\n";
	#endif
	// m_tmpRes = res;
	terrain.newRound( res );
	topBar.newRound( res );
	leftBar.newRound( res );
	bottomBar.newRound( res );
	rightBar.newRound( res );
	gunIndicator.newRound( res );
	hqBlue.newRound( res );
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

// ===================================80 chars=================================|
/* EOF */


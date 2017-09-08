/* main.cc */
// ===================================80 chars==================================

#include "main.h"

//
//
//
//
//
//
//
//
// ================== ECS TEST ==================
#include <iostream>

#include "ECS.h"

ECS_TYPE_IMPLEMENTATION;

using namespace ECS;

struct Position
{
	ECS_DECLARE_TYPE;

	Position( float x, float y )
		: x( x ), y( y ) {}

	Position() {}

	float x;
	float y;
};

ECS_DEFINE_TYPE( Position );

struct Rotation
{
	ECS_DECLARE_TYPE;

	Rotation( float angle )
		: angle( angle ) {}

	Rotation() {}

	float angle;
};

ECS_DEFINE_TYPE( Rotation );

struct SomeComponent
{
	ECS_DECLARE_TYPE;

	SomeComponent() {}
};

ECS_DEFINE_TYPE( SomeComponent );

struct SomeEvent
{
	ECS_DECLARE_TYPE;

	int num;
};

ECS_DEFINE_TYPE( SomeEvent );

class TestSystem : public EntitySystem
		 , public EventSubscriber <Events::OnEntityCreated>
		 , public EventSubscriber <Events::OnEntityDestroyed>
		 , public EventSubscriber <SomeEvent>
{
	public:
		virtual ~TestSystem() {}

		virtual void configure( class World* world ) override
		{
			world-> subscribe <Events::OnEntityCreated> (	this );
			world-> subscribe <Events::OnEntityDestroyed> ( this );
			world-> subscribe <SomeEvent> (			this );
		}

		virtual void unconfigure( class World* world ) override
		{
			world->unsubscribeAll( this );
		}

		virtual void tick( class World* world, float
			deltaTime ) override
		{
			world->each <Position, Rotation> ( [ & ] ( Entity* ent
								   ,
								   ComponentHandle
								   <Position>
								   pos
								   ,
								   ComponentHandle
								   <Rotation>
								   rot ) -> void
				{
					pos->x += deltaTime;
					pos->y += deltaTime;
					rot->angle += deltaTime * 2;
				} );
		}

		virtual void receive( class World* world, const
			Events::OnEntityCreated &event ) override
		{
			std::cout << "An entity was created!" << std::endl;
		}

		virtual void receive( class World* world, const
			Events::OnEntityDestroyed &event ) override
		{
			std::cout << "An entity was destroyed!" << std::endl;
		}

		virtual void receive( class World* world, const
			SomeEvent &event ) override
		{
			std::cout << "I received SomeEvent with value " <<
			event.num << "!" << std::endl;

			// Let's delete an entity while iterating because why
			// not?
			world->all( [ & ] ( Entity* ent ) {
					if ( ent->getEntityId() + 1 ==
					     event.num ) {
						world->destroy( world->getById(
								event.num ) );
					}

					if ( ent->getEntityId() == event.num ) {
						std::cout <<
						"Woah, we shouldn't get here!"
						<< std::endl;
					}
				} );
		}
};

// ================== ECS TEST ==================
//
//
//
//
//
//
//
//

int main()
{
	#if defined DBG
	std::cout << "****************************************\n" <<
	"*** BUILD TYPE IS: DEBUG\tAssert enabled.\n" <<
	"****************************************\n";
	#else
	std::cout << "****************************************\n" <<
	"*** BUILD TYPE IS: RELEASE\n" <<
	"****************************************\n";
	#endif

	#if defined __APPLE__
	// Fix for `cwd issue`: BEGIN
	// (temporary workaround until we get the bundle build system in CMake)
	char		link_path [ MAXPATHLEN ];
	// Current Directory Stuff
	char		buf [ MAXPATHLEN ];
	uint32_t	size = sizeof( buf );
	if ( _NSGetExecutablePath( buf, &size ) == 0 ) {
		realpath( buf, link_path );
	} else {
	}
	std::string	long_path( link_path );
	size_t		pos_ = long_path.find_last_of( "/\\" );
	std::string	relative_path = long_path.substr( 0, pos_ );
	chdir( relative_path.c_str() );
	// Fix for `cwd issue`: END
	#endif	// __APPLE__

	//
	//
	//
	//
	//
	//
	//
	//
	// ================== ECS TEST ==================
	std::cout << "EntityComponentSystem Test" << std::endl <<
	"==========================" << std::endl;

	World*	world = World::createWorld();

	world->registerSystem( new TestSystem() );

	Entity*	ent = world->create();
	auto	pos = ent->assign <Position> ( 0.f, 0.f );
	auto	rot = ent->assign <Rotation> ( 0.f );

	std::cout << "Initial values: position(" << pos->x << ", " << pos->y <<
	"), rotation(" << rot->angle << ")" << std::endl;

	world->tick( 10.f );

	std::cout << "After tick(10): position(" << pos->x << ", " << pos->y <<
	"), rotation(" << rot->angle << ")" << std::endl;

	std::cout << "Creating more entities..." << std::endl;

	for ( int i = 0; i < 10; ++i )
	{
		ent = world->create();
		ent->assign <SomeComponent> ();
	}

	int count = 0;
	std::cout << "Counting entities with SomeComponent..." << std::endl;
	// range based for loop
	for ( auto ent : world->each <SomeComponent> () )
	{
		++count;
		std::cout << "Found entity #" << ent->getEntityId() <<
		std::endl;
	}
	std::cout << count << " entities have SomeComponent!" << std::endl;

	// Emitting events
	world->emit <SomeEvent> ( { 4 } );

	std::cout << "We have " << world->getCount() <<
	" entities right now." << std::endl;
	world->cleanup();
	std::cout << "After a cleanup, we have " << world->getCount() <<
	" entities." << std::endl;

	std::cout << "Destroying the world..." << std::endl;

	world->destroyWorld();

	std::cout << "Press any key to exit..." << std::endl;
	std::getchar();
	// ================== ECS TEST ==================
	//
	//
	//
	//
	//
	//
	//
	//

	// create & run the application
	try
	{
		Application app;
		std::cout << "Welcome to " << CONST_GAME_NAME << "!\n";
		app.run();
	}
	catch ( std::runtime_error &e )
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;

		return 1;
	}

	return 0;
}

// ===================================80 chars==================================
/* EOF */


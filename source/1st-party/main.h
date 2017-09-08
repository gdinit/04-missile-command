/* main.h */
// ===================================80 chars==================================

#ifndef MAIN_H
#define MAIN_H

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

// ===================== CONFIGURE ME ======================
// ENABLE THE NEXT LINE *AFTER* MODIFYING IT TO SUIT YOUR GAME
#include "game/mc_game_defines.h"
// ===================== CONFIGURE ME ======================
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
/// ============== DO NOT TOUCH ==============
// Engine Defines
#include "en_defines.h"

#include "en_essentials.h"
#include "en_application.h"

// For exception handling in main
#include <stdexcept>
// For exception handling in main && for 'welcome to $gamename' text
#include <iostream>

#if defined __APPLE__
// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake:
// BEGIN
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <unistd.h>
#include <sys/param.h>
#include <mach-o/dyld.h>

char REAL_PATH [ MAXPATHLEN ];

const char * getExePath()
{
	char		exe_path [ MAXPATHLEN ];

	uint32_t	size = sizeof( exe_path );

	if ( _NSGetExecutablePath( exe_path, &size ) != 0 ) {
		std::cout << "Error Occured with _NSGetExecutablePath " <<
		std::endl;
	} else {
		// now attempt to get a real path (no symlinks)
		realpath( REAL_PATH, exe_path );

		return REAL_PATH;
	}

	return nullptr;
}

// Fix for `cwd issue`. Temporary, till we get the bundle build system in CMake:
// END

// __APPLE__
#endif

// MAIN_H
#endif

// ===================================80 chars==================================
/* EOF */


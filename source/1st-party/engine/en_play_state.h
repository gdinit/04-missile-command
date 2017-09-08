/* en_play_state.h */
// ===================================80 chars==================================

#ifndef EN_PLAY_STATE_H
#define EN_PLAY_STATE_H

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

// struct Position
// {
// 	ECS_DECLARE_TYPE;

// 	Position( float x, float y )
// 		: x( x ), y( y ) {}

// 	Position() {}

// 	float x;
// 	float y;
// };

// ECS_DEFINE_TYPE( Position );

// struct Rotation
// {
// 	ECS_DECLARE_TYPE;

// 	Rotation( float angle )
// 		: angle( angle ) {}

// 	Rotation() {}

// 	float angle;
// };

// ECS_DEFINE_TYPE( Rotation );

// struct SomeComponent
// {
// 	ECS_DECLARE_TYPE;

// 	SomeComponent() {}
// };

// ECS_DEFINE_TYPE( SomeComponent );

// struct SomeEvent2
// {
// 	ECS_DECLARE_TYPE;

// 	int num;
// };

ECS_DEFINE_TYPE( SomeComponent2 );

struct SomeEvent2
{
	ECS_DECLARE_TYPE;

	int num;
};

// ECS_DEFINE_TYPE( SomeEvent2 );

class TestSystem2 : public EntitySystem
		 , public EventSubscriber <Events::OnEntityCreated>
		 , public EventSubscriber <Events::OnEntityDestroyed>
		 , public EventSubscriber <SomeEvent2>
{
	public:
		virtual ~TestSystem2() {}

		virtual void configure( class World* world ) override
		{
			world-> subscribe <Events::OnEntityCreated> (	this );
			world-> subscribe <Events::OnEntityDestroyed> ( this );
			world-> subscribe <SomeEvent2> (			this );
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
			SomeEvent2 &event ) override
		{
			std::cout << "I received SomeEvent2 with value " <<
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

#include "en_essentials.h"
#include "en_state.h"
#include "en_state_machine.h"
#include "en_main_menu_state.h"
#include "en_pause_state.h"
// TODO remove this #include "mc_config.h"
// Required for centerOrigin
#include "en_util_utility.h"
#include "en_util_make_unique.h"
// TODO remove this
#include "mc_game_objects.h"
#include "en_arena.h"
// TODO remove this #include "mc_hud.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

// to in-line document
// Required for std::unique_ptr
#include <memory>
// Required for debugging -- TODO REMOVE THIS
#include <iostream>
// Required for capturing last windowResizeEvent
#include <chrono>
// Required for JSON
#include <fstream>

class StateMachine;

class PlayState : public State
{
	public:
		PlayState( StateMachine &machine
		, sf::RenderWindow &window
		, EngineSharedContext &context
		, bool replace = true );
		virtual ~PlayState();
		void	onResize();
		void	initializeState();
		void	processEvents();
		void	update();
		void	draw();
		void	pause();
		void	resume();
		// animation stuff
		void	restartPregameAnimationClock();
		void	drawPreGameAnimation();
		float	getPreGameAnimationAgeAsSeconds();

	private:
		const t_objectName	m_myObjNameStr;
		Arena			arena;
		// TODO remove this Hud			hud;
		sf::Vector2f		m_res;

		// window resize stuff
		// Added to store texture size
		sf::Vector2u		m_textureSize;
		// Added to store window size
		sf::Vector2u		m_windowSize;
		// TODO move this to app
		float			m_desiredAspectRatio;

		// animation stuff
		sf::Clock		m_animationClock;
		sf::Time		m_animationAge;
		sf::Text		m_preGameAnimationStep1Text;
		sf::Text		m_preGameAnimationStep2Text;
		sf::Text		m_preGameAnimationStep3Text;
		sf::Text		m_preGameAnimationStep4Text;
		sf::SoundBuffer		m_sbBlip2;
		sf::Sound		m_sBlip2;
		Direction		m_moveDirection;
		sf::SoundBuffer		m_sbClicked;
		sf::Sound		m_sClicked;
		int32			m_systemResizeHourglass;
		// imgui stuff
		sf::CircleShape		m_shape;
		sf::Clock		deltaClock;
		int32			m_clicked;
};

// EN_PLAY_STATE_H
#endif

// ===================================80 chars==================================
/* EOF */


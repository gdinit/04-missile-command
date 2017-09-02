/* application.h */
// ===================================80 chars==================================

#ifndef APPLICATION_H
#define APPLICATION_H

#include "essentials.h"
#include "shared_context.h"
#include "intro_state.h"
#include "globals.h"
#include "config.h"

#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
	public:
		Application();
		virtual ~Application();
		void	createWindow();
		void	loadSettings();
		void	loadGlobals();
		void	run();

	private:
		const t_objectName	m_myObjNameStr;
		StateMachine		m_machine;
		sf::RenderWindow	m_window;
		SharedContext		m_sCtxt;
};

#endif	// APPLICATION_H

// ===================================80 chars==================================
/* EOF */


/* en_application.h */
// ===================================80 chars==================================

#ifndef EN_APPLICATION_H
#define EN_APPLICATION_H

#include "en_essentials.h"
#include "shared_context.h"
#include "en_intro_state.h"
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
		void	run();

	private:
		const t_objectName	m_myObjNameStr;
		StateMachine		m_machine;
		sf::RenderWindow	m_window;
		SharedContext		m_sCtxt;
};

#endif	// EN_APPLICATION_H

// ===================================80 chars==================================
/* EOF */


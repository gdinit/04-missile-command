/* main.h */
// ===================================80 chars==================================

#ifndef MAIN_H
#define MAIN_H

/// ============== CONFIGURE ME ==============
// ENABLE THE NEXT LINE *AFTER* MODIFYING IT TO SUIT YOUR GAME
#include "ga_game_defines.h"
/// ============== CONFIGURE ME ==============

/// ============== DO NOT TOUCH ==============
// Engine Defines
#include "en_defines.h"

#include "en_essentials.h"
#include "en_application.h"

// TODO REMOVE THIS LINE #include "mc_game.h"

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
#endif	// __APPLE__

#endif	// MAIN_H

// ===================================80 chars==================================
/* EOF */


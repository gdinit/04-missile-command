/* main.cc */
// ===================================80 chars==================================

#include "main.h"

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
	size_t		pos = long_path.find_last_of( "/\\" );
	std::string	relative_path = long_path.substr( 0, pos );
	chdir( relative_path.c_str() );
	// Fix for `cwd issue`: END
	#endif	// __APPLE__

	// create & run the application
	try
	{
		Application app;
		std::cout << "Welcome to Breakout!\n";
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


/* en_assert.h */
// ===================================80 chars=================================|

// There are three types of ASSERTs
// 1 Production-and-Debug Asserts.
// 2 Production-Only Asserts.
// 3 Debug-Only Asserts.
//
// These can be used as shown below:
// POASSERT( age > 7, "age must be > 7!\n" );
// PDASSERT( age > 10, "age must be > 10!\n" );
// PASSERT( ( age > 0 ), "ERROR: age must be > 7!\tIt is: " << age << "\n" );
// DOASSERT( age > 15, "age must be > 15!\n" );

#ifndef EN_ASSERT_H
#define EN_ASSERT_H

#include <cassert>

#ifndef EMSCRIPTEN
#define BREAK_ACTION exit( 1 )
#else
#define BREAK_ACTION raise( SIGTRAP )
#endif
// ------------------------------- RELEASE BUILDS ------------------------------
#if defined NDEBUG

// BEGIN:	Type1@ReleaseBuilds	Production-and-Debug Asserts
#define PDASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
// END:		Type1@ReleaseBuilds	Production-and-Debug Asserts
// BEGIN:	Type2@ReleaseBuilds	Production-Only Asserts
#define POASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
// END:		Type2@ReleaseBuilds	Production-Only Asserts
// BEGIN:	Type3@ReleaseBuilds	Debug-Only Asserts
#define DOASSERT( condition, message ) do {} while ( false )
// END:		Type3@ReleaseBuilds	Debug-Only Asserts
// ------------------------------- RELEASE BUILDS ------------------------------
#else
#ifndef DBG
// ------------------------------- DEBUG BUILDS --------------------------------
#define DBG
// BEGIN:	Type1@DebugBuilds	Production-and-Debug Asserts
#define PDASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
// END:		Type1@DebugBuilds	Production-and-Debug Asserts
// BEGIN:	Type2@DebugBuilds	Production-Only Asserts
#   define POASSERT( condition, message ) do {} while ( false )
// END:		Type2@DebugBuilds	Production-Only Asserts
// BEGIN:	Type3@DebugBuilds	Debug-Only Asserts
#define DOASSERT( condition, message ) \
	do \
	{ \
		if ( !( condition ) ) { \
			std::cerr << "Assertion `"#condition "` failed in " << \
			__FILE__ << " function " << __func__ << " line " << \
			__LINE__ << ": " << message << std::endl; \
			BREAK_ACTION; \
		} \
	} while ( false )
// BEGIN:	Type3@DebugBuilds	Debug-Only Asserts
// ------------------------------- DEBUG BUILDS --------------------------------
// exit DBG
#endif
// exit NDEBUG
#endif
// exit EN_ASSERT_H
#endif

// ===================================80 chars=================================|
/* EOF */


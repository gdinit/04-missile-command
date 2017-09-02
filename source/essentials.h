/* essentials.h */
// ===================================80 chars==================================

#ifndef ESSENTIALS_H
#define ESSENTIALS_H

#include <cstdint>
#include <chrono>
// For object name
#include <string>

#if defined NDEBUG
#else
	#ifndef DBG
	#define DBG
	#endif
#endif

typedef unsigned char byte;
typedef std::int8_t int8;
typedef std::uint8_t uint8;

typedef std::int16_t int16;
typedef std::uint16_t uint16;

typedef unsigned int uint;
typedef std::int32_t int32;
typedef std::uint32_t uint32;

typedef std::int64_t int64;
typedef std::uint64_t uint64;

typedef wchar_t wchar;

typedef std::string t_objectName;

enum class Direction : std::int32_t {
	LEFT = -1
	, NONE = 0
	, RIGHT = 1
};

#endif	// ESSENTIALS_H

// ===================================80 chars==================================
/* EOF */


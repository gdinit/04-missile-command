/* en_enums.h */
// ===================================80 chars=================================|

#ifndef EN_ENUMS_H
#define EN_ENUMS_H

// Required for fixed width integer types
#include <cstdint>

// Required for Play State and must stay on engine side.
// enum class Direction : std::int32_t {
enum Direction : std::int32_t {
	NONE = 0
	, UP = 1
	, UPRIGHT = 2
	, RIGHT = 3
	, DOWNRIGHT = 4
	, DOWN = 5
	, DOWNLEFT = 6
	, LEFT = 7
	, UPLEFT = 8
};

// EN_ENUMS_H
#endif

// ===================================80 chars=================================|
/* EOF */


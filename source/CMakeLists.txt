set(CMAKE_LEGACY_CYGWIN_WIN32 0)
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 11)
#set (CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

project(04-missile-command)
SET(PROJECT_STATIC_RUNTIME FALSE CACHE BOOL "Use statically linked standard/runtime libraries?")
mark_as_advanced	(PROJECT_STATIC_RUNTIME)

list(APPEND CMAKE_MODULE_PATH	"${PROJECT_SOURCE_DIR}/cmake/modules")
FIND_PACKAGE(SFML 2.4 COMPONENTS graphics audio window system network)

file(GLOB SOURCES 
	"${PROJECT_SOURCE_DIR}/1st-party/*.cc"
	"${PROJECT_SOURCE_DIR}/1st-party/engine/*.cc"
	"${PROJECT_SOURCE_DIR}/1st-party/game/*.cc"
	#"${PROJECT_SOURCE_DIR}/3rd-party/bigint/v.2010.04.30/*.cc"
	"${PROJECT_SOURCE_DIR}/3rd-party/ecs/v.7a43faf/ecs.cc"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui/v.1.52_wip/imgui.cpp"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui/v.1.52_wip/imgui_draw.cpp"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui-sfml/v.141cd93/imgui-sfml.cpp"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui-sfml/v.141cd93/imgui-SFML.cpp"
	)

if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

################################################################################
# Compiler options
################################################################################
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	#set(warnings "-Wall -Wno-unknown-pragmas -Wextra -Werror")
	set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /WX /EHsc /Wno-unknown-pragmas")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
	if(PROJECT_STATIC_RUNTIME)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static -Wall -Wno-unknown-pragmas")
		#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static -Wall -Wno-unknown-pragmas")
	else()
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wno-unknown-pragmas")
		#shesSET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wno-unknown-pragmas")
	endif()
endif()
################################################################################


################################################################################
include_directories(
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${SFML_INCLUDE_DIR}"
	"${PROJECT_SOURCE_DIR}/1st-party"
	"${PROJECT_SOURCE_DIR}/1st-party/engine"
	"${PROJECT_SOURCE_DIR}/1st-party/game"
	#"${PROJECT_SOURCE_DIR}/3rd-party/bigint/v.2010.04.30"
	"${PROJECT_SOURCE_DIR}/3rd-party/ecs/v.7a43faf"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui/v.1.52_wip"
	"${PROJECT_SOURCE_DIR}/3rd-party/imgui-sfml/v.141cd93"
	)
################################################################################


################################################################################
include(cotire)
################################################################################

################################################################################
IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	INCLUDE_DIRECTORIES("/Library/Frameworks/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
################################################################################

################################################################################
# LIB SUFFIXES
#
#SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	SET(CMAKE_FIND_LIBRARY_PREFIXES "")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
endif()
mark_as_advanced	(CMAKE_FIND_LIBRARY_PREFIXES)
################################################################################


SET(BUILD_SHARED_LIBRARIES ON)

SET(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
add_executable(
	${PROJECT_NAME}
	${GUI_TYPE}
	${SOURCES}
	${IMGUI_SFML_SOURCES}
	${CMAKE_SOURCE_DIR}/extras/exe_icon_for_windows/resource.rc)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${IMGUI_SFML_DEPENDENCIES} ${LUA_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${IMGUI_SFML_DEPENDENCIES})
#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${IMGUI_SFML_DEPENDENCIES} ${LUA_LIBRARY})
#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${IMGUI_SFML_DEPENDENCIES} liblua53)
#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${IMGUI_SFML_DEPENDENCIES})
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES VS_STARTUP_PROJECT ${PROJECT_NAME})
################################################################################
cotire(${PROJECT_NAME})
################################################################################


################################################################################
# This didn't work. Reverting to "duplicate assets to debug dir" method for now.
# set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/release.win/Debug")
################################################################################
set(CMAKE_SUPPRESS_REGENERATION true)
################################################################################


################################################################################
# LINKER FLAGS
#
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Darwin")
        set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
        #set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
	if(CMAKE_COMPILER_IS_GNUCXX)
		set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
	endif()
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
        set	(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "")
endif()
mark_as_advanced	(CMAKE_EXE_LINKER_FLAGS)
################################################################################


################################################################################
# EXECUTABLE_OUTPUT_PATH
#
set(PROJECT_BINARY_DIR "${CMAKE_SOURCE_DIR}/build" CACHE PATH "Out of source, temporary build dir")
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Darwin")
        set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.mac CACHE PATH "Mac output directory")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.win CACHE PATH "Windows output directory")
elseif	(${CMAKE_SYSTEM_NAME}		MATCHES "Linux")
	set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.lin CACHE PATH "Linux output directory")
else()
        set	(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/release.unsupported_platform CACHE PATH "UnsupportedPlatforms output directory")
endif()
mark_as_advanced	(EXECUTABLE_OUTPUT_PATH)
################################################################################


################################################################################
# LIBRARIES
#
set	(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "NOT IN USE" )
mark_as_advanced	(LIBRARY_OUTPUT_PATH)
################################################################################


################################################################################
# PRE/POST BUILD SCRIPTS FOR ALL PLATFORMS
#
#--- PRE-BUILD STUFF -------------------
#add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#so far, nothing to do in pre-build stage...
#---------------------------------------
#
#
#--- POST-BUILD STUFF ------------------
# copy ASSETS
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)
# copy DATA
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)
# copy DOCUMENTATION
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/documentation $<TARGET_FILE_DIR:${PROJECT_NAME}>/documentation)
################################################################################


################################################################################
# CUSTOM COMMANDS FOR WINDOWS BUILDS ONLY
#
# Note that SFML is embedded into the .EXE file so we only need to copy OpenAL.
if	(${CMAKE_SYSTEM_NAME}		MATCHES "Win")
	# copy dependency binaries to build dir.
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/extras/dependencies $<TARGET_FILE_DIR:${PROJECT_NAME}>/)
	# copy ASSETS for Visual Studio so that debug run can find assets
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_SOURCE_DIR}/build/source/assets)
	# copy DATA for Visual Studio so that debug run can find assets
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_SOURCE_DIR}/build/source/data)
endif()
################################################################################


################################################################################
# NOTES - Microsoft Visual Studio compiler flags
#
# /W4 -> For a new project, it may be best to use /W4 in all compilations; this will ensure the fewest possible hard-to-find code defects.
# /WX -> Treats all compiler warnings as errors. For a new project, it may be best to use /WX in all compilations; resolving all warnings ensures the fewest possible hard-to-find code defects.
# /EHsc -> Exception handling model'optimization, space and time for x86 code, space for x64 code'	
################################################################################

#EOF

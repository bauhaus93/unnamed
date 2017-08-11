cmake_minimum_required(VERSION 3.4.3)
project(unnamed CXX)

macro(add_sources)
	file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

	foreach(_src ${ARGN})

		if(_relPath)
			set_property(TARGET unnamed APPEND PROPERTY SRC_LIST "${_relPath}/${_src}")
		else()
			set_property(TARGET unnamed APPEND PROPERTY SRC_LIST "${_src}")
		endif()

	endforeach()
endmacro()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(COMPILE_FLAGS "-std=c++14 -Wall -fmax-errors=1 -ggdb")
	set(LINK_FLAGS "-std=c++14 -Wall -fmax-errors=1 -ggdb")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(COMPILE_FLAGS "-std=c++14 -Wall -ferror-limit=1")
		set(LINK_FLAGS "--std=c++14 -Wall -ferror-limit=1")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(COMPILE_FLAGS "/W4 /std:c++latest /MP")
	set(LINK_FLAGS "/NODEFAULTLIB:msvcrtd.lib")
endif()



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

add_executable(unnamed "")

add_subdirectory(src)

get_property(SRCS TARGET unnamed PROPERTY SRC_LIST)
target_sources(unnamed PRIVATE ${SRCS})

include_directories(src)

if (WIN32)
	set(SDL_PATH "C:/SDL2" CACHE STRING "Path to SDL2 installation")
	include_directories("${SDL_PATH}/include")
	find_library(SDL_LIB NAMES SDL2 PATHS "${SDL_PATH}/lib")
	find_library(SDL_MAIN_LIB NAMES SDL2main PATHS "${SDL_PATH}/lib")
	find_library(SDL_GFX NAMES libSDL2_gfx PATHS "${SDL_PATH}/lib")
endif (WIN32)

if (UNIX)
    include_directories(/usr/include)

		find_library(SDL_LIB NAMES SDL2 PATHS /usr/lib/ /usr/local/lib)
		find_library(SDL_MAIN_LIB NAMES SDL2main PATHS /usr/lib/ /usr/local/lib)
		find_library(SDL_GFX NAMES libSDL2_gfx PATHS /usr/lib/ /usr/local/lib)
endif (UNIX)

target_link_libraries(unnamed "${SDL_LIB}")
target_link_libraries(unnamed "${SDL_MAIN_LIB}")
target_link_libraries(unnamed "${SDL_GFX}")

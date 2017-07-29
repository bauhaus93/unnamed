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
	set(COMPILE_FLAGS "/W4")
	#set(LINK_FLAGS "/NODEFAULTLIB:msvcrtd.lib")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

include_directories(/usr/include)
include_directories(src)

add_executable(unnamed "")

add_subdirectory(src)

get_property(SRCS TARGET unnamed PROPERTY SRC_LIST)
target_sources(unnamed PRIVATE ${SRCS})

find_library(SDL_LIB NAMES SDL2 PATHS /usr/lib/ /usr/local/lib C:/SDL2/lib)
find_library(SDL_MAIN_LIB NAMES SDL2main PATHS /usr/lib/ /usr/local/lib C:/SDL2/lib)

target_link_libraries(unnamed "${SDL_LIB}")
target_link_libraries(unnamed "${SDL_MAIN_LIB}")

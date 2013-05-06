cmake_minimum_required(VERSION 2.8)
#message("Hello CMake !")

# Name of the project, now accessible by ${PROJECT_NAME}
project(zCraft)

# C++2011 is required. It rocks, by the way.
add_definitions(-std=c++11)

# Note : some variables concerning libraries and compilation settings must be
# defined into CMakeCache.txt after first CMake execution (This is specific to
# your building environnment). I suggest you do do this in a separate build/
# directory.

include_directories(
	"src/"
	${sfml_include_dir}
	${glew_include_dir}
)

link_directories(
	${sfml_lib_dir}
	${glew_lib_dir}
)

# Recursively finds files.
# Note : if you add/remove files, you need to rerun CMake to regenerate the build system.
file(GLOB_RECURSE src_engine src/engine/*)
file(GLOB_RECURSE src_tests src/tests/*)
file(GLOB_RECURSE src_zcraft src/zcraft/*)

set(src_all
	${src_engine}
	${src_tests}
	${src_zcraft}
	src/main.cpp
	src/version.hpp
)

# The executable will have the same name as the project.
# This command requires a list of source files.
add_executable(${PROJECT_NAME} ${src_all})

# The executable will be placed in the bin folder (Debug or Release).
# Note : by default, CMAKE_BUILD_TYPE is empty,
# in this case a debug project will be generated.
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# Note : the order is important
target_link_libraries(
	${PROJECT_NAME}
	"opengl32"
	"glu32"
	${glew_lib_name}
	${sfml_graphics_lib_name}
	${sfml_audio_lib_name}
	${sfml_network_lib_name}
	${sfml_window_lib_name}
	${sfml_system_lib_name}
)





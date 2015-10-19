#******************************************************************************
# Copyright (C) 2014-2015 Oliveri Dario
# See copyright notice in LICENSE.md file.
#******************************************************************************


#==============================================================================
# Welcome to BadeEngine3D Build system.
#==============================================================================

cmake_minimum_required( VERSION 2.8)
project( BadeEngine3D)

# -DCMAKE_BUILD_TYPE:STRING=Release
# Debug, MinSizeRel, RelWithDebugInfo, Release, General

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR
  "Cannot write to badeSource folder, please run CMake from another dir")
  message(FATAL_ERROR
  "try console commands (separed by @): mkdir build @ cd build @ cmake-gui ..")
endif()


#==============================================================================
# Use the following options to customize the build
#==============================================================================

set( BADE_TARGET_NAME "target" CACHE STRING
    "Name for a build target, needed for different OSes or compilers")


set( BADE_OPENGL3_API true CACHE BOOL
    "Compile using OpenGL 3 API, only one API must be selected. ")


set( BADE_OPENGLES2_API false CACHE BOOL
    "Compile using OpenGL ES2 API, only one API must be selected. ")


set( BADE_SDL2_DEVICE false CACHE BOOL
    "Build and use SDL2 (used for some demos and tests). ")


set( BADE_SDL2_DIRECTORY "../SDLhg" CACHE PATH
    "Directory in wich SDL2's CMakeLists.txt file is found")
	
	
set( BADE_INFECTORPP2_GLUE true CACHE BOOL
    "Build and use infectorpp2 (used for some demos and tests). ")

	
set( BADE_INFECTORPP2_DIR "../Infectorpp" CACHE PATH
    "Directory in wich SDL2's CMakeLists.txt file is found")


set( BADE_UNITY_BUILD false CACHE BOOL
	"choose TRUE if you are compiling Bade just once, FALSE otherwise")

	
set( BADE_ENABLE_PROFILING false CACHE BOOL
	"choose TRUE if you want to compile using the native profiler")
	
	
set( BADE_ENABLE_TESTS true CACHE BOOL
	"TRUE to enable tests.")

#==============================================================================
# Enable C++11 support ( MIT LICENSE: Copyright (c) 2013 Nathan Osman)
#==============================================================================

# code has minor tweaks
if((MSVC AND (MSVC12 OR MSVC14)) OR
   (CMAKE_COMPILER_IS_GNUCXX
		AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.6) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"
		AND NOT ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.1))

	message(STATUS "Checking for C++11 compiler - available")
else()
	message(FATAL_ERROR "Checking for C++11 compiler - unavailable")
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	
	#Profile code with GCC
	if(CMAKE_COMPILER_IS_GNUCXX AND BADE_ENABLE_PROFILING)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
		SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
		SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
	endif()
	
endif()


#==============================================================================
# Extract public headers (prefixed with Bade) from source folder.
#==============================================================================

file( GLOB BADE_PUBLIC_HEADERS "badeSource/Bade*.hpp")
file( COPY ${BADE_PUBLIC_HEADERS} DESTINATION "../../bade")


#==============================================================================
# Add source files to static library
#==============================================================================
if(BADE_OPENGL3_API)
	set( BADE_TARGET_IMPLEMENTATION "gl3")
endif()


file( GLOB BADE_SOURCE_FILES
							"badeSource/*.cpp"
							"badeSource/${BADE_TARGET_IMPLEMENTATION}/*.cpp")

file( GLOB BADE_HEADER_FILES
							"badeSource/*.hpp"
							"badeSource/${BADE_TARGET_IMPLEMENTATION}/*.hpp")

set_source_files_properties( 	${BADE_HEADER_FILES}
									PROPERTIES HEADER_FILE_ONLY true)


# keep unity build file updated even when not using unity build.?
# It can be handy, but paths are machine specific so require cmake anyway.
file( WRITE badeSource/all.cxx "// Auto-generated build file\n")

foreach( source_file ${BADE_SOURCE_FILES} )

	file( APPEND badeSource/all.cxx "#include \"${source_file}\"\n")

endforeach(source_file)


if( BADE_UNITY_BUILD)

	# Do not build source files...
	set_source_files_properties( 	${BADE_SOURCE_FILES}
									PROPERTIES HEADER_FILE_ONLY true)

	add_library( libBadeEngine3D STATIC
										badeSource/all.cxx
										${BADE_SOURCE_FILES}
										${BADE_HEADER_FILES})

else()

	add_library( libBadeEngine3D STATIC
										${BADE_SOURCE_FILES}
										${BADE_HEADER_FILES})

endif()

# Build SDL2
if(BADE_SDL2_DEVICE)

	#SDL2 CMake scripts are really bad designed, they expose a 
	# embarassing amount of cache variables without any prefix.
	# later I'll add some code to hide them to final users.

    add_subdirectory( ${BADE_SDL2_DIRECTORY} ${CMAKE_BINARY_DIR}/SDL2)
	#target_link_libraries( libBadeEngine3D ${OPENGL_gl_LIBRARY})
endif()


# Build Infectorpp
if(BADE_INFECTORPP2_GLUE)

	set(	INFECTORPP2_ENABLE_PROFILING 
			${BADE_ENABLE_PROFILING}
										CACHE INTERNAL 
										"forward configuration" FORCE)
										
	set(	INFECTORPP2_UNITY_BUILD 
			${BADE_UNITY_BUILD} 
										CACHE INTERNAL 
										"forward configuration" FORCE)
										
	set(	INFECTORPP2_TARGET_NAME 
			"GlueLibrary" 
										CACHE INTERNAL 
										"forward configuration" FORCE)
										
	set( 	INFECTORPP2_ENABLE_EXCEPTIONS 
			TRUE
										CACHE INTERNAL 
										"forward configuration" FORCE)
	
	#enable tests only if user has exceptions
	set( 	INFECTORPP2_ENABLE_TESTS 
			FALSE
										CACHE INTERNAL 
										"forward configuration" FORCE)
										
	add_subdirectory( ${BADE_INFECTORPP2_DIR} ${CMAKE_BINARY_DIR}/Infectorpp2)
	
	include_directories( ${BADE_INFECTORPP2_DIR}/include/Infectorpp )
	
endif()


set_target_properties( libBadeEngine3D  PROPERTIES
										PREFIX "static_"   )

#==============================================================================
# Link with dependencies
#==============================================================================

if(BADE_OPENGL3_API) #this is the only real external dependency
    find_package (OpenGL)
    target_link_libraries( libBadeEngine3D ${OPENGL_gl_LIBRARY})
endif()


#==============================================================================
# Copy static library to "bin folder"
#==============================================================================

add_custom_command(TARGET libBadeEngine3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:libBadeEngine3D>
    "../../bin/${BADE_TARGET_NAME}/$<TARGET_FILE_NAME:libBadeEngine3D>"
)


#==============================================================================
# Preparation for Unit testing.
#==============================================================================

if( NOT ${BADE_ENABLE_TESTS})
	return()
endif()

enable_testing()
add_library( libCatch STATIC tests/catch.cxx)
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)

set_target_properties( libCatch	PROPERTIES
								PREFIX ""   )

function(create_test parm) #tests helper function

	get_filename_component( ExeName		${parm} NAME_WE)
	get_filename_component( SourceFile	${parm} ABSOLUTE)

	add_executable( ${ExeName} ${SourceFile})

	# ARGN is list of arguments past "parm". So all libraries that we link
	target_link_libraries( ${ExeName} ${ARGN})


	add_dependencies( build_and_test ${ExeName})

	include_directories(  "badeSource")

	add_test( ${ExeName} ${ExeName})

	add_custom_command(TARGET ${ExeName}
					   POST_BUILD
					   COMMAND ${ExeName}
					   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
					   COMMENT "Running ${ExeName}" VERBATIM)
endfunction(create_test)


#==============================================================================
# Unit testing and compile demos
#==============================================================================


#tests are grouped by "naming convention": the reason is that running tests
#is platform specific and require additional libraries for the demos
#so we may be able only to run a bunch of tests according to your build
#configuration. The biggest help you can give (apart contributing developing)
#is running tests and let me know wich tests fails.   THANKS :*
# (also writing tests is wellcome!!!! :D)


# "core" tests are runned against various utilities and don't require
# opengl or a graphics context.
file( GLOB BADE_COMMON_TEST_FILES	"tests/core*.cpp")
foreach( source_file ${BADE_COMMON_TEST_FILES} )
	create_test( ${source_file} libCatch libBadeEngine3D)
endforeach(source_file)


if(BADE_SDL2_DEVICE)
  if(BADE_OPENGL3_API)

	#gl3 tests require a graphics context (kindly provided by SDL2)
	#and also test gl3 stuff by mocking opengl functions
    file( GLOB BADE_GL3_TEST_FILES	"tests/gl3*.cpp")
	foreach( source_file ${BADE_GL3_TEST_FILES} )
		create_test( ${source_file} libCatch libBadeEngine3D)
	endforeach(source_file)


  endif()
endif()







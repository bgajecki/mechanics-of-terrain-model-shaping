# CMakeList.txt : CMake project for mechanics-of-terrain-model-shaping, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("mechanics-of-terrain-model-shaping")

add_executable (${PROJECT_NAME} WIN32 main.cpp)

set(INCLUDES PRIVATE
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/Engine
	${PROJECT_SOURCE_DIR}/Stages
	${PROJECT_SOURCE_DIR}/lib/freeglut/include
	${PROJECT_SOURCE_DIR}/lib/glew/include
)

target_include_directories (${PROJECT_NAME} PRIVATE ${INCLUDES})

# Initalization of freeglut and glew
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(FREEGLUT PRIVATE ${PROJECT_SOURCE_DIR}/lib/freeglut/x64/freeglut.lib)
    set(GLEW PRIVATE ${PROJECT_SOURCE_DIR}/lib/glew/x64/glew32.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(FREEGLUT PRIVATE ${PROJECT_SOURCE_DIR}/lib/freeglut/freeglut.lib)
    set(GLEW PRIVATE ${PROJECT_SOURCE_DIR}/lib/glew/Win32/glew32.lib)
endif()

add_subdirectory("Engine")
add_subdirectory("Stages")

target_link_libraries (${PROJECT_NAME}
	${FREEGLUT}
	${GLEW}
	Shaders
	Stages
	opengl32
	glu32
	gdi32
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

set (CMAKE_CXX_FLAGS
	${CMAKE_CXX_FLAGS}
	"-O2 -std=c++20 -fno-omit-frame-pointer -fno-common -fdata-sections"
)

set (CMAKE_EXE_LINKER_FLAGS
	${CMAKE_EXE_LINKER_FLAGS}
	"-Wall -static-libstdc++ -static-libgcc"
)

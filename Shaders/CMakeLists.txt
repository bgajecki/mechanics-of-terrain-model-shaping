cmake_minimum_required (VERSION 3.8)

project ("Shaders")

aux_source_directory(${PROJECT_SOURCE_DIR} SRCS)

add_library(${PROJECT_NAME} STATIC ${SRCS})

set(INCLUDES PRIVATE
	${PROJECT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/lib/freeglut/include
)

target_include_directories (${PROJECT_NAME} PRIVATE ${INCLUDES})

# Initalization of freeglut
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(FREEGLUT PRIVATE ${CMAKE_SOURCE_DIR}/lib/freeglut/x64/freeglut.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(FREEGLUT PRIVATE ${CMAKE_SOURCE_DIR}/lib/freeglut/freeglut.lib)
endif()

target_link_libraries (${PROJECT_NAME}
#	${FREEGLUT}
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

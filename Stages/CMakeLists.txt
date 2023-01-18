cmake_minimum_required (VERSION 3.8)

project ("stages")

aux_source_directory(${PROJECT_SOURCE_DIR} STAGES)
aux_source_directory(${PROJECT_SOURCE_DIR}/UserInterface/ USER_INTERFACE)
aux_source_directory(${PROJECT_SOURCE_DIR}/UserInterface/Element ELEMENT)
aux_source_directory(${PROJECT_SOURCE_DIR}/UserInterface/Button/ BUTTON)

set(SRCS
	${STAGES}
	${USER_INTERFACE}
	${ELEMENT}
	${BUTTON}
)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_include_directories (${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

set(INCLUDES PUBLIC
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/UserInterface
	${PROJECT_SOURCE_DIR}/UserInterface/Element
	${PROJECT_SOURCE_DIR}/UserInterface/Button
	${CMAKE_SOURCE_DIR}/engine
	${CMAKE_SOURCE_DIR}/lib/freeglut/include
	${CMAKE_SOURCE_DIR}/lib/glew/include
	#${CMAKE_SOURCE_DIR}/lib/stb
)

target_include_directories (${PROJECT_NAME} PRIVATE ${INCLUDES})


# Initalization of freeglut and glew
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(FREEGLUT PRIVATE ${CMAKE_SOURCE_DIR}/lib/freeglut/x64/freeglut.lib)
    set(GLEW PRIVATE ${CMAKE_SOURCE_DIR}/lib/glew/x64/glew32.lib)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(FREEGLUT PRIVATE ${CMAKE_SOURCE_DIR}/lib/freeglut/freeglut.lib)
    set(GLEW PRIVATE ${CMAKE_SOURCE_DIR}/lib/glew/Win32/glew32.lib)
endif()

target_link_libraries (${PROJECT_NAME}
	${FREEGLUT}
	${GLEW}
	engine
	opengl32
	glu32
	gdi32
	glm
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

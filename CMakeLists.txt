cmake_minimum_required(VERSION 3.11)
cmake_policy(SET CMP0072 NEW)

project(TD_GL_IMAC1)

# Set the folder where the executable will be created
set(OUTPUT_BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)

# Configure assets header file
# tips found here : https://shot511.github.io/2018-05-29-how-to-setup-opengl-project-with-cmake/
include_directories(${CMAKE_BINARY_DIR}/src)

# Librairies

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad third_party/glad/src/glad.c)
include_directories(third_party/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)


file(GLOB HEADER_FILES ./include/*.hpp)
file(GLOB EXT_SRC_FILES ./src/*.cpp)
file(GLOB EXE_SRC_FILES ./src/main.cpp)
#file(GLOB_RECURSE SHADER_FILES *.glsl)
list(REMOVE_ITEM EXT_SRC_FILES ${EXE_SRC_FILES})

foreach(EXE_SRC_FILE ${EXE_SRC_FILES})
	get_filename_component(FILE ${EXE_SRC_FILE} NAME_WE)
	get_filename_component(DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	set(OUTPUT ${DIR}_${FILE})
	#    add_executable(${OUTPUT} ${SRC_FILE} ${HEADER_FILES} ${SHADER_FILES})
	set(SRC_FILES ${EXT_SRC_FILES} ${EXE_SRC_FILE})
	add_executable(${OUTPUT} ${SRC_FILES} ${HEADER_FILES})
	target_link_libraries(${OUTPUT} ${ALL_LIBRARIES})
	set_target_properties(${OUTPUT} PROPERTIES
		CXX_STANDARD 11
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)
	set_target_properties(${OUTPUT} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
	if (MSVC)
		target_compile_options(${OUTPUT} PRIVATE /W3)
	else()
		target_compile_options(${OUTPUT} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
	endif()
endforeach()

#file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

cmake_minimum_required( VERSION 3.0 )
project(rubiks)

find_package( glfw3 REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

include_directories( /usr/bin/include )
link_directories( PUBLIC /usr/local/lib PUBLIC /usr/lib64 )

set( SRCS
	src/utils.cpp
	src/main.cpp
	src/Window.cpp
	src/ShaderProgram.cpp
	src/Quad.cpp
)
add_executable( rubiks ${SRCS} )

target_link_libraries( rubiks GLEW GLU OpenGL::GL glfw3 X11 pthread )
target_link_libraries( rubiks vector_math )
target_link_libraries( rubiks ${CMAKE_DL_LIBS} ) 

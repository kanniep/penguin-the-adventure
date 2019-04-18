cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_NAME
        "PenquinTheAdventure"
        )

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES
        main.cpp
        getBMP.cpp getBMP.h
        scene.cpp scene.h
        lighting.cpp lighting.h
        Penquin.cpp Penquin.h Obstracles.cpp Obstracles.h Food.cpp Food.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})
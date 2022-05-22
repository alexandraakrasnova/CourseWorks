CMAKE_MINIMUM_REQUIRED(VERSION 3.13.4)
PROJECT(coursework)

SET(CMAKE_CXX_STANDARD 14)
include_directories(include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


# INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(coursework
        src/main.cpp
        src/funcs.cpp
)

# target_link_libraries(server ${Boost_LIBRARIES})

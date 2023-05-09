cmake_minimum_required(VERSION 3.23)
project(Reactions CXX)

set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_library(Reactions::Reactions ALIAS Reactions)

if (${MAIN_PROJECT})
    add_subdirectory(tests)
    target_link_libraries(tests PRIVATE Reactions)
endif ()

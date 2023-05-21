cmake_minimum_required(VERSION 3.25)
project(Reactions CXX)

set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif ()

if (${MAIN_PROJECT})
    set(CMAKE_CXX_STANDARD 20)
endif ()

if (${CMAKE_CXX_STANDARD} LESS 20)
    message(SEND_ERROR "C++${CMAKE_CXX_STANDARD} less than REQUIRED C++20")
endif ()

if (${MAIN_PROJECT} AND (NOT DEFINED FAST OR NOT ${FAST}))
    find_program(CLANG_TIDY NAMES "clang-tidy" REQUIRED)
    set(CLANG_TIDY_COMMAND "${CLANG_TIDY};-fix-errors;-p;${CMAKE_CURRENT_BINARY_DIR}")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_COMMAND})
endif ()

add_subdirectory(src)
add_library(Reactions::Reactions ALIAS Reactions)

if (${MAIN_PROJECT})
    add_subdirectory(tests)
    target_link_libraries(tests PRIVATE Reactions)

    add_subdirectory(it)
    target_link_libraries(it PRIVATE Reactions)

    set_target_properties(
            tests it
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
    )

    add_subdirectory(examples)
    get_property(examples DIRECTORY "examples" PROPERTY BUILDSYSTEM_TARGETS)
    foreach (example ${examples})
        target_link_libraries(${example} PRIVATE Reactions)
    endforeach ()
endif ()

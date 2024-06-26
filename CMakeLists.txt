cmake_minimum_required(VERSION 3.10)

# Define the project name and supported languages
project(AStar VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Print the C++ and C standard versions
message(STATUS "Using C++ standard version ${CMAKE_CXX_STANDARD}")
message(STATUS "Using C standard version ${CMAKE_C_STANDARD}")

# Set the build type to Debug by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# List your source and header files using GLOB
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_LIST_DIR}/src/*.c" "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

# Create an executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/inc")

# Set compiler flags for Debug and Release
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:DEBUG>:
        -O0
        -g
        -Wall
        -Wextra
        -pedantic
        -Wshadow
        -Wconversion
        -Wsign-conversion
        -Wunreachable-code
    >
    $<$<CONFIG:RELEASE>:
        -O3
        -Wall
        -Wextra
        -pedantic
    >
)

# Write the project name to a configuration file
file(WRITE "${CMAKE_BINARY_DIR}/project_config.sh" "PROJECT_NAME=${PROJECT_NAME}\n")

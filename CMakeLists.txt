cmake_minimum_required(VERSION 3.15)

project(MyGame VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directory for all configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add Raylib (included in external/)
add_subdirectory(external/raylib)

# Gather your source files
file(GLOB GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create the game executable
add_executable(MyGame ${GAME_SOURCES})

# Copy assets folder to the runtime output directory after build
add_custom_command(TARGET MyGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:MyGame>/assets
)

# Include your project's headers
target_include_directories(MyGame PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link Raylib
target_link_libraries(MyGame PRIVATE raylib)

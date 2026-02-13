cmake_minimum_required(VERSION 3.15)

project(MyGame VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set output directory for all configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add Raylib (included in external/)
add_subdirectory(external/raylib)

# Gather your source files
file(GLOB GAME_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create the game executable
add_executable(MyGame ${GAME_SOURCES})

# Copy assets folder to the runtime output directory after build
add_custom_command(TARGET MyGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:MyGame>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:MyGame>/assets
)

# Include your project's headers
target_include_directories(MyGame PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link Raylib
target_link_libraries(MyGame PRIVATE raylib)

# Compiler flags (per configuration)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MyGame PRIVATE
        $<$<CONFIG:Debug>:-Wall -Wextra -O0>
        $<$<CONFIG:Release>:-Wall -Wextra -O2>
    )
elseif (MSVC)
    target_compile_options(MyGame PRIVATE
        $<$<CONFIG:Debug>:/W4 /Od>
        $<$<CONFIG:Release>:/W4 /O2>
    )
endif()

# Platform-specific system libraries
if (WIN32)
    target_link_libraries(MyGame PRIVATE winmm gdi32 opengl32)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(MyGame PRIVATE X11 pthread)
endif()

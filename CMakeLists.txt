cmake_minimum_required(VERSION 3.15)
project(SpriteEngine)

set(CMAKE_CXX_STANDARD 17)

# Add external dependencies
add_subdirectory(external/glad)

# GLFW - assumes it's added via FetchContent or ExternalProject and ends up in build/_deps/glfw-src
add_subdirectory(${CMAKE_BINARY_DIR}/_deps/glfw-src ${CMAKE_BINARY_DIR}/_deps/glfw-build)

# Source files
file(GLOB_RECURSE SRC_FILES
    src/*.cpp
)

add_executable(main ${SRC_FILES})

# Include directories
target_include_directories(main PRIVATE
    external/glad/include
    ${CMAKE_BINARY_DIR}/_deps/glfw-src/include
    src
)

include(FetchContent)

FetchContent_Declare(
  stb
  URL https://github.com/nothings/stb/archive/refs/heads/master.zip
)

FetchContent_MakeAvailable(stb)

target_include_directories(main PRIVATE ${stb_SOURCE_DIR})

# Link libraries
target_link_libraries(main PRIVATE
    glad
    glfw
)

# Optionally copy shaders next to binary
file(GLOB SHADERS src/shaders/*)
foreach(shader IN LISTS SHADERS)
    add_custom_command(TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${shader}
        $<TARGET_FILE_DIR:main>
    )
endforeach()

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:main>/assets)
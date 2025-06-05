cmake_minimum_required(VERSION 3.20)
project(Kallune)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
add_executable(${PROJECT_NAME} ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src/)

# Set the folder where the executable will be created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Librairies

# Ajout de GLM via FetchContent
include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8 # Tu peux mettre une version plus récente si tu veux
)

FetchContent_MakeAvailable(glm)

# ---Add glbasimac---
add_subdirectory(lib/glbasimac)
target_link_libraries(${PROJECT_NAME} PRIVATE glbasimac glm)

include(CmakeUtils/files_and_folders.cmake)
Cool__target_copy_folder(${PROJECT_NAME} "assets")

# Include stb_image.h
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
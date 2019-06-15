# -------------------------------------------------------------
# general setup
# -------------------------------------------------------------
cmake_minimum_required(VERSION 3.8...3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

# -------------------------------------------------------------
# find dependencies
# -------------------------------------------------------------
enable_language(CXX)
find_package(mpUtils REQUIRED)


# -------------------------------------------------------------
# set up project
# -------------------------------------------------------------

# Appends the cmake/ path to MAKE_MODULE_PATH variable.
set(CMAKE_MODULE_PATH ${mpUtils_CMAKE_SCRIPTS_PATH} ${CMAKE_MODULE_PATH})

# create project
include(GetVersionFromGit)
project(fireFightingGameThing VERSION "${VERSION_SHORT}" LANGUAGES CXX)

# default build configuration
include(setDefaultTypeRelease)


# -------------------------------------------------------------
# user settings and optional features
# -------------------------------------------------------------
option(USE_DEBUG_LOGGING "Use debug logging even in release builds." OFF)


# -------------------------------------------------------------
# create target
# -------------------------------------------------------------

# create target
add_executable(fireFightingGameThing)

# add general source files
target_sources(fireFightingGameThing PRIVATE
        "src/main.cpp"
        "src/engine/SpriteRenderer.cpp"
        "src/engine/Camera2D.cpp"
        "src/gameLogic/GameObject.cpp"
        )

# add definitions
set(FFGT_PROJECT_SHADER_PATH "${CMAKE_CURRENT_LIST_DIR}/shader")
set(FFGT_PROJECT_RESOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/resources")
target_compile_definitions(fireFightingGameThing PRIVATE PROJECT_SHADER_PATH="${FFGT_PROJECT_SHADER_PATH}/")
target_compile_definitions(fireFightingGameThing PRIVATE PROJECT_RESOURCE_PATH="${FFGT_PROJECT_RESOURCE_PATH}/")

if (USE_DEBUG_LOGGING)
    target_compile_definitions(fireFightingGameThing PRIVATE MPU_ENABLE_DEBUG_LOGGING)
endif()

# link libraries
target_link_libraries(fireFightingGameThing mpUtils::mpUtils)

# set cuda code generation flags
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} ${mpUtils_CUDA_ARCH_FLAGS}")


# -------------------------------------------------------------
# set includes
# -------------------------------------------------------------

target_include_directories(fireFightingGameThing
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )


# -------------------------------------------------------------
# set properties
# -------------------------------------------------------------

# set required language standard
set_target_properties(fireFightingGameThing PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        )

target_compile_definitions(fireFightingGameThing PRIVATE "FFGT_VERSION=\"${VERSION_SHORT}\"")
target_compile_definitions(fireFightingGameThing PRIVATE "FFGT_VERSION_SHA=\"${VERSION_SHA1}\"")

# set -Wa,-I for resources search path
target_compile_options(fireFightingGameThing PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wa,-I${CMAKE_SOURCE_DIR},-I${CMAKE_SOURCE_DIR}/resources,-I${CMAKE_SOURCE_DIR}/shader>)








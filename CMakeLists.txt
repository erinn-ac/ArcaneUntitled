cmake_minimum_required(VERSION 3.20)

# ---- Project ----
project(ArcaneUntitled
    VERSION 1.0
    DESCRIPTION "ArcaneUntitled C++ Project"
    LANGUAGES CXX
)

# ---- Options ----
option(ARCANE_ENABLE_WARNINGS "Enable compiler warnings" ON)
option(ARCANE_ENABLE_LTO "Enable link-time optimization" OFF)

# ---- Sources ----
if (MSVC)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # for msvc hashtag for gcc
endif()
set(SOURCES
    src/Main.cpp
    src/config.h
)


# ==== packages ====
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
# ---- Executable ----
add_executable(${PROJECT_NAME} ${SOURCES})

# ---- C++ Standard ----
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# ==== Include Directories ====
target_include_directories(${PROJECT_NAME} PRIVATE dependencies)

# ==== libraries ====
if (MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW3_LIBRARY} OpenGL::GL)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)
endif()

# ---- Warnings ----
if (ARCANE_ENABLE_WARNINGS)
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endif()

# ---- Link Time Optimization ----
if (ARCANE_ENABLE_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
    if (ipo_supported)
        set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(WARNING "IPO/LTO not supported: ${ipo_error}")
    endif()
endif()

# ---- Output Directory ----
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

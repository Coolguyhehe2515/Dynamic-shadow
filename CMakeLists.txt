cmake_minimum_required(VERSION 3.22)

project(DynamicShadows LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED MOD_ID)
    set(MOD_ID dynamic_shadows)
endif()

if(NOT DEFINED MOD_NAME)
    set(MOD_NAME "Dynamic Shadows")
endif()

if(NOT DEFINED MOD_AUTHOR)
    set(MOD_AUTHOR "KrispyBRN")
endif()

if(NOT DEFINED MOD_VERSION)
    set(MOD_VERSION 0.1.0)
endif()

if(NOT DEFINED MOD_LIBRARY_NAME)
    set(MOD_LIBRARY_NAME dynamic_shadows)
endif()

include(FetchContent)

FetchContent_Declare(
    preloader
    GIT_REPOSITORY https://github.com/LiteLDev/preloader-android.git
    GIT_TAG v0.2.2
)

FetchContent_MakeAvailable(preloader)

add_library(${MOD_LIBRARY_NAME} SHARED
    src/main.cpp
    src/render/RenderHooks.cpp
)

target_include_directories(${MOD_LIBRARY_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${MOD_LIBRARY_NAME}
    PRIVATE
        preloader
        log
        android
)

target_compile_options(${MOD_LIBRARY_NAME}
    PRIVATE
        -fPIC
        -fvisibility=hidden
        -ffunction-sections
        -fdata-sections
)

target_link_options(${MOD_LIBRARY_NAME}
    PRIVATE
        -Wl,--gc-sections
)

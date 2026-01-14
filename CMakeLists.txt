#
# Copyright (c) 2025-present Henri Michelon
#
# This software is released under the MIT License.
# https://opensource.org/licenses/MIT
#
cmake_minimum_required(VERSION 3.29)

#######################################################
project(lysa_ui)
if (NOT DEFINED LYSA_ENGINE_PROJECT_DIR)
    if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.env.cmake")
        message(FATAL_ERROR "Please create a .env.cmake file with the LYSA_ENGINE_PROJECT_DIR & VIREO_RHI_PROJECT_DIR variables")
    else()
        include(.env.cmake)
    endif ()
endif ()
if (NOT DEFINED LYSA_ENGINE_PROJECT_DIR)
    message(FATAL_ERROR "Please set LYSA_ENGINE_PROJECT_DIR in the .env.cmake file")
endif()
if (NOT DEFINED VIREO_RHI_PROJECT_DIR)
    message(FATAL_ERROR "Please set VIREO_RHI_PROJECT_DIR in the .env.cmake file")
endif()

#######################################################
if(NOT DEFINED LYSA_ENGINE_AS_DEPENDENCY)
    set(LYSA_ENGINE_AS_DEPENDENCY ON)
    set(LUA_BINDING OFF)
    set(DIRECTX_BACKEND ON)
    set(PHYSIC_ENGINE_JOLT ON)
    set(PHYSIC_ENGINE_PHYSX OFF)
    set(FORWARD_RENDERER ON)
    set(DEFERRED_RENDERER ON)
endif ()

#######################################################
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(MSVC)
    set(USE_STATIC_MSVC_RUNTIME_LIBRARY OFF)
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
if(WIN32)
    add_compile_definitions(UNICODE _UNICODE)
endif ()

#######################################################
set(LYSA_ENGINE_TARGET "lysa_engine")
add_subdirectory(${LYSA_ENGINE_PROJECT_DIR} external_lib_build/${LYSA_ENGINE_TARGET})
set(LYSA_ENGINE_SRC_DIR ${LYSA_ENGINE_PROJECT_DIR}/src)

#######################################################
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#######################################################
function(build_target TARGET_NAME SRCS MODULES)
    message("Building target ${TARGET_NAME}")
    add_library(${TARGET_NAME} ${SRCS})
    target_sources(${TARGET_NAME}
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
            ${COMMON_MODULES}
            ${MODULES}
    )
    lysa_compile_options(${TARGET_NAME})
    add_dependencies(${TARGET_NAME} ${LYSA_ENGINE_TARGET})
    target_link_libraries(${TARGET_NAME} ${LYSA_ENGINE_TARGET} std-cxx-modules)
    if(WIN32)
        target_compile_definitions(${TARGET_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
        if(MINGW)
            target_link_options(${TARGET_NAME} PRIVATE "-mwindows")
        endif()
    endif()
endfunction()

#######################################################
if(LUA_BINDING)

endif ()

#######################################################
set(LYSA_UI_SRC
        ${SRC_DIR}/Button.cpp
        ${SRC_DIR}/CheckWidget.cpp
        ${SRC_DIR}/Frame.cpp
        ${SRC_DIR}/Image.cpp
        ${SRC_DIR}/Line.cpp
        ${SRC_DIR}/ScrollBar.cpp
        ${SRC_DIR}/Style.cpp
        ${SRC_DIR}/StyleClassic.cpp
        ${SRC_DIR}/StyleClassicResource.cpp
        ${SRC_DIR}/Text.cpp
        ${SRC_DIR}/TextEdit.cpp
        ${SRC_DIR}/ToggleButton.cpp
        ${SRC_DIR}/TreeView.cpp
        ${SRC_DIR}/ValueSelect.cpp
        ${SRC_DIR}/Widget.cpp
        ${SRC_DIR}/Window.cpp
        ${SRC_DIR}/WindowManager.cpp

)
set(LYSA_UI_MODULES
        ${SRC_DIR}/UI.ixx
        ${SRC_DIR}/Alignment.ixx
        ${SRC_DIR}/Box.ixx
        ${SRC_DIR}/Button.ixx
        ${SRC_DIR}/CheckWidget.ixx
        ${SRC_DIR}/Event.ixx
        ${SRC_DIR}/Frame.ixx
        ${SRC_DIR}/Image.ixx
        ${SRC_DIR}/Line.ixx
        ${SRC_DIR}/Panel.ixx
        ${SRC_DIR}/Resource.ixx
        ${SRC_DIR}/ScrollBar.ixx
        ${SRC_DIR}/Style.ixx
        ${SRC_DIR}/StyleClassic.ixx
        ${SRC_DIR}/StyleClassicResource.ixx
        ${SRC_DIR}/Text.ixx
        ${SRC_DIR}/TextEdit.ixx
        ${SRC_DIR}/ToggleButton.ixx
        ${SRC_DIR}/TreeView.ixx
        ${SRC_DIR}/ValueSelect.ixx
        ${SRC_DIR}/Widget.ixx
        ${SRC_DIR}/Window.ixx
        ${SRC_DIR}/WindowManager.ixx
       )
build_target(${PROJECT_NAME} "${LYSA_UI_SRC}" "${LYSA_UI_MODULES}")

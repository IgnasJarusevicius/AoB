cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE TYPE INTERNAL FORCE)
project("game")

list(FIND CMAKE_CONFIGURATION_TYPES "${CMAKE_BUILD_TYPE}" index)
if (${index} EQUAL -1)
   set(CMAKE_BUILD_TYPE "Release")
endif()

########################################################################
## compiler flags
########################################################################

#C++11 is a required language feature for this project
set(CMAKE_CXX_STANDARD 14)

if(CMAKE_COMPILER_IS_GNUCXX)

    #enable warnings in Debug configurations
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Release")
    	add_compile_options(-Wall -Wpedantic)
    endif()
endif()

if (UNIX)
add_custom_target(link_img ALL COMMAND ${CMAKE_COMMAND} -E create_symlink  ${CMAKE_CURRENT_SOURCE_DIR}/img ${CMAKE_BINARY_DIR}/img)
add_custom_target(link_snd ALL COMMAND ${CMAKE_COMMAND} -E create_symlink  ${CMAKE_CURRENT_SOURCE_DIR}/sounds ${CMAKE_BINARY_DIR}/sounds)
endif(UNIX)

if (MSVC)
    include_directories(${PROJECT_SOURCE_DIR}/external/msvc)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set( MSVC_MULTITHREAD_COMPILE_FLAGS "/MP")
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MSVC_MULTITHREAD_COMPILE_FLAGS}" )
endif(MSVC)


set(GAME_SOURCES
    glad/glad.cpp
    audio.cpp
    object/GameObject.cpp
    main.cpp
    graphic/texture.cpp
    graphic/GraphicObject.cpp
    object/stats.cpp
    graphic/TextObj.cpp
    graphic/Picture.cpp
    graphic/Rectangle.cpp
    object/menu.cpp
    object/bobject.cpp
    object/character.cpp
    object/damage.cpp
    object/object.cpp
    object/ranged.cpp
    object/BattleGrid.cpp
    object/grid.cpp
    object/ProgressBar.cpp
    object/AttackType.cpp
    graphic/gres.cpp
    graphic/sprite.cpp
)


find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
add_executable(game ${GAME_SOURCES})

set(GAME_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/graphic
    ${CMAKE_CURRENT_SOURCE_DIR}/object
    ${OPENAL_INCLUDE_DIR}DE_DIR}
)

target_include_directories(game PUBLIC ${GAME_INCLUDES})
target_link_libraries(game
                     ${GLUT_LIBRARY}
                     ${OPENGL_LIBRARIES}
                     openal
                     glfw
                     dl
                     pthread)

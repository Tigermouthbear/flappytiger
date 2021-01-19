cmake_minimum_required(VERSION 3.1)
project(flappytiger)

set(GLFW_SOURCE_DIR "external/glfw")
set(GLM_SOURCE_DIR "external/glm")
set(GLEW_SOURCE_DIR "external/glew")
set(FT_SOURCE_DIR "external/freetype2")
set (CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS}
        ${GLM_SOURCE_DIR}
        ${FT_SOURCE_DIR}/include
        ${GLEW_SOURCE_DIR}/include)

add_library(glew STATIC
        ${GLEW_SOURCE_DIR}/src/glew.c
        ${GLEW_SOURCE_DIR}/include)

target_link_libraries(glew ${GLFW_LIBRARIES})

add_definitions(-DGLEW_STATIC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(MSVC)
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable(flappytiger
        src/main.cpp
        src/FlappyTiger.h src/FlappyTiger.cpp
        src/render/buffer/Point.h
        src/render/stb_image.h
        src/render/buffer/Buffer.h
        src/render/buffer/StaticMesh.h src/render/buffer/StaticMesh.cpp
        src/render/buffer/Texture.h src/render/buffer/Texture.cpp
        src/render/FontRenderer.h src/render/FontRenderer.cpp
        src/render/shader/Shader.h src/render/shader/Shader.cpp
        src/render/shader/Uniform.h
        src/render/window/Window.h src/render/window/Window.cpp
        src/render/window/InputsCallback.h
        src/render/window/Screen.h
        src/game/StartScreen.cpp src/game/StartScreen.h
        src/game/IngameScreen.cpp src/game/IngameScreen.h
        src/render/buffer/DynamicMesh.cpp src/render/buffer/DynamicMesh.h)

option(INSTALL_APP "Sets resource paths for installation" OFF)
if(UNIX AND INSTALL_APP)
    target_compile_definitions(flappytiger PRIVATE INSTALL_PREFIX="/usr/share/flappytiger")
    install(TARGETS flappytiger DESTINATION /usr/bin)
    install(FILES resources/flappytiger.desktop DESTINATION /usr/share/applications)
    install(FILES resources/icons/48x48/flappytiger.png DESTINATION /usr/share/icons/hicolor/48x48/apps)
    install(FILES resources/icons/128x128/flappytiger.png DESTINATION /usr/share/icons/hicolor/128x128/apps)
    install(FILES resources/icons/256x256/flappytiger.png DESTINATION /usr/share/icons/hicolor/256x256/apps)
    install(FILES resources/icons/scaleable/flappytiger.svg DESTINATION /usr/share/icons/hicolor/scaleable/apps)
    install(FILES resources/font.ttf resources/pipe.png resources/sky.jpg resources/tigerbird.png DESTINATION /usr/share/flappytiger/resources)
    install(FILES resources/shaders/2d.vert resources/shaders/2d_colored.frag resources/shaders/2d_textured.frag resources/shaders/text.vert resources/shaders/text.frag DESTINATION /usr/share/flappytiger/resources/shaders)
else()
    target_compile_definitions(flappytiger PRIVATE INSTALL_PREFIX="${CMAKE_CURRENT_BINARY_DIR}")
    configure_file(${CMAKE_SOURCE_DIR}/resources/font.ttf ${CMAKE_CURRENT_BINARY_DIR}/resources/font.ttf COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/pipe.png ${CMAKE_CURRENT_BINARY_DIR}/resources/pipe.png COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/sky.jpg ${CMAKE_CURRENT_BINARY_DIR}/resources/sky.jpg COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/tigerbird.png ${CMAKE_CURRENT_BINARY_DIR}/resources/tigerbird.png COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/2d.vert ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/2d.vert COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/2d_colored.frag ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/2d_colored.frag COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/2d_textured.frag ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/2d_textured.frag COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/text.vert ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/text.vert COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/text.frag ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/text.frag COPYONLY)
endif(UNIX AND INSTALL_APP)
unset(INSTALL_APP CACHE)

target_link_libraries(flappytiger ${OPENGL_LIBRARIES} glfw glew freetype)
if(MSVC)
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'flappytiger' as StartUp Project in Visual Studio.\n" )
    else()
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT flappytiger )
    endif()
endif()

cmake_minimum_required(VERSION 3.15)
project(game)

set(CMAKE_CXX_STANDARD 20)
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

add_subdirectory(libraries/fmt-6.1.2)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

message("cmake path: ${PROJECT_SOURCE_DIR}/cmake")
message("OPENGL_gl_LIBRARY library: ${OPENGL_gl_LIBRARY}")
message("SDL2 include dir: ${SDL2_INCLUDE_DIR}")
message("SDL2_image include dir: ${SDL2_IMAGE_INCLUDE_DIRS}")
message("SDL2 library: ${SDL2_LIBRARY}")
message("SDL2_image library: ${SDL2_IMAGE_LIBRARIES}")

add_library(engine
        libraries/gl3w/GL/gl3w.c
        libraries/imgui/imgui.cpp
        libraries/imgui/imgui_demo.cpp
        libraries/imgui/imgui_draw.cpp
        libraries/imgui/examples/imgui_impl_opengl3.cpp
        libraries/imgui/examples/imgui_impl_sdl.cpp
        libraries/imgui/imgui_widgets.cpp
        src/Game.cpp
        src/Game.h
        src/Renderer.cpp
        src/Renderer.h
        src/Config.h
        src/Player.cpp
        src/Player.h
        src/Spritesheet.cpp
        src/Spritesheet.h
        src/Sprite.cpp
        src/Sprite.h
        src/Events.cpp
        src/Events.h
        src/Lifecycle.cpp
        src/Lifecycle.h
        src/m.cpp
        src/m.h
        src/Rect.cpp
        src/Rect.h
        src/Map.cpp
        src/Map.h
        src/Tilemap.cpp
        src/Tilemap.h
        src/Tile.cpp
        src/Tile.h
        src/Resources.cpp
        src/Resources.h
        src/Spritesheet.cpp
        src/Spritesheet.h
        src/debug.h
        src/Stacktrace.hpp
        src/Shader.cpp
        src/Shader.h
        src/SpriteRenderer.cpp
        src/SpriteRenderer.h
        src/SpriteBatch.cpp
        src/SpriteBatch.h
        src/Mesh.cpp
        src/Mesh.h
        src/QuadMeshBuilder.cpp
        src/QuadMeshBuilder.h
        src/Texture.cpp
        src/Texture.h
        src/CubeMeshBuilder.cpp
        src/CubeMeshBuilder.h
        src/Camera.cpp
        src/Camera.h
        src/Sprite.cpp
        src/Sprite.h
        src/DevUi.cpp
        src/DevUi.h)

# Engine needs its header files, and users of the library must also see these (PUBLIC).
target_include_directories(engine
        PUBLIC
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        "./libraries/glm-0.9.9.7"
        "./libraries/json-3.7.3"
        "./libraries/fmt-6.1.2/include"
        "./libraries/gl3w"
        "libraries/imgui"
        "libraries/imgui/examples"
        "./libraries/stb")

# Link the libraries to the engine.
target_link_libraries(engine PUBLIC ${OPENGL_gl_LIBRARY} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} fmt::fmt)

# Add an executable for the file main.cpp.
add_executable(game src/main.cpp)
# Link the executable to `engine`
target_link_libraries(game PRIVATE engine)

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(tests)
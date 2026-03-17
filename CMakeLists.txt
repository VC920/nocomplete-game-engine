cmake_minimum_required(VERSION 3.10)

project(mini-engine)

# 源文件
set(PROJECT_SOURCE_FILES
    thirdparty/glad/glad.c

    game/Game.cpp
    game/main.cpp

    engine/Application.cpp
    engine/Engine.cpp
    input/InputManager.cpp
    render/ShaderProgram.cpp
    render/Renderer.cpp
    render/Material.cpp
    render/Mesh.cpp
    scene/GameObject.cpp
    scene/Scene.cpp
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# 头文件
target_include_directories(${PROJECT_NAME} PRIVATE
    thirdparty/glad/include
    thirdparty/glfw/include
    engine
    game
    graphics
    input
    render
    scene
)

# 库文件
target_link_directories(${PROJECT_NAME} PRIVATE
    thirdparty/glfw/lib
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw3
)
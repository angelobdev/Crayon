# ----- Workspace Settings -----
cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- Crayon Project -----
project(Crayon VERSION 1.0.0)

add_library(Crayon STATIC
        src/Crayon.h # File to be included inside projects

        src/Crayon/Core/Application.cpp
        src/Crayon/Core/Application.h
        src/Crayon/Core/Base.h
        src/Crayon/Core/EntryPoint.h
        src/Crayon/Core/Input.h
        src/Crayon/Core/Logger.cpp
        src/Crayon/Core/Logger.h
        src/Crayon/Core/Window.cpp
        src/Crayon/Core/Window.h

        src/Crayon/Events/Event.h
        src/Crayon/Events/Event.cpp
        src/Crayon/Events/KeyEvent.h
        src/Crayon/Events/MouseEvent.h
        src/Crayon/Events/WindowEvent.h

        src/Crayon/Graphics/Core/OpenGL.h
        src/Crayon/Graphics/Core/VertexArray.h
        src/Crayon/Graphics/Core/VertexBuffer.h        
        src/Crayon/Graphics/Core/IndexBuffer.h
        src/Crayon/Graphics/Core/Shader.h
        src/Crayon/Graphics/Core/Texture.h

        src/Crayon/Graphics/Camera.h
        src/Crayon/Graphics/Directions.h
        src/Crayon/Graphics/Material.h
        src/Crayon/Graphics/Mesh.h

        src/Crayon/Graphics/GUI/imgui_impl_glfw.cpp
        src/Crayon/Graphics/GUI/imgui_impl_glfw.h
        src/Crayon/Graphics/GUI/imgui_impl_opengl3.cpp
        src/Crayon/Graphics/GUI/imgui_impl_opengl3.h
        src/Crayon/Graphics/GUI/ImGuiController.h
        src/Crayon/Graphics/GUI/ImGuiController.cpp

        src/Crayon/Utils/ResourceLoader.cpp
        src/Crayon/Utils/ResourceLoader.h
)

target_include_directories(Crayon PUBLIC "src")
target_precompile_headers(Crayon PUBLIC "src/crypch.h")

# ----- Dependencies -----
set(CRAYON_VENDOR_DIR "vendor")

# spdlog
set(SPDLOG_DIR "${CRAYON_VENDOR_DIR}/spdlog")
add_subdirectory("${SPDLOG_DIR}")
target_include_directories(Crayon PUBLIC "${SPDLOG_DIR}/include")
target_link_libraries(Crayon PRIVATE "spdlog")

# glfw
set(GLFW_DIR "${CRAYON_VENDOR_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_include_directories(Crayon PUBLIC "${GLFW_DIR}/include")
target_link_libraries(Crayon PRIVATE "glfw")

# glad
set(GLAD_DIR "${CRAYON_VENDOR_DIR}/glad")
add_subdirectory("${GLAD_DIR}")
target_include_directories(Crayon PUBLIC "${GLAD_DIR}/include")
target_link_libraries(Crayon PRIVATE "glad")

# imgui
set(IMGUI_DIR "${CRAYON_VENDOR_DIR}/imgui")
add_subdirectory("${IMGUI_DIR}")
target_include_directories(Crayon PUBLIC "${IMGUI_DIR}")
target_link_libraries(Crayon PRIVATE "imgui")

# debugbreak
set(DBGBRK_DIR "${CRAYON_VENDOR_DIR}/debugbreak")
target_include_directories(Crayon PUBLIC "${DBGBRK_DIR}/include")

# glm
set(GLM_DIR "${CRAYON_VENDOR_DIR}/glm")
target_include_directories(Crayon PUBLIC "${GLM_DIR}")

# stb_image
set(STB_IMAGE_DIR "${CRAYON_VENDOR_DIR}/stb_image")
target_include_directories(Crayon PUBLIC "${STB_IMAGE_DIR}/include")

# ----- Examples -----
option(CRAYON_BUILD_EXAMPLES "Crayon Build Examples" ON) # TODO test
if (CRAYON_BUILD_EXAMPLES)
    add_subdirectory("examples/Sandbox")
endif ()

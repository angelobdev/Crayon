# ----- Workspace Settings -----
cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----- Crayon Project -----
project(Crayon VERSION 1.0.0)

add_library(Crayon STATIC
        src/Crayon.h # File to be included inside projects

        src/Crayon/Core/Base.h

        src/Crayon/Core/Application.h
        src/Crayon/Core/Application.cpp

        src/Crayon/Core/EntryPoint.h

        src/Crayon/Core/Logger.h
        src/Crayon/Core/Logger.cpp

        src/Crayon/Events/Event.h
        src/Crayon/Events/Event.cpp
        src/Crayon/Events/KeyEvent.h
        src/Crayon/Events/MouseEvent.h
        src/Crayon/Events/WindowEvent.h
        src/Crayon/Core/Events.h

        src/Crayon/Core/Window.h
        src/Crayon/Core/Window.cpp

        src/Crayon/Core/Input.h
        src/Crayon/Core/Input.cpp

        src/Crayon/Graphics/ImGui/imgui_impl_glfw.cpp
        src/Crayon/Graphics/ImGui/imgui_impl_glfw.h
        src/Crayon/Graphics/ImGui/imgui_impl_opengl3.cpp
        src/Crayon/Graphics/ImGui/imgui_impl_opengl3.h

        src/Crayon/Graphics/ImGui/ImGuiController.h
        src/Crayon/Graphics/ImGui/ImGuiController.cpp
        src/Crayon/Graphics/Shader.h
        src/Crayon/Graphics/Common.h
        src/Crayon/Utilities/ResourceLoader.cpp
        src/Crayon/Utilities/ResourceLoader.h
        src/Crayon/Graphics/VertexArray.cpp src/Crayon/Graphics/VertexArray.h src/Crayon/Graphics/VertexBuffer.cpp src/Crayon/Graphics/VertexBuffer.h src/Crayon/Utilities/GLUtils.cpp src/Crayon/Utilities/GLUtils.h src/Crayon/Graphics/IndexBuffer.cpp src/Crayon/Graphics/IndexBuffer.h src/Crayon/Graphics/Shader.cpp)

target_include_directories(Crayon PUBLIC "src")
target_precompile_headers(Crayon PUBLIC "src/crypch.h")

# ----- Dependencies -----
set(CRAYON_VENDOR_DIR "vendor")

# spdlog
set(SPDLOG_DIR "${CRAYON_VENDOR_DIR}/spdlog")
target_include_directories(Crayon PUBLIC "${SPDLOG_DIR}/include")

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

# ----- Examples -----
option(CRAYON_BUILD_EXAMPLES "Crayon Build Examples" ON) # TODO test
if (CRAYON_BUILD_EXAMPLES)
    add_subdirectory("examples/Sandbox")
endif ()

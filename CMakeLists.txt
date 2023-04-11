# ----- Workspace Settings -----
cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

# ----- Crayon Project -----
project(Crayon VERSION 1.0.0)

add_library(Crayon STATIC
        "src/Crayon.h" # File to be included inside projects

        "src/Crayon/Core/Base.h"

        "src/Crayon/Core/Application.h"
        "src/Crayon/Core/Application.cpp"

        "src/Crayon/Core/EntryPoint.h"

        "src/Crayon/Core/Logger.h"
        "src/Crayon/Core/Logger.cpp"

        "src/Crayon/Core/Events.h"

        "src/Crayon/Events/Event.h"
        "src/Crayon/Events/Event.cpp"
        "src/Crayon/Events/KeyEvent.h"
        "src/Crayon/Events/MouseEvent.h"
        "src/Crayon/Events/WindowEvent.h"

        "src/Crayon/Core/Window.h"
        "src/Crayon/Core/Window.cpp"

        "src/Crayon/Core/ImGui/imgui_impl_glfw.cpp"
        "src/Crayon/Core/ImGui/imgui_impl_glfw.h"
        "src/Crayon/Core/ImGui/imgui_impl_opengl3.cpp"
        "src/Crayon/Core/ImGui/imgui_impl_opengl3.h"

        src/Crayon/Core/ImGui/ImGuiController.h src/Crayon/Core/Input.h src/Crayon/Core/Input.cpp src/Crayon/Core/ImGui/ImGuiController.cpp)

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

# ----- Examples -----
option(CRAYON_BUILD_EXAMPLES "Crayon Build Examples" ON) # TODO test
if (CRAYON_BUILD_EXAMPLES)
    add_subdirectory("examples/Sandbox")
endif ()
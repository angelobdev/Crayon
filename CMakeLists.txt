# ----- Workspace Settings -----
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# ----- Crayon Project -----
project (Crayon VERSION 1.0.0)

add_library(Crayon STATIC 	
	"src/Crayon.h" # File to be included inside projects
	
	"src/Crayon/Application.h"
	"src/Crayon/Application.cpp"
	
	"src/Crayon/EntryPoint.h"
	
	"src/Crayon/Core.h"

	"src/Crayon/Logger.h" 
	"src/Crayon/Logger.cpp"

	 "src/Crayon/Events/Event.h"
)
target_include_directories(Crayon PUBLIC "src")
target_precompile_headers(Crayon PUBLIC  "src/crypch.h")

# ----- Dependencies -----
set(CRAYON_VENDOR_DIR "vendor")

# spdlog
set(SPDLOG_DIR "${CRAYON_VENDOR_DIR}/spdlog")
target_include_directories(Crayon PUBLIC "${SPDLOG_DIR}/include")

# ----- Examples -----
option(CRAYON_BUILD_EXAMPLES "Crayon Build Examples" ON) # TODO test
if(CRAYON_BUILD_EXAMPLES)
	add_subdirectory("examples/Sandbox")
endif()
add_executable(Sandbox "src/Sandbox.cpp")
target_link_libraries(Sandbox PRIVATE "Crayon")

add_custom_command(
        TARGET Sandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${PROJECT_SOURCE_DIR}/examples/Sandbox/assets
        $<TARGET_FILE_DIR:Sandbox>/assets
        COMMENT "Creating symlink of assets folder")
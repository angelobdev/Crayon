add_executable(Sandbox "src/Sandbox.cpp")
target_link_libraries(Sandbox PRIVATE "Crayon")

set(ASSETS_SRC_DIR "${PROJECT_SOURCE_DIR}/examples/Sandbox/assets")
set(ASSETS_DST_DIR "$<TARGET_FILE_DIR:Sandbox>/assets")

if(UNIX)

    add_custom_command(
        TARGET Sandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${ASSETS_SRC_DIR}
        ${ASSETS_DST_DIR}
        COMMENT "Creating symlink of assets folder")

else()

    add_custom_command(
        TARGET Sandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        ${ASSETS_SRC_DIR}
        ${ASSETS_DST_DIR}
        COMMENT "Copying assets folder to binary dir")

endif()
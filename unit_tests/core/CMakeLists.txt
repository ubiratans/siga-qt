set(project_name "core_unit_test")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_subdirectory( core_element )

add_executable( ${project_name} ${SOURCES} ${HEADERS} )

target_link_libraries( ${project_name} gmock_main )

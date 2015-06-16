set(project_name "unit_test_core")
set(lib_project_name "lib_${project_name}")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_subdirectory(core_element)

list(APPEND project_dependencies "lib_unit_test_core_element")

add_executable( ${project_name} ${SOURCES} ${HEADERS} )
add_library( ${lib_project_name} ${SOURCES} ${HEADERS} )

target_link_libraries( ${project_name} ${project_dependencies} )
target_link_libraries( ${lib_project_name} ${project_dependencies} )

add_test( ${project_name} ${project_name} )

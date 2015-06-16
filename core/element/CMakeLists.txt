set( project_name "core_element")

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

add_library( ${project_name} ${HEADERS} ${SOURCES} )

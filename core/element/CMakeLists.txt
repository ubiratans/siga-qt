set( project_name "core_element")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_library( ${project_name} ${HEADERS} ${SOURCES} )

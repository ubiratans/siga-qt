set( project_name "view_cli")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_executable( ${project_name} ${HEADERS} ${SOURCES} )

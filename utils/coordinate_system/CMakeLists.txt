set( project_name "utils_coordinate_system" )

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_library(${project_name} ${HEADERS} ${SOURCES})
target_link_libraries(${project_name} core_coordinate_system)

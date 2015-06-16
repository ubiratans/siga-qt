set(project_name "utils_command")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_library(${project_name} ${SOURCES} ${HEADERS})

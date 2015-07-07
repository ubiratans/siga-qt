set(project_name "view_gui_graphic_element_command")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_library(${project_name} ${SOURCES} ${HEADERS})

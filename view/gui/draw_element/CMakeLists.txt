set(project_name "view_draw_element")

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_library(${project_name} ${SOURCES} ${HEADERS})

target_link_libraries(${project_name} view_canvas core)

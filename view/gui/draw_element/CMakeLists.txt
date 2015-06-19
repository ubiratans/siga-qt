set(project_name "view_gui_draw_element")

file(GLOB_RECURSE HEADERS *.h)
file(GLOB_RECURSE SOURCES *.cpp)

#add_subdirectory( draw_primitive )

add_library(${project_name} ${SOURCES} ${HEADERS})

target_link_libraries(${project_name} Qt5::Core Qt5::OpenGL core_element)

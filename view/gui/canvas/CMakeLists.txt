set(project_name "view_canvas")

file(GLOB_RECURSE HEADERS *.h)
file(GLOB SOURCES *.cpp)
file(GLOB FORMS "forms/*.ui")

wrap_qt_ui_files(FORM_HEADERS ${project_name} ${FORMS})

add_library(${project_name} ${SOURCES} ${HEADERS} ${FORM_HEADERS})

target_link_libraries( ${project_name} Qt5::Core Qt5::Widgets Qt5::OpenGL core_coordinate_system view_gui_graphic_element )

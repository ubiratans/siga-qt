set(project_name "view_gui")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")
file(GLOB FORMS "forms/*.ui")
file(GLOB RESOURCES "resources/*.qrc")

#qt5_wrap_ui(FORM_HEADERS ${FORMS} )
wrap_qt_ui_files(FORM_HEADERS ${project_name} ${FORMS})

# Subdirectories
add_subdirectory(canvas)
add_subdirectory(graphic_element)

add_executable(${project_name} ${SOURCES} ${HEADERS} ${FORM_HEADERS} ${RESOURCES})

target_link_libraries(${project_name} Qt5::Core Qt5::Widgets core view_canvas utils_coordinate_system)

# generate ts files
GenerateTranslations()

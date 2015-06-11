set(project_name "view_gui")

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

# Subdirectories
add_subdirectory(canvas)
add_subdirectory(draw_element)

add_executable(${project_name} ${SOURCES} ${HEADERS})

target_link_libraries(${project_name} Qt5::Core Qt5::Widgets core)

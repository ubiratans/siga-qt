set( project_name "core_coordinate_system")

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

add_library( ${project_name} ${SOURCES} ${HEADERS})

target_link_libraries(${project_name} Qt5::Core)

# generate ts files
GenerateTranslations()

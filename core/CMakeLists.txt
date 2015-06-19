set( project_name "core" )

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cpp)

# subdirectories
add_subdirectory(coordinate_system)
add_subdirectory(element)

add_library(${project_name} ${SOURCES} ${HEADERS})

# Linking qt core to the current project
target_link_libraries(${project_name} Qt5::Core core_element)

# Generating translations
GenerateTranslations()

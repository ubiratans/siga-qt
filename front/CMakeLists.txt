set(project_name "front")

file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

add_library( ${project_name} ${HEADERS} ${SOURCES} )

target_link_libraries( ${project_name} Qt5::Core core )


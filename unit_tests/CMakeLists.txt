set( project_name "unit_tests")

file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SOURCES "*.cpp")

set( EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/${project_name} )
set( LIBRARY_OUTPUT_PATH ${LIBRARY_OUTPUT_PATH}/${project_name}/lib )

# subdirectories
add_subdirectory(core)

#add_executable( ${project_name} ${SOURCES} ${HEADERS} )
#target_link_libraries( ${project_name} gmock_main )

#add_test( ${project_name} ${project_name} )

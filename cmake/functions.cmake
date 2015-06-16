function(GenerateTranslations)
    set(current_path ${CMAKE_CURRENT_SOURCE_DIR})
    set(translation_dir ${current_path}/resources/translations/)
    #set(output_dir )
    set(ts_files)

    # Creates TS dir
    # The ts files are the translations files that will be edited to receive the translations and will be 'compiled' resulting in .qm files
    if (NOT EXISTS ${translation_dir})
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E make_directory ${translation_dir}
        )
    endif(NOT EXISTS ${translation_dir})


    # Generating ts files via QT lupdate
    foreach (language ${translation_languages})
        LIST(APPEND ts_files ${translation_dir}translation_${language}.ts)
    endforeach(language ${translation_languages})

    execute_process(
        COMMAND ${QtLupdateLocation} ${current_path} -ts ${ts_files}
    )

    ## Installation
    # INSTALL(FILES ${qm_files} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

endfunction()

function (add_gmock_test target)
    add_executable( ${target} ${ARGN} )
    target_link_libraries( ${target} gmock_main )

    add_test( ${target} ${target} )
endfunction()

function(wrap_qt_ui_files out_files name)
    set(ui_files ${out_files})
    set(ui_options ${_WRAP_UI_OPTIONS})

    cmake_parse_arguments(_WRAP_UI "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(ui_files ${_WRAP_UI_UNPARSED_ARGUMENTS})
    set(ui_options ${_WRAP_UI_OPTIONS})

    foreach(it ${ui_files})
        get_filename_component(output ${it} NAME_WE)
        get_filename_component(input ${it} ABSOLUTE)

        set(output_file "${CMAKE_CURRENT_SOURCE_DIR}/${output}_ui.h")


        #message(STATUS "OUTPUT FILE: ${output_file}")
        #message(STATUS "INPUT: ${input}")
        #message(STATUS "UIC LOCATION: ${QtUIC_Location}")

        add_custom_command(OUTPUT ${output_file}
          COMMAND ${QtUIC_Location}
          ARGS ${ui_options} -o ${output_file} ${input}
          MAIN_DEPENDENCY ${input} VERBATIM)

        list(APPEND ${out_files} ${output_file})
    endforeach()

    set(${out_files} ${${out_files}} PARENT_SCOPE)
    add_custom_target("${name}_ui_headers_generation" ALL DEPENDS ${${out_files}})
endfunction()

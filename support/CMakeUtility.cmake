function(IDE projName projFiles projFolder)
    add_custom_target(${projName} SOURCES ${projFiles})
    set_target_properties(${projName} PROPERTIES FOLDER ${projFolder})
endfunction()

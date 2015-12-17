macro(copySample fileString)
  file(GLOB filesList "${fileString}")
  foreach(file ${filesList})
    get_filename_component(fileDir ${file} DIRECTORY)
    get_filename_component(fileName ${file} NAME)
    configure_file( ${fileDir}/${fileName} ${CMAKE_CURRENT_BINARY_DIR}/${fileName} COPYONLY )
    message("Copy ${fileName} to ${CMAKE_CURRENT_BINARY_DIR}/${fileName}")
  endforeach(file)
endmacro(copySample)

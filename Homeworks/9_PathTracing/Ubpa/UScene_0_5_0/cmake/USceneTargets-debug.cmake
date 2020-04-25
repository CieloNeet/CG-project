#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ubpa::UScene_core" for configuration "Debug"
set_property(TARGET Ubpa::UScene_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UScene_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UScene_0_5_0/lib/UScene_cored.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UScene_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UScene_core "${_IMPORT_PREFIX}/UScene_0_5_0/lib/UScene_cored.lib" )

# Import target "Ubpa::UScene_parser" for configuration "Debug"
set_property(TARGET Ubpa::UScene_parser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UScene_parser PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/UScene_parserd.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UScene_parser )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UScene_parser "${_IMPORT_PREFIX}/bin/UScene_parserd.exe" )

# Import target "Ubpa::UScene_tool" for configuration "Debug"
set_property(TARGET Ubpa::UScene_tool APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UScene_tool PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UScene_0_5_0/lib/UScene_toold.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UScene_tool )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UScene_tool "${_IMPORT_PREFIX}/UScene_0_5_0/lib/UScene_toold.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ubpa::UBL_core" for configuration "Debug"
set_property(TARGET Ubpa::UBL_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UBL_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UBL_0_1_0/lib/UBL_cored.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UBL_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UBL_core "${_IMPORT_PREFIX}/UBL_0_1_0/lib/UBL_cored.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

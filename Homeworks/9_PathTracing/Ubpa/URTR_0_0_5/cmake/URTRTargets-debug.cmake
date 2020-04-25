#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ubpa::URTR_core" for configuration "Debug"
set_property(TARGET Ubpa::URTR_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::URTR_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/URTR_0_0_5/lib/URTR_cored.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::URTR_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::URTR_core "${_IMPORT_PREFIX}/URTR_0_0_5/lib/URTR_cored.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

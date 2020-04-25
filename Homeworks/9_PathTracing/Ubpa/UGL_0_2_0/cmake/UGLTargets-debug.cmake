#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ubpa::UGL__deps_glad" for configuration "Debug"
set_property(TARGET Ubpa::UGL__deps_glad APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UGL__deps_glad PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UGL_0_2_0/lib/UGL__deps_gladd.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UGL__deps_glad )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UGL__deps_glad "${_IMPORT_PREFIX}/UGL_0_2_0/lib/UGL__deps_gladd.lib" )

# Import target "Ubpa::UGL_core" for configuration "Debug"
set_property(TARGET Ubpa::UGL_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UGL_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UGL_0_2_0/lib/UGL_cored.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UGL_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UGL_core "${_IMPORT_PREFIX}/UGL_0_2_0/lib/UGL_cored.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

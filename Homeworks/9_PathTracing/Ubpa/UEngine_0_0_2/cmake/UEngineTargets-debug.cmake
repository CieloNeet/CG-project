#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ubpa::UEngine__deps_imgui" for configuration "Debug"
set_property(TARGET Ubpa::UEngine__deps_imgui APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UEngine__deps_imgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine__deps_imguid.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UEngine__deps_imgui )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UEngine__deps_imgui "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine__deps_imguid.lib" )

# Import target "Ubpa::UEngine__deps_imgui_impl" for configuration "Debug"
set_property(TARGET Ubpa::UEngine__deps_imgui_impl APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UEngine__deps_imgui_impl PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine__deps_imgui_impld.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UEngine__deps_imgui_impl )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UEngine__deps_imgui_impl "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine__deps_imgui_impld.lib" )

# Import target "Ubpa::UEngine_core" for configuration "Debug"
set_property(TARGET Ubpa::UEngine_core APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Ubpa::UEngine_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine_cored.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Ubpa::UEngine_core )
list(APPEND _IMPORT_CHECK_FILES_FOR_Ubpa::UEngine_core "${_IMPORT_PREFIX}/UEngine_0_0_2/lib/UEngine_cored.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

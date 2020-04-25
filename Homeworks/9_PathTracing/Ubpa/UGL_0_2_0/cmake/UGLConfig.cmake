message(STATUS "config UGL v0.2.0...")


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was Config.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

####################################################################################


if(NOT ${FetchContent_FOUND})
	include(FetchContent)
endif()
if(NOT ${UCMake_FOUND})
	message(STATUS "find package: UCMake v")
	find_package(UCMake  QUIET)
	if(${UCMake_FOUND})
		message(STATUS "UCMake v${UCMake_VERSION} found")
	else()
		set(_Ubpa_UGL_address "https://github.com/Ubpa/UCMake")
		message(STATUS "UCMake v not found")
		message(STATUS "fetch: ${_Ubpa_UGL_address} with tag v")
		FetchContent_Declare(
		  UCMake
		  GIT_REPOSITORY ${_Ubpa_UGL_address}
		  GIT_TAG "v"
		)
		message(STATUS "UCMake v fetch done, building ...")
		FetchContent_MakeAvailable(UCMake)
		message(STATUS "UCMake v build done")
	endif()
endif()
Ubpa_AddDepPro(UGL UGM 0.5.1)
Ubpa_AddDepPro(UGL UDP 0.3.1)



include ( "${CMAKE_CURRENT_LIST_DIR}/UGLTargets.cmake" )

message(STATUS "config UGL v0.2.0 done")

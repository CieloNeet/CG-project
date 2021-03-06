message(STATUS "config UScene v0.5.0...")


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
		set(_Ubpa_UScene_address "https://github.com/Ubpa/UCMake")
		message(STATUS "UCMake v not found")
		message(STATUS "fetch: ${_Ubpa_UScene_address} with tag v")
		FetchContent_Declare(
		  UCMake
		  GIT_REPOSITORY ${_Ubpa_UScene_address}
		  GIT_TAG "v"
		)
		message(STATUS "UCMake v fetch done, building ...")
		FetchContent_MakeAvailable(UCMake)
		message(STATUS "UCMake v build done")
	endif()
endif()
Ubpa_AddDepPro(UScene UECS 0.5.5)



include ( "${CMAKE_CURRENT_LIST_DIR}/USceneTargets.cmake" )

message(STATUS "config UScene v0.5.0 done")

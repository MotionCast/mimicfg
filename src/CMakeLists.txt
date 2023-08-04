### LIST FILES
set(
	MIMICFG_HEADERS
	${PROJECT_SOURCE_DIR}/include/mimicfg/FileConfig.h
	${PROJECT_SOURCE_DIR}/include/mimicfg/BaseConfig.h
	${PROJECT_SOURCE_DIR}/include/mimicfg/ICEConfig.h
	${PROJECT_SOURCE_DIR}/include/mimicfg/KalmanConfig.h
	${PROJECT_SOURCE_DIR}/include/mimicfg/SignalerConfig.h
	${PROJECT_SOURCE_DIR}/include/mimicfg/NodesConfig.h
)

### TARGET
# Provide STATIC and SHARED targets
add_library(mimicfg-static INTERFACE)
add_library(mimicfg-shared INTERFACE)

set_target_properties(mimicfg-static PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(mimicfg-shared PROPERTIES LINKER_LANGUAGE CXX)

### HEADERS

## STATIC
# Including headers in other projects (PUBLIC) require `mimicfg` prefix
target_include_directories(
	mimicfg-static
	INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(mimicfg-static INTERFACE cxx_std_17)

## SHARED
# Including headers in other projects (PUBLIC) require `mimicfg` prefix
target_include_directories(
	mimicfg-shared
	INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(mimicfg-shared INTERFACE cxx_std_17)

### DEPENDENCIES
if(USE_TOML11)
	message("-- Fetching toml11 from repository")

	# toml11
	FetchContent_Declare(
		toml11
		GIT_REPOSITORY https://github.com/ToruNiina/toml11
		GIT_TAG        v3.7.1
	)

	FetchContent_MakeAvailable(toml11)

	# Save time by not compiling tests and examples
	target_link_libraries(mimicfg-static INTERFACE toml11)
	target_link_libraries(mimicfg-shared INTERFACE toml11)
endif()

### INSTALL
install(
	TARGETS mimicfg-shared toml11
	EXPORT MimicConfigTargets
	DESTINATION lib
)

install(
	FILES ${MIMICFG_HEADERS}
	DESTINATION include/mimicfg
)

install(
	EXPORT MimicConfigTargets
	FILE MimicConfigTargets.cmake
	DESTINATION lib/cmake/mimicfg
)

include(CMakePackageConfigHelpers)

configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/MimiCfgConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/mimicfg"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/MimiCfgConfigVersion.cmake"
	VERSION "${mimicfg_VERSION_MAJOR}.${mimicfg_VERSION_MINOR}"
	COMPATIBILITY AnyNewerVersion
)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/MimiCfgConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/MimiCfgConfigVersion.cmake
	DESTINATION lib/cmake/mimicfg
)

export(EXPORT MimicConfigTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/MimicConfigTargets.cmake"
)

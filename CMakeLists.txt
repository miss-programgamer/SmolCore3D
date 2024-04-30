# Project settings
cmake_minimum_required(VERSION 3.29.0)
project(SmolCore3D VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Cache variables
set(SMOL_CORE3D_BUILD_TESTS FALSE CACHE BOOL "Whether unit tests should be built")

# Main headers
set(PROJECT_HEADERS
	"source/smol/core3d/vec3.hpp"
	"source/smol/core3d/vec4.hpp"
	"source/smol/core3d/mat4x4.hpp"
	"source/smol/core3d.hpp"
)

# Main target
add_library(SmolCore3D INTERFACE)
target_sources(SmolCore3D INTERFACE FILE_SET HEADERS BASE_DIRS "source" FILES ${PROJECT_HEADERS})
target_include_directories(SmolCore3D INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>")
target_include_directories(SmolCore3D INTERFACE "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

# Test target
if (SMOL_CORE3D_BUILD_TESTS)
	# Find Catch2
	find_package(Catch2 3 REQUIRED)
	include(Catch)
	
	# Add test target
	add_executable(SmolCore3DTests "tests/main.cpp")
	target_link_libraries(SmolCore3DTests PRIVATE Catch2::Catch2WithMain SmolCore3D)
	catch_discover_tests(SmolCore3DTests)
	
	# Enable testing
	include(CTest)
	enable_testing()
endif()

# Packaging settings
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Generate CMake integration scripts
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

configure_package_config_file("cmake/Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/SmolCore3DConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/SmolCore3D"
)

write_basic_package_version_file(SmolCore3DConfigVersion.cmake
	VERSION ${CMAKE_PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

# Install targets & scripts
install(TARGETS SmolCore3D EXPORT SmolCore3DTargets LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR} FILE_SET HEADERS)
install(EXPORT SmolCore3DTargets FILE SmolCore3DTargets.cmake NAMESPACE Smol:: DESTINATION "lib/cmake/SmolCore3D")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/SmolCore3DConfigVersion.cmake" DESTINATION "lib/cmake/SmolCore3D")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/SmolCore3DConfig.cmake" DESTINATION "lib/cmake/SmolCore3D")
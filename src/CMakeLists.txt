set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

add_library(rulesLib SHARED rules.c rules.h rules.inc)
add_library(rulesLibStatic STATIC rules.c rules.h rules.inc)

set_target_properties (rulesLibStatic
	PROPERTIES
		OUTPUT_NAME rulesLib
)

add_executable(rules app.c)
add_dependencies(rules rulesLib)
target_link_libraries(rules rulesLib rulesLibStatic)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/rules.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/rules.pc
	@ONLY
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/rules.pc
	DESTINATION share/pkgconfig
	COMPONENT "PkgConfig"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/RulesConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/RulesConfig.cmake
	INSTALL_DESTINATION cmake
)
install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/RulesConfig.cmake
	DESTINATION cmake
)

install(
	TARGETS rules rulesLib rules
	LIBRARY DESTINATION lib COMPONENT "Library"
	ARCHIVE DESTINATION lib COMPONENT "Library"
	RUNTIME DESTINATION bin COMPONENT "Runtime"
)

install(
	FILES rules.h
	DESTINATION include
	COMPONENT "Header"
)

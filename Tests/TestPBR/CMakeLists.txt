file(GLOB_RECURSE TESTPBR_HEADER_FILES
		"*.h"
		"*.hpp"
		)
file(GLOB_RECURSE TESTPBR_SOURCE_FILES
		"*.c"
		"*.cpp"
		"*.rc"
		)
set(TESTPBR_SOURCES
		${TESTPBR_HEADER_FILES}
		${TESTPBR_SOURCE_FILES}
		)
set(TESTPBR_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Tests/TestPBR/")

add_executable(TestPBR ${TESTPBR_SOURCES})
add_dependencies(TestPBR Acid)

target_compile_features(TestPBR PUBLIC cxx_std_17)
set_target_properties(TestPBR PROPERTIES
		POSITION_INDEPENDENT_CODE ON
		FOLDER "Acid"
		)

target_include_directories(TestPBR PRIVATE ${ACID_INCLUDE_DIR} ${TESTPBR_INCLUDE_DIR})
target_link_libraries(TestPBR PRIVATE Acid)

if(MSVC AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set_target_properties(TestPBR PROPERTIES LINK_FLAGS "/subsystem:windows /ENTRY:mainCRTStartup")
elseif(UNIX AND APPLE)
	set_target_properties(TestPBR PROPERTIES
			MACOSX_BUNDLE_BUNDLE_NAME "Test PBR"
			MACOSX_BUNDLE_SHORT_VERSION_STRING ${ACID_VERSION}
			MACOSX_BUNDLE_LONG_VERSION_STRING ${ACID_VERSION}
			MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/Scripts/MacOSXBundleInfo.plist.in"
			)
endif()

add_test(NAME "PBR" COMMAND "TestPBR")

if(ACID_INSTALL_EXAMPLES)
	install(TARGETS TestPBR
			RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
			ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
			)
endif()

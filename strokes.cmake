set(SOURCE_BASE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE CSources "src/**.cpp")
file(GLOB_RECURSE HSources "src/**.h")
file(GLOB_RECURSE ObjSources "src/**.mm")

add_executable(${PROJECT_NAME}
        ${CSources}
        ${HSources}
		${ObjSources}
)

# INCLUDES
target_include_directories(${PROJECT_NAME} PRIVATE
        "src"
		"vendor"
)

# LIBS
target_link_libraries(${PROJECT_NAME}
	"-framework Cocoa"
	"-framework ApplicationServices"  # AXIsProcessTrusted*
	"-framework IOKit"                # IOHIDCheckAccess/RequestAccess
)

# PROPERTIES
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_NAME ${PROJECT_NAME}
        ARCHIVE_OUTPUT_DIRECTORY "bin-int/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        LIBRARY_OUTPUT_DIRECTORY "bin-int/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        RUNTIME_OUTPUT_DIRECTORY "bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}"
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE False
        INTERPROCEDURAL_OPTIMIZATION False
)

# PREPROCESSOR DEFINITIONS
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "_CRT_SECURE_NO_WARNINGS"
)


if(CMAKE_BUILD_TYPE STREQUAL Debug) # DEBUG
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "MC_DEBUG"
    )
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-g>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-g>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++23>
    )
elseif (CMAKE_BUILD_TYPE STREQUAL Release) # RELEASE
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "MC_RELEASE"
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++23>
    )
elseif (CMAKE_BUILD_TYPE STREQUAL Dist) # DISTRIBUTION
    target_compile_definitions(${PROJECT_NAME} PRIVATE
            "MC_DIST"
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-m64>
            $<$<COMPILE_LANGUAGE:C>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-m64>
            $<$<COMPILE_LANGUAGE:CXX>:-O2>
            $<$<COMPILE_LANGUAGE:CXX>:-std=c++23>
    )
endif ()

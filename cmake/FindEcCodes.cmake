option(USE_ECCODES_CONDA "Using CONDA eccodes" OFF)

if(WIN32 AND (NOT CYGWIN) AND (NOT USE_ECCODES_CONDA))
    option(USE_OPENJP "Using OpenJpeg" ON)

    if(USE_OPENJP)
        find_library(OPENJP_LIBRARY
            NAMES openjp2
            PATHS ${OPENJP_INSTALL_PREFIX}
            PATH_SUFFIXES lib
            NO_DEFAULT_PATH
            )
        if(OPENJP_LIBRARY)
            set(OPENJP_FOUND TRUE)
            message(STATUS "Found OpenJPEG: ${OPENJP_LIBRARY}")
        endif()
    endif()


    if(ECCODES_INSTALL_PREFIX)
        set(EcCodes_INCLUDE_HINTS ${ECCODES_INSTALL_PREFIX}/include)
        set(EcCodes_LIBRARY_HINTS ${ECCODES_INSTALL_PREFIX}/lib)
    endif()

    find_path(
        EcCodes_INCLUDE_DIR
        NAMES eccodes.h
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_INCLUDE_DIR} /usr /usr/local
        PATH_SUFFIXES include
        NO_DEFAULT_PATH
    )

	find_file(
        EcCodes_LIBRARY
		NAMES grib_api_lib.lib
        PATHS ${ECCODES_INSTALL_PREFIX} ${EcCodes_LIBRARY_DIR}
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
	)
else()
    find_package(
        eccodes 
        REQUIRED
        CONFIG
    )
    message("ECCODES_INCLUDE_DIRS ${ECCODES_INCLUDE_DIRS}")
    message("ECCODES_TPL_LIBRARIES ${ECCODES_TPL_LIBRARIES}")
    message("ECCODES_SELF_INCLUDE_DIRS ${ECCODES_SELF_INCLUDE_DIRS}")

    list (GET ECCODES_INCLUDE_DIRS 0 EcCodes_INCLUDE_DIR)
    set(EcCodes_LINK_LIBRARIES ${ECCODES_TPL_LIBRARIES})

    message("EcCodes_INCLUDE_DIR ${EcCodes_INCLUDE_DIR}")

	find_library(
        EcCodes_LIBRARY
		NAMES eccodes
        PATHS "${EcCodes_INCLUDE_DIR}/.."
		PATH_SUFFIXES lib
        NO_DEFAULT_PATH
    )
    message("EcCodes_LIBRARY ${EcCodes_LIBRARY}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(EcCodes
	REQUIRED_VARS EcCodes_INCLUDE_DIR EcCodes_LIBRARY
)

if(USE_OPENJP AND NOT OPENJP_FOUND)
    if(EcCodes_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find openjpeg library")
    endif()
endif()

if(EcCodes_FOUND AND NOT TARGET EcCodes::EcCodes)

	add_library(EcCodes::EcCodes UNKNOWN IMPORTED)
	set_target_properties(EcCodes::EcCodes PROPERTIES
		IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
		IMPORTED_LOCATION "${EcCodes_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${EcCodes_INCLUDE_DIR}")

    if(WIN32 AND (NOT CYGWIN))
        set_target_properties(EcCodes::EcCodes PROPERTIES
            INTERFACE_LINK_LIBRARIES "${OPENJP_LIBRARY}")
    else()
        set_target_properties(EcCodes::EcCodes PROPERTIES
            INTERFACE_LINK_LIBRARIES "${EcCodes_LINK_LIBRARIES}")
    endif()

	mark_as_advanced(
		EcCodes_INCLUDE_DIR
		EcCodes_LIBRARY
	)
endif()
add_library(grib_message_handler STATIC)

set(SOURCE_FILES
	src/grib_message_handler.cpp
	src/grib_file_handler.cpp
	src/grib_handler.cpp
)

target_sources(grib_message_handler
	PRIVATE
		${SOURCE_FILES}
	)

target_include_directories(grib_message_handler 
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(grib_message_handler 
	PUBLIC
		EcCodes::EcCodes
)

add_library(NuwePyeccodes::grib_message_handler ALIAS grib_message_handler)
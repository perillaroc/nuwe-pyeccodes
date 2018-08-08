project(grib_message_handler)

set(SOURCE_FILES
	src/grib_message_handler.cpp
	src/grib_file_handler.cpp
)

add_library(grib_message_handler STATIC ${SOURCE_FILES})

target_link_libraries(grib_message_handler PUBLIC
	EcCodes::EcCodes
)
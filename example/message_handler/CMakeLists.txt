#project(example_message_handler)

set(TEST_DATA_ROOT ${NUWE_DATA_ROOT})

configure_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/example_config.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/example_config.h"
)

add_executable(example_message_handler main.cpp)

target_link_libraries(example_message_handler PUBLIC
	NuwePyeccodes::grib_message_handler
)

target_include_directories(example_message_handler PUBLIC
	${CMAKE_CURRENT_BINARY_DIR}
)
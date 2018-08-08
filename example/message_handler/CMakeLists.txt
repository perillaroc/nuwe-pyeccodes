project(example_message_handler)

set(TEST_DATA_ROOT ${NUWE_DATA_ROOT})

configure_file (
	"${PROJECT_SOURCE_DIR}/example_config.h.in"
    "${PROJECT_BINARY_DIR}/example_config.h"
)


add_executable(example_message_handler main.cpp)

target_link_libraries(example_message_handler PUBLIC
	NuwePyeccodes::grib_message_handler
)

target_include_directories(example_message_handler PUBLIC
	${PROJECT_BINARY_DIR}
)
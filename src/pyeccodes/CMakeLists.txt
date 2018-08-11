project(pyeccodes)

find_package(pybind11 REQUIRED)

pybind11_add_module(nuwe_pyeccodes nuwe_pyeccodes.cpp)

configure_file (
	"${PROJECT_SOURCE_DIR}/setup.py.in"
    "${PROJECT_BINARY_DIR}/setup.py"
)

target_link_libraries(nuwe_pyeccodes PUBLIC
	NuwePyeccodes::grib_message_handler
)

set_target_properties(nuwe_pyeccodes PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
	LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
	ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)
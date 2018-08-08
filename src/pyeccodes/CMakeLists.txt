project(pyeccodes)

find_package(pybind11 REQUIRED)

pybind11_add_module(nuwe_pyeccodes nuwe_pyeccodes.cpp)

target_link_libraries(nuwe_pyeccodes PUBLIC
	NuwePyeccodes::grib_message_handler
)
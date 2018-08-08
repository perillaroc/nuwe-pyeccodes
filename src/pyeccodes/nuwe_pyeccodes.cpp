#include <pybind11/pybind11.h>
#include <grib_message_handler.h>
#include <grib_file_handler.h>

namespace py = pybind11;
using namespace pyeccodes;

PYBIND11_MODULE(nuwe_pyeccodes, m) {
	py::class_<GribMessageHandler>(m, "GribMessageHandler")
		.def(py::init<>())
		.def("getString", &GribMessageHandler::getString)
		.def("getLong", &GribMessageHandler::getLong)
		.def("getDouble", &GribMessageHandler::getDouble);

	py::class_<GribFileHandler>(m, "GribFileHandler")
		.def(py::init<>())
		.def("openFile", &GribFileHandler::openFile)
		.def("closeFile", &GribFileHandler::closeFile)
		.def("next", &GribFileHandler::next);
}
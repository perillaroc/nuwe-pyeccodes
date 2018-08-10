#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <algorithm>

#include <grib_message_handler.h>
#include <grib_file_handler.h>

namespace py = pybind11;
using namespace pyeccodes;

PYBIND11_MODULE(nuwe_pyeccodes, m) {
	py::class_<GribMessageHandler>(m, "GribMessageHandler")
		.def(py::init<>())
		.def("getSize", &GribMessageHandler::getSize)
		.def("getLength", &GribMessageHandler::getLength)
		.def("getString", &GribMessageHandler::getString)
		.def("setString", &GribMessageHandler::setString)
		.def("getLong", &GribMessageHandler::getLong)
		.def("setLong", &GribMessageHandler::setLong)
		.def("getDouble", &GribMessageHandler::getDouble)
		.def("setDouble", &GribMessageHandler::setDouble)
		.def("getDoubleArray", [](GribMessageHandler &message_handler, const std::string &key){
			auto values = message_handler.getDoubleArray(key);
			
			py::array_t<double> py_values(values.size());
			py::buffer_info buffer = py_values.request();
			double *buffer_pointer = (double*)buffer.ptr;
			std::copy(values.begin(), values.end(), buffer_pointer);
			return py_values;
		})
		.def("setDoubleArray", [](GribMessageHandler &message_handler, const std::string &key, py::array_t<double> array) {
			py::buffer_info buffer = array.request();
			auto size = buffer.size;
			double* ptr = (double *)buffer.ptr;
			std::vector<double> value_vector(size);
			std::copy(ptr, ptr + size, value_vector.begin());
			message_handler.setDoubleArray(key.c_str(), value_vector);
		})
		.def("writeMessage", &GribMessageHandler::witeMessage);

	py::class_<GribFileHandler>(m, "GribFileHandler")
		.def(py::init<>())
		.def("openFile", &GribFileHandler::openFile)
		.def("closeFile", &GribFileHandler::closeFile)
		.def("next", &GribFileHandler::next);
}
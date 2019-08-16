#include "eccodes_function.h"
#include <pybind11/numpy.h>

#include <grib_handler.h>


namespace pyeccodes {

namespace py = pybind11;

void init_eccodes_function(pybind11::module& m)
{
    py::class_<pyeccodes::GribHandler>(m, "GribHandler")
        .def(py::init<>());

    py::enum_<pyeccodes::GribKeyType>(m, "GribKeyType")
        .value("Undefined", pyeccodes::GribKeyType::Undefined)
        .value("Long", pyeccodes::GribKeyType::Long)
        .value("Double", pyeccodes::GribKeyType::Double)
        .value("String", pyeccodes::GribKeyType::String)
        .value("Bytes", pyeccodes::GribKeyType::Bytes)
        .value("Section", pyeccodes::GribKeyType::Section)
        .value("Label", pyeccodes::GribKeyType::Label)
        .value("Missing", pyeccodes::GribKeyType::Missing)
        .export_values();

    m.def("codes_grib_new_from_file", [](py::object arg1) {
        int fileDescriptor = PyObject_AsFileDescriptor(arg1.ptr());
        if (fileDescriptor >= 0) {
            auto infile = _fdopen(fileDescriptor, "rb");
            if (infile == NULL) {
                py::print("_fdopen failed");
            }
            return pyeccodes::codes_grib_new_from_file(infile);
        }
        else {
            throw std::invalid_argument("param must be a file");
        }
    }, py::return_value_policy::reference);

    m.def("codes_get_string", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getString(key);
    });

    m.def("codes_get_long", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getLong(key);
    });

    m.def("codes_get_double", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getDouble(key);
    });

    m.def("codes_get_size", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getSize(key);
    });

    m.def("codes_get_length", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getLength(key);
    });

    m.def("codes_get_double_array", [](pyeccodes::GribHandler* handler, const std::string& key) {
        auto values = handler->message_handler_->getDoubleArray(key);
        py::array_t<double> py_values(values.size());
        py::buffer_info buffer = py_values.request();
        double* buffer_pointer = (double*)buffer.ptr;
        std::copy(values.begin(), values.end(), buffer_pointer);
        return py_values;
    });

    m.def("get_native_type", [](pyeccodes::GribHandler* handler, const std::string& key) {
        return handler->message_handler_->getNativeType(key);
    });

    m.def("grib_handler_release", [](pyeccodes::GribHandler* handler) {
        delete handler;
        handler = nullptr;
    });
}
} // namespace pyeccodes
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <algorithm>

#include <grib_message_handler.h>
#include <grib_file_handler.h>

#ifdef _MSC_VER
# define NUWE_THREAD_LOCAL __declspec( thread )
#else
# define NUWE_THREAD_LOCAL __thread
#endif

#if defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR)
#include <windows.h>
#endif

#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
/* Our crt debug report handler allows us to temporarily disable asserts
 * just for the current thread.
 */

NUWE_THREAD_LOCAL int nuwe__crt_assert_enabled = TRUE;

static int nuwe__crt_dbg_report_handler(int report_type, char* message, int* ret_val) {
    if (nuwe__crt_assert_enabled || report_type != _CRT_ASSERT)
        return FALSE;

    if (ret_val) {
        /* Set ret_val to 0 to continue with normal execution.
         * Set ret_val to 1 to trigger a breakpoint.
        */

        if (IsDebuggerPresent())
            *ret_val = 1;
        else
            *ret_val = 0;
    }

    /* Don't call _CrtDbgReport. */
    return TRUE;
}
#else
NUWE_THREAD_LOCAL int nuwe__crt_assert_enabled = FALSE;
#endif

namespace py = pybind11;
using namespace pyeccodes;

PYBIND11_MODULE(_pyeccodes, m) {
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
        .def("handleNewFromFile", [](GribFileHandler& file_handler, py::object arg1) {
#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
            _CrtSetReportHook(nuwe__crt_dbg_report_handler);
            nuwe__crt_assert_enabled = FALSE;
#endif
            int fileDescriptor = PyObject_AsFileDescriptor(arg1.ptr());
            py::print("fileDescriptor=", fileDescriptor);
            if (fileDescriptor >= 0) {
                
                auto infile = _fdopen(fileDescriptor, "rb");

                if (infile == NULL) {
                    py::print("_fdopen failed");
                }
                return file_handler.setFile(infile);
            } else {
                throw std::invalid_argument("param must be a file");
            }
#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
            nuwe__crt_assert_enabled = TRUE;
#endif
        })
		.def("next", &GribFileHandler::next);
}
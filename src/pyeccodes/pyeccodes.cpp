#include <pybind11/pybind11.h>

#include "eccodes_function.h"
#include "handler_class.h"

PYBIND11_MODULE(_pyeccodes, m) {
    pyeccodes::init_eccodes_function(m);
    pyeccodes::init_handler_class(m);
}
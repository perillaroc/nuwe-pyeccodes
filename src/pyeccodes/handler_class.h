#pragma once
#include <pybind11/pybind11.h>

namespace pyeccodes {

void init_handler_class(pybind11::module& m);

} // namespace pyeccodes
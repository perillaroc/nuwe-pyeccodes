#pragma once
#include <pybind11/pybind11.h>

namespace pyeccodes {

void init_eccodes_function(pybind11::module& m);

} // namespace pyeccodes
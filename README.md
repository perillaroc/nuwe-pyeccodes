# nuwe-pyeccodes

A python binding for ecCodes for python in Windows.

~~ecCodes by ECMWF has its own python binding which only supports python 2 and s not available on Windows.~~ The new eccodes package on conda-forge can be used in python 3 and windows, and also supports JPEG packing. **So, please use the official python binding.**

`nuwe-pyeccodes` provides some simple methods to process GRIB2 data based on ecCodes and supports python 3 (python 2 is not supported currently).

## Requirments

### ecCodes

Install ecCodes using CMake in Linux or Visual Studio on Windows.

It is recommended to build under anaconda on Windows (Enable `USE_ECCODES_CONDA` option for CMake).

### pybind11 and python

Choose a python distribution (official Python or Anaconda Python) and install `pybind11` package.

## Building

Use CMake to build from source code.

Add `pybind11` and `ecCodes` cmake module path to `CMAKE_PREFIX_PATH`.

If you aren't using anaconda on Windows, some Cmake variables are availabel to help find required libraries.

- `OPENJP_INSTALL_PREFIX`: OpenJPEG install prefix.
- `EcCodes_INCLUDE_DIR`: ecCodes include directory.
- `EcCodes_LIBRARY_DIR`: ecCodes library directory.

## Getting Started

`nuwe-pyeccodes` supports two kind of APIs: handler classes and ecCodes functions.

### Handler Classes

```py
import nuwe_pyeccodes

grib_file_handler = nuwe_pyeccodes.GribFileHandler()
# open a grib file
grib_file_handler.openFile("grib_file_path")
while True:
    # load a message in grib file.
    grib_message_handler = grib_file_handler.next()
    if grib_message_handler is None:
        break

    # get string, long or double key value
    print(grib_message_handler.getString("shortName"))
    print(grib_message_handler.getLong("Ni"))
    print(grib_message_handler.getDouble("level"))

    # values is Numpy array.
    values = grib_message_handler.getDoubleArray("values")
    print(values[0])

grib_file_handler.closeFile()
```

### ecCodes Functions

Some `eccodes-python` functions is supported. Such as:

- `codes_grib_new_from_file`
- `codes_release`
- `codes_get`
- `codes_get_long`
- `codes_get_double`
- `codes_get_string`
- `codes_get_size`
- `codes_get_length`
- `codes_get_double_array`

The API is the same as `eccodes`, so just one import line needs to be changed.

From 

```py
from eccodes import *
```

To

```py
from nuwe_pyeccodes import *
```

## Example

C++ Examples are in `example` directory.

## License

Copyright &copy; 2018-2019, Periilla Roc

`nuwe-pyeccodes` is licensed under [The MIT License](./LICENSE.md).
# nuwe-pyeccodes

A python binding for ecCodes for python 3 in Windows.

ecCodes by ECMWF has its own python binding which only supports python 2 and is not available on Windows.
`nuwe-pyeccodes` provides some simple methods to process GRIB2 data based on ecCodes.


## Requirments

### ecCodes

Install ecCodes using CMake in Linux or Visual Studio on Windows.

Use OpenJPEG as the JPEG decoder on Windows.

### pybind11 and python

Choose a python distribution (official Python or Anaconda Python).

Download the latest pybind11 and build with CMake.

## Building

Use CMake to build from source code.

Some Cmake variables are availabel to help find required libraries on Windows.

- `OPENJP_INSTALL_PREFIX`: OpenJPEG install prefix.
- `EcCodes_INCLUDE_DIR`: ecCodes include directory.
- `EcCodes_LIBRARY_DIR`: ecCodes library directory.

## Getting Started

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

## Example

C++ Examples are in `example` directory.

## License

Copyright &copy; 2018, Periilla Roc

`nuwe-pyeccodes` is licensed under [The MIT License](./LICENSE.md).
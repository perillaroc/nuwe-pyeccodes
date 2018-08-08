#pragma once

#include <eccodes.h>

namespace nuwe_pyeccodes {

class GribMessageHandler
{
public:
	GribMessageHandler(codes_handle* handle);

	codes_handle* grib_handle = nullptr;
};
}
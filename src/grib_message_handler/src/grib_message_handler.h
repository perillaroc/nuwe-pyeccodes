#pragma once

#include <eccodes.h>
#include <string>

namespace nuwe_pyeccodes {

class GribMessageHandler
{
public:
	GribMessageHandler(codes_handle* handle);

	std::string getString(const std::string &key);
	long getLong(const std::string &key);
	double getDouble(const std::string &key);

	codes_handle* grib_handle = nullptr;
};
}
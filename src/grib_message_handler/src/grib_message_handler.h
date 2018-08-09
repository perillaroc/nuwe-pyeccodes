#pragma once

#include <eccodes.h>
#include <string>
#include <vector>

namespace pyeccodes {

class GribMessageHandler
{
public:
	GribMessageHandler();

	void setHandle(codes_handle* handle);

	std::string getString(const std::string &key);
	long getLong(const std::string &key);
	double getDouble(const std::string &key);

	std::vector<double> getDoubleArray(const std::string &key);

private:
	codes_handle* grib_handle_ = nullptr;
};
}
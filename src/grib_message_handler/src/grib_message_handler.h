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
	void setString(const std::string &key, const std::string &value);
	
	long getLong(const std::string &key);
	void setLong(const std::string &key, long value);

	double getDouble(const std::string &key);
	void setDouble(const std::string &key, double value);

	size_t getSize(const std::string &key);
	size_t getLength(const std::string &key);

	std::vector<double> getDoubleArray(const std::string &key);
	void setDoubleArray(const std::string &key, std::vector<double> &values);

	void witeMessage(const std::string &file_path, const std::string &file_mode);

private:
	codes_handle* grib_handle_ = nullptr;
};
}
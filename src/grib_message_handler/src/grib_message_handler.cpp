#include "grib_message_handler.h"

using namespace nuwe_pyeccodes;

GribMessageHandler::GribMessageHandler(codes_handle* handle) {
	grib_handle = handle;
}

std::string GribMessageHandler::getString(const std::string &key) {
	size_t length = 0;
	codes_get_length(grib_handle, key.c_str(), &length);
	char* value = new char[length];
	int error = codes_get_string(grib_handle, key.c_str(), value, &length);
	std::string value_string{ value };
	delete[] value;
	return value_string;
}

long GribMessageHandler::getLong(const std::string &key) {
	long value = 0;
	int error = codes_get_long(grib_handle, key.c_str(), &value);
	return value;
}

double GribMessageHandler::getDouble(const std::string & key)
{
	double value = 0.0;
	int error = codes_get_double(grib_handle, key.c_str(), &value);
	return value;
}
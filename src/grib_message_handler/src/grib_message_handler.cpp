#include "grib_message_handler.h"

using namespace pyeccodes;

GribMessageHandler::GribMessageHandler() {
}

void pyeccodes::GribMessageHandler::setHandle(codes_handle * handle)
{
	grib_handle_ = handle;
}

std::string GribMessageHandler::getString(const std::string &key) {
	size_t length = 0;
	codes_get_length(grib_handle_, key.c_str(), &length);
	char* value = new char[length];
	int error = codes_get_string(grib_handle_, key.c_str(), value, &length);
	std::string value_string{ value };
	delete[] value;
	return value_string;
}

long GribMessageHandler::getLong(const std::string &key) {
	long value = 0;
	int error = codes_get_long(grib_handle_, key.c_str(), &value);
	return value;
}

double GribMessageHandler::getDouble(const std::string & key)
{
	double value = 0.0;
	int error = codes_get_double(grib_handle_, key.c_str(), &value);
	return value;
}

std::vector<double> GribMessageHandler::getDoubleArray(const std::string &key) {
	size_t length = 0;
	codes_get_size(grib_handle_, key.c_str(), &length);
	std::vector<double> values(length);
	codes_get_double_array(grib_handle_, key.c_str(), values.data(), &length);
	return values;
}
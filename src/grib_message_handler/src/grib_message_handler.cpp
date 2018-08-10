#include "grib_message_handler.h"

using namespace pyeccodes;

GribMessageHandler::GribMessageHandler() {
}

void pyeccodes::GribMessageHandler::setHandle(codes_handle * handle)
{
	grib_handle_ = handle;
}

std::string GribMessageHandler::getString(const std::string &key) {
	auto length = getLength(key);
	char* value = new char[length];
	auto error = codes_get_string(grib_handle_, key.c_str(), value, &length);
	std::string value_string{ value };
	delete[] value;
	return value_string;
}

void pyeccodes::GribMessageHandler::setString(const std::string & key, const std::string & value)
{
	auto length = value.length();
	auto error = codes_set_string(grib_handle_, key.c_str(), value.c_str(), &length);
}

long GribMessageHandler::getLong(const std::string &key) {
	long value = 0;
	auto error = codes_get_long(grib_handle_, key.c_str(), &value);
	return value;
}

void pyeccodes::GribMessageHandler::setLong(const std::string & key, long value)
{
	auto error = codes_set_long(grib_handle_, key.c_str(), value);
}

double GribMessageHandler::getDouble(const std::string & key)
{
	double value = 0.0;
	auto error = codes_get_double(grib_handle_, key.c_str(), &value);
	return value;
}

void pyeccodes::GribMessageHandler::setDouble(const std::string & key, double value)
{
	auto error = codes_set_double(grib_handle_, key.c_str(), value);
}

size_t GribMessageHandler::getSize(const std::string &key) {
	size_t length = 0;
	auto error = codes_get_size(grib_handle_, key.c_str(), &length);
	return length;
}

size_t GribMessageHandler::getLength(const std::string &key) {
	size_t length = 0;
	auto error = codes_get_length(grib_handle_, key.c_str(), &length);
	return length;

}

std::vector<double> GribMessageHandler::getDoubleArray(const std::string &key) {
	auto length = getSize(key);
	std::vector<double> values(length);
	codes_get_double_array(grib_handle_, key.c_str(), values.data(), &length);
	return values;
}

void pyeccodes::GribMessageHandler::setDoubleArray(const std::string & key, std::vector<double>& values)
{
	auto error = codes_set_double_array(grib_handle_, key.c_str(), values.data(), values.size());
}

void pyeccodes::GribMessageHandler::witeMessage(const std::string & file_path, const std::string & file_mode)
{
	codes_write_message(grib_handle_, file_path.c_str(), file_mode.c_str());
}

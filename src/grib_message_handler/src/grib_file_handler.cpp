#include "grib_file_handler.h"

using namespace pyeccodes;

GribFileHandler::GribFileHandler() 
{

}

pyeccodes::GribFileHandler::~GribFileHandler()
{
	if (grib_handle_) {
		codes_handle_delete(grib_handle_);
		grib_handle_ = nullptr;
	}
	if (grib_file_) {
		fclose(grib_file_);
		grib_file_ = nullptr;
	}
}

void GribFileHandler::openFile(const std::string & file_path)
{
	grib_file_ = fopen(file_path.c_str(), "rb");

}

void pyeccodes::GribFileHandler::closeFile()
{
	if (grib_handle_) {
		codes_handle_delete(grib_handle_);
		grib_handle_ = nullptr;
	}
	if (grib_file_) {
		fclose(grib_file_);
		grib_file_ = nullptr;
	}
}

std::unique_ptr<GribMessageHandler> pyeccodes::GribFileHandler::next()
{
	int error = 0;
	if (grib_handle_) {
		codes_handle_delete(grib_handle_);
		grib_handle_ = nullptr;
	}
	grib_handle_ = codes_grib_handle_new_from_file(nullptr, grib_file_, &error);
	if (grib_handle_) {
		auto message_handler = std::make_unique<GribMessageHandler>();
		message_handler->setHandle(grib_handle_);
		return message_handler;
	} else {
		return std::unique_ptr<GribMessageHandler>();
	}
}

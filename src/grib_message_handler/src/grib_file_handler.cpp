#include "grib_file_handler.h"
// #include <iostream>

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

void pyeccodes::GribFileHandler::setFile(std::FILE* grib_file)
{
    grib_file_ = grib_file;
}

std::unique_ptr<GribMessageHandler> pyeccodes::GribFileHandler::next()
{
	int error = 0;
	if (grib_handle_) {
		codes_handle_delete(grib_handle_);
		grib_handle_ = nullptr;
	}
	// std::cout<<"codes_grib_handle_new_from_file"<<std::endl;
	grib_handle_ = codes_grib_handle_new_from_file(nullptr, grib_file_, &error);
	// std::cout<<"codes_grib_handle_new_from_file..."<<error<<std::endl;
	if (grib_handle_) {
		// std::cout<<"get handler..."<<std::endl;
		auto message_handler = std::make_unique<GribMessageHandler>();
		message_handler->setHandle(grib_handle_);
		return message_handler;
	} else {
		// std::cout<<"no grib handler"<<std::endl;
		return std::unique_ptr<GribMessageHandler>();
	}
}

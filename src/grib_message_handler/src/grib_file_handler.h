#pragma once

#include <string>
#include <memory>
#include <eccodes.h>

#include "grib_message_handler.h"


namespace pyeccodes {

class GribFileHandler 
{
public:
	GribFileHandler();
	~GribFileHandler();

	void openFile(const std::string &file_path);
	void closeFile();

	std::unique_ptr<GribMessageHandler> next();


private:
	std::string data_file_path_;

	FILE* grib_file_ = nullptr;
	codes_handle* grib_handle_ = nullptr;
};
}
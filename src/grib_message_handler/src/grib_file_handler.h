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

    void setFile(std::FILE* grib_file);

	std::unique_ptr<GribMessageHandler> next();


private:
	std::string data_file_path_;

	std::FILE* grib_file_ = nullptr;
	codes_handle* grib_handle_ = nullptr;
};
}
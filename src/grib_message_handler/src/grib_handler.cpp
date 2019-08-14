#include "grib_handler.h"
#include <iostream>

namespace pyeccodes {

GribHandler::~GribHandler()
{
    std::cout << "~GribHandler()" << std::endl;
}

GribHandler* codes_grib_new_from_file(std::FILE* file)
{
    auto file_handler = new pyeccodes::GribFileHandler;
    file_handler->setFile(file);

    auto handler = new pyeccodes::GribHandler;
    handler->file_handler_ = file_handler;
    handler->message_handler_ = file_handler->next();
    return handler;
}
} // namespace pyeccodes
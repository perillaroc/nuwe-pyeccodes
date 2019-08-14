#pragma once
#include "grib_file_handler.h"

namespace pyeccodes {

class GribHandler {
public:
    GribFileHandler* file_handler_ = nullptr;
    std::unique_ptr<GribMessageHandler> message_handler_;
};

GribHandler* codes_grib_new_from_file(std::FILE* file);

} // namespace pyeccodes
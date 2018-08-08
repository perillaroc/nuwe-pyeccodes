#include "grib_message_handler.h"

using namespace nuwe_pyeccodes;

GribMessageHandler::GribMessageHandler(codes_handle* handle) {
	grib_handle = handle;
}
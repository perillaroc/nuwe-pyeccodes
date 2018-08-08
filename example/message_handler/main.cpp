#include <iostream>

#include <example_config.h>

#include <grib_message_handler.h>
#include <grib_file_handler.h>

using namespace nuwe_pyeccodes;
using namespace std;

int main() {
	string data_path = string(TEST_DATA_ROOT) + string("/t.grb2");

	auto file_handler = std::make_shared<GribFileHandler>();
	file_handler->openFile(data_path);
	
	std::unique_ptr<GribMessageHandler> h;
	while (h = file_handler->next()) {
		std::cout << h->getString("shortName") << std::endl;
	}

	file_handler->closeFile();

	return 0;
}
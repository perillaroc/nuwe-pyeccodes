#include <iostream>

#include <example_config.h>

#include <grib_message_handler.h>
#include <grib_file_handler.h>

using namespace pyeccodes;
using namespace std;

int main() {
	string data_path = string(TEST_DATA_ROOT) + string("/t.grb2");
	std::cout<<data_path<<std::endl;

	auto file_handler = std::make_shared<GribFileHandler>();
	
	std::cout<<"file opening..."<<std::endl;
	file_handler->openFile(data_path);
	std::cout<<"file opening...Done"<<std::endl;
	
	std::unique_ptr<GribMessageHandler> h;
	while (h = file_handler->next()) {
		std::cout<<"get message"<<std::endl;
		std::cout << h->getString("shortName") << std::endl;
		std::cout << h->getLong("Ni") << std::endl;
		std::cout << h->getDouble("level") << std::endl;
		std::cout << h->getSize("values") << std::endl;
		std::cout << h->getLength("typeOfLevel") << std::endl;
		auto values = h->getDoubleArray("values");
		std::cout << values.size() << ": index 0: " << values[0] << std::endl;

		h->setString("shortName", "u");
		std::cout << h->getString("shortName") << std::endl;
	}

	std::cout<<"file closing..."<<std::endl;
	file_handler->closeFile();
	std::cout<<"file closing...done"<<std::endl;

	return 0;
}
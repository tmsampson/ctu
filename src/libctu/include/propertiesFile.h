#include "dataStore.h"
#include <iostream>

class PropertiesFile : public DataStore
{
public:
	PropertiesFile(std::string path)
		: DataStore(path)
	{
		// add two values
		Add<int>("andrew", 22);
		Add<std::string>("hello", "world");

		// check if they have been added
		std::cout << "Andrew is " << Get<int>("andrew", 0) << " years old" << std::endl;
		std::cout << "Hello " << Get<std::string>("hello", "error") << "!" << std::endl;

		// remove one
		Remove("andrew");

		// check them again, "andrew" should now be 0 years old
		std::cout << "Andrew is " << Get<int>("andrew", 0) << " years old" << std::endl;
		std::cout << "Hello " << Get<std::string>("hello", "error") << "!" << std::endl;
	}
};
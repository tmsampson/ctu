#include "JSONFile.h"
#include <iostream>

class PropertiesFile : public JSONFile
{
public:
	PropertiesFile(std::string path)
		: JSONFile(path)
	{
		// add two values
		Add<int>("andrew", 22);
		Add<std::string>("hello", "world");

		// check if they have been added
		std::cout << "Andrew is " << Get<int>("andrew", 0) << " years old" << std::endl;
		std::cout << "Hello " << Get<std::string>("hello", "error") << "!" << std::endl;

		// remove one
		Remove("andrew");
		Set("hello", "andrew");

		// check them again, "andrew" should now be 0 years old
		std::cout << "Andrew is " << Get<int>("andrew", 0) << " years old" << std::endl;
		std::cout << "Hello " << Get<std::string>("hello", "error") << "!" << std::endl;
	}
};
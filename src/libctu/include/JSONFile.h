#include "json/json.h"
#include <iostream>
#include <fstream>
#include <string>

class JSONFile
{
private:
	std::string m_path;
	Json::Value m_root;
	Json::Reader m_reader;

public:
	JSONFile(std::string path)
		: m_path(path)
	{
		// open the input file
		std::ifstream inputFile(m_path);
		// used to hold the contents of the file, if it opens and if its not empty
		std::string fileContents("");

		// if the file opens, read the contents into fileContents, otherwise error
  		if (inputFile.is_open())
  		{
  			std::string line("");

  			while (inputFile.good())
		    {
		      std::getline(inputFile, line);
		      fileContents += line;
		    }

		    inputFile.close();
		}
		else
		{
			std::cout << "Failed to open the file at " << m_path << std::endl;
			return;
		}

		// parse the file contents, error if it fails
		if (!m_reader.parse(fileContents, m_root))
		{
			std::cout << "Failed to parse file at " << path << std::endl;
			std::cout << "Error: " << m_reader.getFormattedErrorMessages();
			return;
		}
	}

	~JSONFile()
	{
		// save by default on destruction
		Save();
	}

	void Save()
	{
		// Make a new JSON document for the configuration. Preserve original comments.
		Json::StyledWriter writer;
		std::string outputString = writer.write( m_root );
		
		// open the output file
		std::ofstream outputFile(m_path);
		if (outputFile.is_open())
		{
			// write the data out
			outputFile << outputString;
			outputFile.close();
		}
		else
		{
			std::cout << "Failed to open the file at " << m_path << std::endl;
		}
	}

	template <typename T>
	void Add(std::string key, T value)
	{
		Set<T>(key, value);
	}

	void Remove(std::string key)
	{
		m_root.removeMember(key);
	}

	template <typename T>
	void Set(std::string key, T value)
	{
		m_root[key] = value;
	}

	// template specialisations for getting values

	template <typename T>
	T Get(std::string key, T defaultValue)
	{
		return m_root.get(key, defaultValue);
	}

	template <>
	bool Get<bool>(std::string key, bool defaultValue)
	{
		return m_root.get(key, defaultValue).asBool();
	}

	template <>
	int Get<int>(std::string key, int defaultValue)
	{
		return m_root.get(key, defaultValue).asInt();
	}

	template <>
	unsigned int Get<unsigned int>(std::string key, unsigned int defaultValue)
	{
		return m_root.get(key, defaultValue).asUInt();
	}

	template <>
	float Get<float>(std::string key, float defaultValue)
	{
		return m_root.get(key, defaultValue).asFloat();
	}

	template <>
	double Get<double>(std::string key, double defaultValue)
	{
		return m_root.get(key, defaultValue).asDouble();
	}

	template <>
	std::string Get<std::string>(std::string key, std::string defaultValue)
	{
		return m_root.get(key, defaultValue).asString();
	}
};
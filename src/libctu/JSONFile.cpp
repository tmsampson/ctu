#include "JSONFile.h"

JSONFile::JSONFile(const std::string& path)
	: m_path(path), m_isLoaded(false)
{
	// open the input file
	std::ifstream inputFile(m_path);
	// used to hold the contents of the file, if it opens and if its not empty
	std::string fileContents("");

	// if the file opens, read the contents into fileContents, otherwise error
	if (!inputFile.is_open())
		return;

	m_isLoaded = true;

	std::string line("");

	while (inputFile.good())
	{
		std::getline(inputFile, line);
		fileContents += line;
	}

	inputFile.close();

	// parse the file contents, error if it fails
	if (!m_reader.parse(fileContents, m_root))
	{
		std::cout << "Failed to parse file at " << path << std::endl;
		std::cout << "Error: " << m_reader.getFormattedErrorMessages();
		return;
	}
}

JSONFile::~JSONFile()
{
	// save by default on destruction
	Save();
}

bool JSONFile::IsLoaded() const
{
	return m_isLoaded;
}

bool JSONFile::Save()
{
	// create a JSON stylised output string
	Json::StyledWriter writer;
	std::string outputString = writer.write(m_root);
	
	// open the output file
	std::ofstream outputFile(m_path);
	if (!outputFile.is_open())
		return false;

	// write the data out
	outputFile << outputString;
	outputFile.close();
	m_isLoaded = true;

	return true;
}

void JSONFile::Remove(const std::string& key, bool saveImmediate)
{
	m_root.removeMember(key);

	if (saveImmediate)
		Save();
}

// template specialisations for getting values

template <typename T>
T JSONFile::Get(const std::string& key, const T& defaultValue)
{
	return m_root.get(key, defaultValue);
}

template <>
bool JSONFile::Get<bool>(const std::string& key, const bool& defaultValue)
{
	return m_root.get(key, defaultValue).asBool();
}

template <>
int JSONFile::Get<int>(const std::string& key, const int& defaultValue)
{
	return m_root.get(key, defaultValue).asInt();
}

template <>
unsigned int JSONFile::Get<unsigned int>(const std::string& key, const unsigned int& defaultValue)
{
	return m_root.get(key, defaultValue).asUInt();
}

template <>
float JSONFile::Get<float>(const std::string& key, const float& defaultValue)
{
	return m_root.get(key, defaultValue).asFloat();
}

template <>
double JSONFile::Get<double>(const std::string& key, const double& defaultValue)
{
	return m_root.get(key, defaultValue).asDouble();
}

template <>
std::string JSONFile::Get<std::string>(const std::string& key, const std::string& defaultValue)
{
	return m_root.get(key, defaultValue).asString();
}
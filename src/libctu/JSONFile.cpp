#include "JSONFile.h"
#include "BasicTypes.h"

JSONFile::JSONFile(const std::string& path)
	: m_path(path), m_bLoadFailed(false), m_bParseFailed(false)
{
	std::ifstream inputFile(m_path.c_str());
	std::string fileContents;

	// Did the file specified by "path" open correctly?
	if(!inputFile.is_open())
	{
		m_bLoadFailed = true;
		return;
	}

	// Read JSON file contents
	std::string line("");
	while(inputFile.good())
	{
		std::getline(inputFile, line);
		fileContents += line;
	}
	inputFile.close();

	// Parse JSON string
	if(!m_reader.parse(fileContents, m_root))
	{
		// Do not allow partial parses
		m_root.clear();
		m_bLoadFailed = m_bParseFailed = true;
		printf("PARSE FAIL");
		return;
	}
}

JSONFile::~JSONFile()
{
	Save(); // Save by default on destruction
}

bool JSONFile::Save()
{
	// Make sure not to overwrite non-JSON files
	if(m_bParseFailed)
		return false;

	// Create a JSON "stylised" output string
	Json::StyledWriter writer;
	std::string outputString = writer.write(m_root);
	
	// Open the output file for writing
	std::ofstream outputFile(m_path.c_str());
	if(!outputFile.is_open())
		return false;

	// Write the JSON string to file
	outputFile << outputString;
	outputFile.close();

	m_bLoadFailed = false;
	return true;
}

bool JSONFile::IsLoaded() const
{
	return !m_bLoadFailed;
}

bool JSONFile::ContainsKey(const std::string& key) const
{
	return m_root.isMember(key);
}

bool JSONFile::Remove(const std::string& key, bool saveImmediate)
{
	if(!ContainsKey(key))
		return false;

	m_root.removeMember(key);
	if (saveImmediate)
		return Save();
	return true;
}

std::string JSONFile::GetLastError()
{
	return m_reader.getFormattedErrorMessages();
}

// **********************************************************************
// Template specialisations for getting values WITH default value
// **********************************************************************
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
s32 JSONFile::Get<s32>(const std::string& key, const s32& defaultValue)
{
	return m_root.get(key, defaultValue).asInt();
}

template <>
u32 JSONFile::Get<u32>(const std::string& key, const u32& defaultValue)
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
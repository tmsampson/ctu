#ifndef JSON_FILE_H
#define JSON_FILE_H

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
	bool m_isLoaded;

public:
	JSONFile(const std::string& path);
	~JSONFile();

	bool IsLoaded() const;
	bool Save();

	template <typename T>
	void Add(const std::string& key, const T& value, bool saveImmediate = false);

	void Remove(const std::string& key, bool saveImmediate = false);

	template <typename T>
	void Set(const std::string& key, const T& value, bool saveImmediate = false);

	template <typename T>
	T Get(const std::string& key, const T& defaultValue);
};

#include "JSONFile.inl"

#endif
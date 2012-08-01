#ifndef JSON_FILE_H
#define JSON_FILE_H

#include "json/json.h"
#include <iostream>
#include <fstream>
#include <string>

class JSONFile
{
	public:
		JSONFile(const std::string& path);
		~JSONFile();

		bool Save();
		bool IsLoaded() const;
		bool ContainsKey(const std::string& key) const;

		template <typename T>
		T Get(const std::string& key, const T& defaultValue);
		template <typename T>
		T Get(const std::string& key);
		template <typename T>
		bool Set(const std::string& key, const T& value, bool saveImmediate = false);

		bool Remove(const std::string& key, bool saveImmediate = false);
		std::string GetLastError();

	private:
		std::string m_path;
		Json::Value m_root;
		Json::Reader m_reader;
		bool m_bLoadFailed, m_bParseFailed;
};

#include "JSONFile.inl"
#endif
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

		bool IsLoaded() const;
		bool Save();

		template <typename T>
		void Set(const std::string& key, const T& value, bool saveImmediate = false);

		template <typename T>
		T Get(const std::string& key, const T& defaultValue);

		void Remove(const std::string& key, bool saveImmediate = false);

	private:
		std::string m_path;
		Json::Value m_root;
		Json::Reader m_reader;
		bool m_isLoaded;
};

#include "JSONFile.inl"
#endif
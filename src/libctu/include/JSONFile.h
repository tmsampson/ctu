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
		T Get(const std::string& key, const T& defaultValue);

		template <typename T>
		T Get(const std::string& key)
		{
			return JSONFile::Get<T>(key, T());
		}

		template <typename T>
		void Set(const std::string& key, const T& value, bool saveImmediate = false)
		{
			m_root[key] = value;
			if (saveImmediate)
				Save();
		}

		void Remove(const std::string& key, bool saveImmediate = false);

	private:
		std::string m_path;
		Json::Value m_root;
		Json::Reader m_reader;
		bool m_isLoaded;
};

#endif
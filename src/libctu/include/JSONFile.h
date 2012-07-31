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
		T Get(const std::string& key)
		{
			return JSONFile::Get<T>(key, T());
		}

		template <typename T>
		bool Set(const std::string& key, const T& value, bool saveImmediate = false)
		{
			if(key.empty())
				return false;

			m_root[key] = value;
			if (saveImmediate)
				return Save();

			return true;
		}

		void Remove(const std::string& key, bool saveImmediate = false);

	private:
		std::string m_path;
		Json::Value m_root;
		Json::Reader m_reader;
		bool m_isLoaded;
};

#endif
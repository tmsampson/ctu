#ifndef CONFIG_FILE_H
#define CONFIG_FILE_H

#include "json/json.h"
#include <string>

class ConfigFile
{
	public:
		ConfigFile(const std::string& path);
		~ConfigFile();

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
		std::string GetLastError() const;

	private:
		std::string m_path;
		Json::Value m_root;
		Json::Reader m_reader;
		bool m_bLoadFailed, m_bParseFailed;
};

#include "ConfigFile.inl"
#endif
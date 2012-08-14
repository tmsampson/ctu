template <typename T>
T ConfigFile::Get(const std::string& key)
{
	return ConfigFile::Get<T>(key, T());
}

template <typename T>
bool ConfigFile::Set(const std::string& key, const T& value, bool saveImmediate)
{
	if(key.empty())
		return false;

	m_root[key] = value;
	if (saveImmediate)
		return Save();

	return true;
}
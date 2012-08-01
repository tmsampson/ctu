template <typename T>
T JSONFile::Get(const std::string& key)
{
	return JSONFile::Get<T>(key, T());
}

template <typename T>
bool JSONFile::Set(const std::string& key, const T& value, bool saveImmediate)
{
	if(key.empty())
		return false;

	m_root[key] = value;
	if (saveImmediate)
		return Save();

	return true;
}
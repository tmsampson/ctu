template <typename T>
void JSONFile::Add(const std::string& key, const T& value, bool saveImmediate)
{
	Set<T>(key, value);

	if (saveImmediate)
		Save();
}

template <typename T>
void JSONFile::Set(const std::string& key, const T& value, bool saveImmediate)
{
	m_root[key] = value;

	if (saveImmediate)
		Save();
}
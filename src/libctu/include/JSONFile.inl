template <typename T>
void JSONFile::Set(const std::string& key, const T& value, bool saveImmediate)
{
	m_root[key] = value;

	if (saveImmediate)
		Save();
}
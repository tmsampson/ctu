#include "TaskList.h"
#include "Utils.h"
#include <fstream>

CTU::ESection::Enum StringToSection(const std::string& str)
{
	if(str == "HIGH")   { return CTU::ESection::HIGH;   }
	if(str == "MEDIUM") { return CTU::ESection::MEDIUM; }
	if(str == "LOW")    { return CTU::ESection::LOW;    }
	return CTU::ESection::NONE;
}

bool CTU::TaskList::Init(const std::string& taskListPath, const std::string& bullet)
{
	m_taskListPath = taskListPath;
	m_bullet = bullet;

	if (!Utils::TouchFile(taskListPath))
	{
		m_taskListPath = m_bullet = "";
		return false;
	}

	m_tasks.clear();
	return true;
}

bool CTU::TaskList::Parse()
{
	std::ifstream taskListFile(m_taskListPath.c_str());
	if(!taskListFile.is_open())
	{
		Utils::PrintLine(Utils::EColour::RED,
		                 "ERROR: could not open task list file: %s", m_taskListPath.c_str());
		return false;
	}

	u32 uLineNumber = 0;
	static std::string line;
	while(std::getline(taskListFile, line))
	{
		if(!ParseLine(line, m_bullet))
		{
			Utils::PrintLine(Utils::EColour::RED,
			                 "ERROR: task on line %d could not be parsed", uLineNumber + 1);
			Clear();
			return false;
		}
		++uLineNumber;
	}

	taskListFile.close();
	return true;
}

bool CTU::TaskList::ParseLine(const std::string& line, const std::string& bullet)
{
	// Empty line?
	if(line.empty())
		return true;

	// Section heading?
	if(*line.begin() == char("[")  && *line.rbegin() == char("]"))
	{
		std::string sectionName = line.substr(1, line.size() -1);
		m_currentSection = StringToSection(sectionName);
		if(m_currentSection == CTU::ESection::NONE)
		{
			Utils::PrintLine(Utils::EColour::RED,
			                 "ERROR: Invalid section name: '%s'", sectionName.c_str());
			return false;
		}
		return true;
	}

	// Task Item?
	if(line.size() <= bullet.size())
		return false;

	// Bullet present?
	if(bullet.size() && line.substr(0, bullet.size()) != bullet)
	{
		Utils::PrintLine(Utils::EColour::RED,
		                 "ERROR: Bullet point '%s' missing", bullet.c_str());
		return false;
	}

	std::string rawText = line.substr(bullet.size());
	return AddTask(rawText);
}

bool CTU::TaskList::Save()
{
	CTU_ASSERT(m_taskListPath.size() != 0, "Save path was blank");

	std::ofstream output(m_taskListPath.c_str());
	if(!output.is_open())
	{
		Utils::PrintLine(Utils::EColour::RED,
		                 "ERROR: Could not open task list file for writing: %s", m_taskListPath.c_str());
		return false;
	}

	std::vector<Task>::const_iterator i = m_tasks.begin();
	for(; i != m_tasks.end(); ++i)
		output << m_bullet << i->RawText << std::endl;
	output.close();
	return true;
}

void CTU::TaskList::PrintNumeric() const
{
	if(!GetTaskCount())
	{
		Utils::PrintLine(Utils::EColour::YELLOW, "active task list is empty");
		return;
	}

	std::vector<CTU::Task>::const_iterator i = m_tasks.begin();
	for(u32 uLine = 1; i != m_tasks.end(); ++i)
	{
		Utils::PrintLine("%d. %s", uLine, i->Contents.c_str());
		++uLine;
	}
}

bool CTU::TaskList::AddTask(const std::string& rawText)
{
	Task task;
	task.RawText  = rawText;
	task.Contents = rawText;
	task.Section  = m_currentSection;
	m_tasks.push_back(task);
	return true;
}

bool CTU::TaskList::RemoveTask(u32 uIndex)
{
	if (uIndex == 0)
		return false;
	if(uIndex > GetTaskCount())
		return false;
	m_tasks.erase(m_tasks.begin() + uIndex -1);
	return true;
}

bool CTU::TaskList::RemoveTask(u32 uIndex, std::string& removedItem)
{
	if (uIndex == 0)
		return false;
	if(uIndex > GetTaskCount())
		return false;
	removedItem = m_tasks[uIndex - 1].Contents;
	m_tasks.erase(m_tasks.begin() + uIndex -1);
	return true;
}

void CTU::TaskList::Clear()
{
	m_tasks.clear();
}

const std::string CTU::TaskList::GetPath() const
{
	return m_taskListPath;
}

u32 CTU::TaskList::GetTaskCount() const
{
	return m_tasks.size();
}

const std::vector<CTU::Task>& CTU::TaskList::GetAllTasks() const
{
	return m_tasks;
}
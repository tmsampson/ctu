#include "TaskList.h"
#include "Utils.h"
#include <fstream>
#include <assert.h>

bool CTU::TaskList::Init(const std::string& taskListPath, const std::string& bullet)
{
	m_taskListPath = taskListPath;
	m_bullet = bullet;

	return Utils::TouchFile(taskListPath);
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
			Utils::PrintLine(Utils::EColour::RED, "ERROR: task on line %d could not be parsed", uLineNumber);
			return false;
		}
		++uLineNumber;
	}

	taskListFile.close();
	return true;
}

bool CTU::TaskList::ParseLine(const std::string& line, const std::string& bullet)
{
	return true;
}

bool CTU::TaskList::AddTask(const std::string& rawText)
{
	Task task;
	task.RawText  = rawText;
	task.Contents = rawText;
	m_tasks.push_back(task);
	return true;
}

bool CTU::TaskList::Save()
{
	assert(m_taskListPath.size());

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
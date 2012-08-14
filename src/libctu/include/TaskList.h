#ifndef TASK_LIST_H_
#define TASK_LIST_H_

#include <string>
#include <vector>

namespace CTU
{
	class Task
	{
		public:
			std::string RawText;
			std::string Contents;
	};

	class TaskList
	{
		public:
			bool Parse(const std::string& taskListPath, const std::string& bullet);
			bool AddTask(const std::string& rawText);
			bool Save();

		private:
			bool ParseLine(const std::string& line, const std::string& bullet);
			std::string m_taskListPath, m_bullet;
			std::vector<Task> m_tasks;
	};
}



#endif
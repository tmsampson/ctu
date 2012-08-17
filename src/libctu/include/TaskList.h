#ifndef TASK_LIST_H_
#define TASK_LIST_H_

#include "BasicTypes.h"
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
			bool Init(const std::string& taskListPath, const std::string& bullet);
			bool Parse();
			bool AddTask(const std::string& rawText);
			const std::string GetPath() const;
			bool Save();

			u32 GetTaskCount() const;
			const std::vector<Task>& GetAllTasks() const;

		private:
			bool ParseLine(const std::string& line, const std::string& bullet);
			std::string m_taskListPath, m_bullet;
			std::vector<Task> m_tasks;
	};
}

#endif
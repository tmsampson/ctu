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
			bool Save();
			void PrintNumeric() const;

			bool AddTask(const std::string& rawText);
			bool RemoveTask(u32 uIndex);
			bool RemoveTask(u32 uIndex, std::string& removedItem);
			void Clear();

			const std::string GetPath() const;
			u32 GetTaskCount() const;
			const std::vector<Task>& GetAllTasks() const;

		private:
			bool ParseLine(const std::string& line, const std::string& bullet);
			std::string m_taskListPath, m_bullet;
			std::vector<Task> m_tasks;
	};
}

#endif
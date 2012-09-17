#ifndef TASK_LIST_H_
#define TASK_LIST_H_

#include "BasicTypes.h"
#include <string>
#include <vector>

namespace CTU
{
	namespace ESection
	{
		enum Enum { NONE = 0, LOW, MEDIUM, HIGH };
	}

	class Task
	{
		public:
			std::string RawText;
			std::string Contents;
			CTU::ESection::Enum Section;
	};

	class TaskList
	{
		public:
			TaskList() : m_currentSection(CTU::ESection::NONE) { }
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
			CTU::ESection::Enum m_currentSection;
	};
}

#endif
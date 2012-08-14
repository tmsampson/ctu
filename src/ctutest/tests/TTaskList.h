#ifndef T_TASK_LIST_H_
#define T_TASK_LIST_H_

#include "TaskList.h"
#include <gtest/gtest.h>
#include "Common.h"
#include <fstream>

class TTaskList : public ::testing::Test { };

// ************************************************
//  TTaskList::AddTask Tests
// ************************************************
TEST_F(TTaskList, AddTask_NoTasksAdded_TaskCountIsZero)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	ASSERT_TRUE(newList.GetTaskCount() == 0);
}

TEST_F(TTaskList, AddTask_AddOneTask_TaskCountIsOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add one task
	newList.AddTask("test");

	ASSERT_TRUE(newList.GetTaskCount() == 1);
}

TEST_F(TTaskList, AddTask_AddFourTasks_TaskCountIsFour)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add four tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");
	newList.AddTask("test4");

	ASSERT_TRUE(newList.GetTaskCount() == 4);
}

#endif
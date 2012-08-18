#ifndef T_TASK_LIST_H_
#define T_TASK_LIST_H_

#include "TaskList.h"
#include "Common.h"
#include <gtest/gtest.h>
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

	ASSERT_EQ(0, newList.GetTaskCount());
}

TEST_F(TTaskList, AddTask_AddOneTask_TaskCountIsOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add one task
	newList.AddTask("test");

	ASSERT_EQ(1, newList.GetTaskCount());
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

	ASSERT_EQ(4, newList.GetTaskCount());
}

// ************************************************
//  TTaskList::RemoveTask Tests
// ************************************************
TEST_F(TTaskList, RemoveTask_RemoveOneTask_TaskCountIsOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add two tasks
	newList.AddTask("test1");
	newList.AddTask("test2");

	// Remove one task
	newList.RemoveTask(1);

	ASSERT_EQ(1, newList.GetTaskCount());
}

TEST_F(TTaskList, RemoveTask_RemoveFourTasks_TaskCountIsFour)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add eight tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");
	newList.AddTask("test4");
	newList.AddTask("test5");
	newList.AddTask("test6");
	newList.AddTask("test7");
	newList.AddTask("test8");

	// Remove four tasks
	newList.RemoveTask(1);
	newList.RemoveTask(2);
	newList.RemoveTask(3);
	newList.RemoveTask(4);

	ASSERT_EQ(4, newList.GetTaskCount());
}

TEST_F(TTaskList, RemoveTask_RemoveTaskFirstIndex_CorrectTaskIsReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add three tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");

	// Remove first task
	std::string taskStr = "";
	newList.RemoveTask(1, taskStr);

	ASSERT_EQ("test1", taskStr);
}

TEST_F(TTaskList, RemoveTask_RemoveTaskLastIndex_CorrectTaskIsReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("./", "");

	// Add three tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");

	// Remove last task
	std::string taskStr = "";
	newList.RemoveTask(newList.GetTaskCount(), taskStr);

	ASSERT_EQ("test3", taskStr);
}

// ************************************************
//  TTaskList::GetPath Tests
// ************************************************
TEST_F(TTaskList, GetPath_NormalCall_PathReturned)
{
	const std::string path = "C:\\temp.txt";

	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(path, "");
	ASSERT_EQ(path, newList.GetPath());
}

/*TEST_F(TTaskList, GetPath_NoExtension_BlankReturn)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("C:\\temp", "");

	ASSERT_EQ(newList.GetPath(), "");
}

TEST_F(TTaskList, GetPath_NoPathPassed_BlankReturn)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init("", "");

	ASSERT_EQ(newList.GetPath(), "");
}*/

#endif
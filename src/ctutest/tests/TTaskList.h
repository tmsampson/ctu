#ifndef T_TASK_LIST_H_
#define T_TASK_LIST_H_

#include "TaskList.h"
#include "Common.h"
#include <gtest/gtest.h>
#include <fstream>

class TTaskList : public ::testing::Test { };
static const std::string VALID_PATH                          = "ctutest_resources/temp";
static const std::string INVALID_PATH                        = "";
static const std::string TASK_LIST_EMPTY                     = "ctutest_resources/tl-empty";
static const std::string TASK_LIST_SINGLE_TASK               = "ctutest_resources/tl-single";
static const std::string TASK_LIST_SINGLE_TASK_NOBULLET      = "ctutest_resources/tl-single-nobullet";
static const std::string TASK_LIST_SINGLE_TASK_DOUBLE_BULLET = "ctutest_resources/tl-single-double-bullet";
static const std::string TASK_LIST_MULTIPLE_TASKS            = "ctutest_resources/tl-multiple";
static const std::string TASK_LIST_MULTIPLE_TASKS_MSB        = "ctutest_resources/tl-multiple-missing-single-bullet";

// ************************************************
//  TTaskList::Init Tests
// ************************************************
TEST_F(TTaskList, Init_ValidPathPassed_ReturnsTrue)
{
	// Create a new list and initialise it
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TEMP_FILE, ""));
}

TEST_F(TTaskList, Init_InvalidPathPassed_ReturnsFalse)
{
	// Create a new list and initialise it
	CTU::TaskList newList;

	ASSERT_FALSE(newList.Init(INVALID_PATH, ""));
}

// ************************************************
//  TTaskList::Parse Tests
// ************************************************
TEST_F(TTaskList, Parse_Empty_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_EMPTY, ""));
	ASSERT_TRUE(newList.Parse());
}

TEST_F(TTaskList, Parse_SingleTask_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_SINGLE_TASK, "> "));
	ASSERT_TRUE(newList.Parse());
	ASSERT_EQ(1, newList.GetTaskCount());
}

TEST_F(TTaskList, Parse_SingleTaskNoBullet_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_SINGLE_TASK_NOBULLET, ""));
	ASSERT_TRUE(newList.Parse());
	ASSERT_EQ(1, newList.GetTaskCount());
}

TEST_F(TTaskList, Parse_SingleTaskMissingBullet_ReturnsFalse)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_SINGLE_TASK_NOBULLET, "> "));
	ASSERT_FALSE(newList.Parse());
	ASSERT_EQ(0, newList.GetTaskCount());
}

TEST_F(TTaskList, Parse_SingleTaskParseBulletRaw_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_SINGLE_TASK, ""));
	ASSERT_TRUE(newList.Parse());
	ASSERT_EQ(1, newList.GetTaskCount());

	// Bullet point parsed as raw text?
	static const std::string SINGLE_TASK_CONTENTS = "> Single Task";
	ASSERT_EQ(SINGLE_TASK_CONTENTS, newList.GetAllTasks()[0].RawText);
	ASSERT_EQ(SINGLE_TASK_CONTENTS, newList.GetAllTasks()[0].Contents);
}

TEST_F(TTaskList, Parse_SingleTaskDoubleBullet_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_SINGLE_TASK_DOUBLE_BULLET, "> "));
	ASSERT_TRUE(newList.Parse());
	ASSERT_EQ(1, newList.GetTaskCount());

	// Second bullet point parsed as raw text?
	static const std::string SINGLE_TASK_CONTENTS = "> Single Task";
	ASSERT_EQ(SINGLE_TASK_CONTENTS, newList.GetAllTasks()[0].RawText);
	ASSERT_EQ(SINGLE_TASK_CONTENTS, newList.GetAllTasks()[0].Contents);
}

TEST_F(TTaskList, Parse_MultipleTasks_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_MULTIPLE_TASKS, "> "));
	ASSERT_TRUE(newList.Parse());
	ASSERT_EQ(2, newList.GetTaskCount());
}

TEST_F(TTaskList, Parse_MultipleTasksSingleMissingBullet_ReturnsTrue)
{
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(TASK_LIST_MULTIPLE_TASKS_MSB, "> "));
	ASSERT_FALSE(newList.Parse());
	ASSERT_EQ(0, newList.GetTaskCount());
}

// ************************************************
//  TTaskList::Save Tests
// ************************************************
TEST_F(TTaskList, Save_NormalCall_ReturnsTrue)
{
	// Create a new list and initialise it
	CTU::TaskList newList;

	ASSERT_TRUE(newList.Init(VALID_PATH, ""));
}

// ************************************************
//  TTaskList::AddTask Tests
// ************************************************
TEST_F(TTaskList, AddTask_NoTasksAdded_TaskCountIsZero)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	ASSERT_EQ(0, newList.GetTaskCount());
}

TEST_F(TTaskList, AddTask_AddOneTask_TaskCountIsOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add one task
	newList.AddTask("test");

	ASSERT_EQ(1, newList.GetTaskCount());
}

TEST_F(TTaskList, AddTask_AddFourTasks_TaskCountIsFour)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

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
	newList.Init(VALID_PATH, "");

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
	newList.Init(VALID_PATH, "");

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
	newList.Init(VALID_PATH, "");

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
	newList.Init(VALID_PATH, "");

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
//  TTaskList::Clear Tests
// ************************************************
TEST_F(TTaskList, Clear_OneTask_OneTaskIsCleared)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add one task
	newList.AddTask("test1");

	// Clear the list
	newList.Clear();

	ASSERT_EQ(0, newList.GetTaskCount());
}

TEST_F(TTaskList, Clear_MultipleTasks_AllTasksCleared)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add five tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");
	newList.AddTask("test4");
	newList.AddTask("test5");

	// Clear the list
	newList.Clear();
	
	ASSERT_EQ(0, newList.GetTaskCount());
}

TEST_F(TTaskList, Clear_NoTasks_ListRemainsUnchanged)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Clear the list
	newList.Clear();

	ASSERT_EQ(0, newList.GetTaskCount());
}

// ************************************************
//  TTaskList::GetPath Tests
// ************************************************
TEST_F(TTaskList, GetPath_InitialisedWithValidPath_PathReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	ASSERT_EQ(VALID_PATH, newList.GetPath());
}

TEST_F(TTaskList, GetPath_InitialisedWithInvalidPath_BlankStringReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(INVALID_PATH, "");

	ASSERT_EQ("", newList.GetPath());
}

// ************************************************
//  TTaskList::GetTaskCount Tests
// ************************************************
TEST_F(TTaskList, GetTaskCount_OneTask_ReturnsCountOfOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add one task
	newList.AddTask("test1");

	ASSERT_EQ(1, newList.GetTaskCount());
}

TEST_F(TTaskList, GetTaskCount_FiveTasks_ReturnsCountOfFive)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add five tasks
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");
	newList.AddTask("test4");
	newList.AddTask("test5");
	
	ASSERT_EQ(5, newList.GetTaskCount());
}

TEST_F(TTaskList, GetTaskCount_NoTasks_ReturnsCountOfOne)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	ASSERT_EQ(0, newList.GetTaskCount());
}

// ************************************************
//  TTaskList::GetAllTasks Tests
// ************************************************
TEST_F(TTaskList, GetAllTasks_NoTasks_EmptyVectorReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Get all the tasks
	std::vector<CTU::Task> tasks = newList.GetAllTasks();

	ASSERT_EQ(0, tasks.size());
}

TEST_F(TTaskList, GetAllTasks_OneTask_VectorOfSizeOneReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add one task
	newList.AddTask("test1");

	// Get all the tasks
	std::vector<CTU::Task> tasks = newList.GetAllTasks();

	ASSERT_EQ(1, tasks.size());
}

TEST_F(TTaskList, GetAllTasks_FiveTasks_VectorOfSizeFiveReturned)
{
	// Create a new list and initialise it
	CTU::TaskList newList;
	newList.Init(VALID_PATH, "");

	// Add one task
	newList.AddTask("test1");
	newList.AddTask("test2");
	newList.AddTask("test3");
	newList.AddTask("test4");
	newList.AddTask("test5");

	// Get all the tasks
	std::vector<CTU::Task> tasks = newList.GetAllTasks();

	ASSERT_EQ(5, tasks.size());
}

#endif
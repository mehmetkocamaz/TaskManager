#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <stdexcept>
#include "Task.h"
#define BLUE 1
#define GREEN 2
#define LIGHT_BLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define TURKUAZ 11
using namespace std;

class TaskManager {
public:

	void Execute(TaskManager& tasky) {
		FillTheVector();
		Instructions();
		int choice = 0;
		string taskName, dueDate;
		int taskIndex;
		while (4 != choice && 5 != choice) {
			SetConsoleTextColor(RED);
			cout << "Please enter your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
				SetConsoleTextColor(RED);
				cout << "Enter task name: ";
				SetConsoleTextColor(GREEN);
				//cin >> taskName;
				cin.ignore();
				getline(cin, taskName);
				SetConsoleTextColor(RED);
				cout << "Enter due date: ";
				//cin >> dueDate;
				//cin.ignore();
				getline(cin, dueDate);
				tasky.AddTask(Task(taskName, dueDate));
				break;
			case 2:
				tasky.LoadTasksFromFile(choice);
				break;
			case 3:
				tasky.LoadTasksFromFile(choice);
				SetConsoleTextColor(RED);
				cout << "Enter the task number to mark as completed: ";
				//getline(cin, taskIndex);
				if (cin >> taskIndex)
				{
					tasky.MarkCompleted(taskIndex - 1); // TRY - CATCH KULLANMAN GEREKLÝ (VECTOR BOUNDARY) 
				}
				else
				{
					SetConsoleTextColor(YELLOW);
					cout << "Invalid Choise! Program will terminate. \n";
					choice = 5;
				}
				break;
			case 4:
				SaveTasksFromFile(m_Task[0]);
				break;
			case 5:
				break;
			default:
				SetConsoleTextColor(YELLOW);
				cout << "Invalid Choise! \n";
				choice = 5;
				break;
			}
			SetConsoleTextColor(WHITE);
		}
	}

	void Instructions() {
		SetConsoleTextColor(GREEN);
		cout << "Welcome to the Task Manager! \n" << endl;
		SetConsoleTextColor(RED);
		cout << "1. ";
		SetConsoleTextColor(GREEN);
		cout << "Add Task" << endl;
		SetConsoleTextColor(RED);
		cout << "2. ";
		SetConsoleTextColor(GREEN);
		cout << "View Tasks" << endl;
		SetConsoleTextColor(RED);
		cout << "3. ";
		SetConsoleTextColor(GREEN);
		cout << "Mark Task as Completed" << endl;
		SetConsoleTextColor(RED);
		cout << "4. ";
		SetConsoleTextColor(GREEN);
		cout << "Save and Exit"<< endl;
		SetConsoleTextColor(WHITE);
	}

	void FillTheVector() {
		int counter = 0;
		ifstream inputFile("Tasky.txt");
		if (!inputFile.is_open()) {
			cerr << "Error opening file Tasky.txt" << endl;
		}
		string name, dueDate, completionStatus, newLine;

		while (getline(inputFile, name)) {
			getline(inputFile, dueDate);
			getline(inputFile, completionStatus);
			getline(inputFile, newLine);
			bool isCompleted = (completionStatus == "Completed");
			m_Task.push_back(Task(name, dueDate, isCompleted));
		}
	}

	void AddTask(const Task& task) {
		m_Task.push_back(task); 
		ofstream outputFile("Tasky.txt", ios::app);
		if (outputFile.is_open())
		{
			outputFile << task.GetName() << "\n" << task.GetDueDate() << "\n" << (task.GetCompletionStatus() ? "Completed" : "Not Completed") << "\n" << "-------------------------------" << endl;
			SetConsoleTextColor(GREEN);
			cout << "Task added!\n" << endl;
			outputFile.close();
		}
		else
		{
			cout << "Unable to open file." << endl;
		}
	}
	void MarkCompleted(int taskIndex) { // TRY - CATCH KULLANMAN GEREKLÝ (VECTOR BOUNDARY) 
		if (m_Task.size() < taskIndex || taskIndex < 0)
		{
			SetConsoleTextColor(PURPLE);
			cerr << "There is not task number " << taskIndex + 1 << " to complete" << endl;
		}
		else
		{
			if (m_Task[taskIndex].SetCompletionStatus(true))
			{
				SetConsoleTextColor(GREEN);
				cout << "Task marked as completed!\n" << endl;
			}
			else
			{
				SetConsoleTextColor(YELLOW);
				cout << "Task could not marked as completed!\n" << endl;
			}
		}
		/*
		try
		{
			if (m_Task[taskIndex].SetCompletionStatus(true))
			{
				SetConsoleTextColor(GREEN);
				cout << "Task marked as completed!\n" << endl;
			}
			else
			{
				SetConsoleTextColor(YELLOW);
				cout << "Task could not marked as completed!\n" << endl;
			}
		}
		catch (out_of_range& ex)
		{
			SetConsoleTextColor(PURPLE);
			cerr << "An exception occured: " << ex.what() << endl;
		}*/
		
	}
	void LoadTasksFromFile(int choice) {
		int counter = 0;
		ifstream inputFile("Tasky.txt");
		if (!inputFile.is_open()) {
			cerr << "Error opening file Tasky.txt" << endl;
		}
		string name, dueDate, completionStatus,newLine;

		while (getline(inputFile,name)) {
			getline(inputFile, dueDate);
			getline(inputFile, completionStatus);
			getline(inputFile, newLine); 
			if (2 == choice) {
				SetConsoleTextColor(RED);
				cout << counter + 1;
				SetConsoleTextColor(WHITE);
				cout << "[" << (m_Task[counter].GetCompletionStatus() ? "+" : "-") << "]";
				SetConsoleTextColor(GREEN);
				cout << name;
				SetConsoleTextColor(WHITE);
				cout << " Due Date: ";
				SetConsoleTextColor(RED);
				cout << dueDate;
				cout << " " << endl;
			}
			counter++;
		}
		if (counter == 0) {
			SetConsoleTextColor(TURKUAZ);
			cout << "There is no task to show." << endl;
		}
		inputFile.close();
	}
	void SaveTasksFromFile(const Task& task) {
		int counter = 0;
		ofstream outputFile("Tasky.txt");
		if (outputFile.is_open())
		{
			while (m_Task.size() > counter) {
			outputFile << m_Task[counter].GetName() << "\n" << m_Task[counter].GetDueDate() << "\n" << (m_Task[counter].GetCompletionStatus() ? "Completed" : "Not Completed") << "\n" << "-------------------------------" << endl;
			counter++;
			}
			SetConsoleTextColor(YELLOW);
			cout << "All tasks saved!\n" << endl;
			outputFile.close();
		}
		else
		{
			cout << "Unable to open file." << endl;
		}
	}

	// Constructors
	TaskManager() : m_File("Tasky.txt") {
		m_Task = {};
	}

private:
	void SetConsoleTextColor(int color) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}
	// MEMBERS
	fstream m_File;
	vector<Task> m_Task;
};

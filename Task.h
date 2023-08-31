#include <iostream>
#include <string>
using namespace std;

static class Task {
public:
	// Getters - Setters
	bool GetCompletionStatus() const {
		return m_CompletionStatus;
	}
	bool SetCompletionStatus(bool completion) {
		if (m_CompletionStatus = completion)
		{
			return true;
		}
		return false;
	}
	string GetDueDate() const {
		return m_DueDate;
	}
	string GetName() const {
		return m_Name;
	}
	// Constructors
	Task(string name, string dueDate, bool completionStatus) : m_Name(name), m_DueDate(dueDate), m_CompletionStatus(completionStatus) {

	}
	Task(string name, string dueDate) : m_Name(name), m_DueDate(dueDate), m_CompletionStatus(false) {

	}

private:
	//MEMBERS
	string m_Name;
	string m_DueDate;
	bool m_CompletionStatus;
};
#ifndef PROJECT_STRUCTURE
#define PROJECT_STRUCTURE

#include <iostream>
#include "date/date.h"

using namespace std;

namespace psl 
{

class Project {
public:
	string name;
	string description;
	string begin_date;
	string due_date;
	int total_tasks;
	string total_progress;
	vector< string > participants;
	vector< string > departments;
	bool overdue;
	
	Project(string name,
		string description,
		string begin_date,
		string due_date,
		int total_tasks,
		string total_progress,
		vector< string > participants,
		vector< string > departments,
		bool overdue): name(name), description(description), begin_date(begin_date), due_date(due_date), total_tasks(total_tasks), total_progress(total_progress), participants(participants), departments(departments), overdue(overdue) {}
};
	
}

#endif


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
		vector< string > departments,
		vector< string > participants): name(name), description(description), begin_date(begin_date), due_date(due_date), total_tasks(total_tasks), total_progress(total_progress), participants(participants), departments(departments) {
		/*
		date::year_month_day currentDate = date::year_month_day(date::floor<date::days>(std::chrono::system_clock::now()));

		date::year_month_day begin = date::year(date::parse("%Y-%m-%d", begin_date)) / date::month(date::parse("%Y-%m-%d", begin_date)) / date::day(date::parse("%Y-%m-%d", begin_date));
		date::year_month_day due = date::year(date::parse("%Y-%m-%d", due_date)) / date::month(date::parse("%Y-%m-%d", due_date)) / date::day(date::parse("%Y-%m-%d", due_date));

		return (begin > due || currentDate > due);
		*/
	}
};
	
}

#endif


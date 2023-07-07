#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <OpenXLSX/OpenXLSX.hpp>
#include "date/date.h"
#include "projectStructure.hpp"

using namespace std;


/**********************************Basic file**********************************

Name: Projects
Type: xlsx
|Project Name|Project Description|Begin Date|Due Date|Total Tasks|Total Progress|Participants|Departments|Overdue|Total_projects|#|

******************************************************************************/

#define update(num, wks) do { num += 1; c = wks.cell("A" + to_string(num)); } while (c.value() != ""); wks.cell("K1").value() = num - 2;

void auto_update() {
	OpenXLSX::XLDocument doc;
	doc.open("Projects.xlsx");
	
	int num = 0;
	auto wks = doc.workbook().worksheet("Projects");
	OpenXLSX::XLCell c;
	
	update(num, wks);
	doc.save();
}


string cells[10] = {"Project Name", 
	           "Project Description" ,
		   "Begin Date" ,
		   "Due Date" ,
		   "Total Tasks" ,
		   "Total Progress" ,
		   "Participants" , 
		   "Departments",
		   "Overdue",
		   "Total_Projects: "};
			    
string n[11] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "k1"};

void basic_if_not_exists() {
	ifstream file("Projects.xlsx");
	if (!file) {
		OpenXLSX::XLDocument doc;
		doc.create("Projects.xlsx");
		auto wks = doc.workbook().worksheet("Sheet1");
		wks.setName("Projects");

		for (int i = 0; i < 10; i++) {
		    std::string name = n[i] + "1";
		    auto c = wks.cell(name);
		    c.value() = cells[i];
		}	       

	doc.save();
	doc.close();
		    
	cout << "\nCREATED PROJECTS FILE: Projects.xlsx " << endl;
	}
}

void new_project(psl::Project* p) {
	OpenXLSX::XLDocument doc;
	doc.open("Projects.xlsx");
	
	int num = 0;
	auto wks = doc.workbook().worksheet("Projects");
	OpenXLSX::XLCell c;
	
	update(num, wks);


	c.value() = p->name;

	c = wks.cell("B" + to_string(num));
	c.value() = p->description;

	c = wks.cell("C" + to_string(num));
	c.value() = p->begin_date;

	c = wks.cell("D" + to_string(num));
	c.value() = p->due_date;

	c = wks.cell("E" + to_string(num));
	c.value() = p->total_tasks;

	c = wks.cell("F" + to_string(num));
	c.value() = p->total_tasks;

	c = wks.cell("G" + to_string(num));
	c.value() = p->total_progress;
	
	c = wks.cell("H" + to_string(num));
	c.value() = p->overdue;

	string participantsString;
	for (const auto& participant : p->participants) {
	participantsString += participant + ", ";
	}
	participantsString = participantsString.substr(0, participantsString.length() - 2); // Remove the extra comma and space
	c.value() = participantsString;
	c = wks.cell("I" + to_string(num));

	string departmentsString;
	for (const auto& department : p->departments) {
	departmentsString += department + ", ";
	}
	departmentsString = departmentsString.substr(0, departmentsString.length() - 2); // Remove the extra comma and space
	c.value() = departmentsString;
	c = wks.cell("J" + to_string(num));
	// Continue setting values for other cells

	doc.save();
	doc.close();
}

vector< psl::Project > list() {
	vector < psl::Project > project_list;
	OpenXLSX::XLDocument doc;
	doc.open("Projects.xlsx");
	
	auto wks = doc.workbook().worksheet("Projects");
	OpenXLSX::XLCell c;
	num = wks.cell("K1").value();
	
	for (int i = 2; i <= num; i++) {
		for (int e; e <= sizeof(n); e++) {
			string name = n[e] + to_string(i);
			
		} 	
	}
}

#endif

#include <iostream>
#include <filesystem>
#include <string>
#include <ctime>
#include <vector>
#include "Database_Connection.hpp"
#include "projectStructure.hpp"
#include <csignal>
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#include <Lmcons.h>
#endif

using namespace std;


string getCurrentUsername() {
	string username;

#ifdef _WIN32
    char winUsername[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserNameA(winUsername, &size)) {
        username = winUsername;
    }
#else
    char* linuxUsername = getlogin();
    if (linuxUsername) {
        username = linuxUsername;
    }
#endif

    return username;
}




void write_to_data_file(const psl::Project& data, const std::string& filename = "Projects.pdat") {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "\n:::ERROR FROM MAIN.CPP line " << __LINE__ << ": FAILED TO OPEN PROJECTS FILE " << filename << std::endl;
        return;
    }

    // Write the data to the file
    file.write(reinterpret_cast<const char*>(&data), sizeof(psl::Project));
}


void log(const std::string& message, const std::string& filename="Plog.log") {
	std::ofstream logFile(filename, std::ios::app | std::ios::out);
	if (!logFile) {
		cerr << "\n:::ERROR FROM MAIN.CPP line " << __LINE__ << ": FAILED TO OPEN PROJECT'S LOG FILE " << filename << std::endl;
		return;
	}

	// Get the current time
	std::time_t currentTime = std::time(nullptr);
	std::string timestamp = std::ctime(&currentTime);

	string username = getCurrentUsername();

	// Write the log message with a timestamp
	logFile << "[" << timestamp.substr(0, timestamp.length() - 1) << " User: " << username << "] " << message << std::endl;
}

volatile bool programExited = false;

// Signal handler function for Ctrl+C
void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "LOGGING OUT ..." << std::endl;
	log("Logged out");
	exit(-1);
    }
}


void new_project_() {
	string name, description, date_begin, date_due, line;
	vector< string > departments, participants;
	int total;
	
	cout << "\n:::TO CREATE A PROJECT PLEASE ENTER THE FOLLOWING INPUTS (type '>' when you have finished the input): "
	     << "\n::::::PROJECT NAME <"; getline(cin, name, '>');
	cout << "\n::::::PROJECT DESCRIPTION <"; getline(cin, description, '>');
	cout << "\n::::::PROJECT'S BEGIN DATE <"; getline(cin, date_begin, '>');
	cout << "\n::::::PROJECT'S DUE DATE <"; getline(cin, date_due, '>');
	cout << "\n::::::PROJECT'S DEPARTMENTS (type enter after each department has been entered. type 'done' when you are finished.)\n<";
	string message = "Created new project: name: <" + name + "> description: <" + description + "> beginDate: <" + date_begin + "> endDate: <" + date_due + "> departments: <";
	while (getline(cin, line)) {
		message = message + line + ", ";
		if (line == "done") {cout << ">"; break;}
		departments.push_back(line);
	}
	
	message += "> participants: <";
	
	line = "";
	
	cout << "\n::::::PROJECT'S PARTICIPANTS (type enter after each department has been entered. type 'done' when you are finished.)\n<";
	while (getline(cin, line)) {
		message = message + line + ", ";
		if (line == "done") { cout << ">"; break; }
	  	departments.push_back(line);
	}
	
	message += ">";
	 
	string new_progress = "0/" + to_string(total);
	psl::Project p (name, description, date_begin, date_due, total, new_progress, departments, participants);
	message.erase(std::remove(message.begin(), message.end(), '\n'), message.cend());
	size_t found = message.find("done, ");
    	while (found != std::string::npos) {
        	message.erase(found, 6); // 6 is the length of "done, "
        	found = message.find("done, ");
        }
        
	write_to_data_file(p); 
	cout << message;
	log(message);
}

int main() {
    	std::signal(SIGINT, signalHandler);
    	if (!programExited) {log("Logged in");}
	while (!programExited) {
		string command;
		cout << "\n>>> ";
		getline(cin, command);
		
		if ((command == "exit") || (command ==  "quit")) { exit(0); } else
		if ((command == "new") || (command ==  "create")) { new_project_(); } else
		
		{ continue; }
	}
	
	
	vector< string > e = {"Arian", "Arash"};
	vector< string > l = {"cooking", "cleaning", "washing", "watching movies", "trading"};
	psl::Project p("Practice Excel", "Transferring data to excel", "2023-07-08", "2023-07-015", 32, "17/32", e, l);
	auto_update();
	return 0;
}


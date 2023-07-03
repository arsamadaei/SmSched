#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <iostream>
#include "sqlite3/sqlite3.h"
using namespace std;

// Connect to database
void connect() {
	sqlite3* db;
	int connectionResult;
	connectionResult = sqlite3_open("svdat.db" , &db);

	if (connectionResult != SQLITE_OK) {
		cout << "\n*** CONNECTION UNSUCCESSFUL TO DATABASE: " << "svdat.db" << endl;
	} else { cout << "\n*** CONNECTION ESTABLISHED TO DATABASE: " << "svdat.db" << endl; }
}

#endif

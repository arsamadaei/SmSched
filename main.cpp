#include <iostream>
#include <vector>
#include "Database_Connection.hpp"
#include "projectStructure.hpp"

using namespace std;

int main() {
	vector< string > e = {"person", "person1", "person2", "person3"};
	vector< string > l = {"loob", "foo", "bar", "dymph", "node"};
	psl::Project p("name", "description", "begin_date", "due_date", 10, "3/10", e, l, 1);
	basic_if_not_exists();
	auto_update();
	return 0;
}


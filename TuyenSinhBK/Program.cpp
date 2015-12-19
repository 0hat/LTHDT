#include <iostream>
#include <string>
#include "ReadData.h"
#include "StudentProfile.h"
#include "sqlite3.h"

using namespace std;


int main() {
	vector<StudentProfile> myStudentList;
	ReadData myReader(29);
	myReader.readAndCreateStudentProfileList(myStudentList);
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_open("29.db", &db);
	if (rc) {
		cout << sqlite3_errmsg(db) << endl;
		exit(EXIT_FAILURE);
	}
	// create table
	char* createtable = R"dl(CREATE TABLE NVXT(sbd varchar(9), nvso int, manv varchar(4), diemxt double precision);)dl";
	sqlite3_exec(db, createtable, 0, 0, 0);
	for each (StudentProfile var in myStudentList)
	{
		var.exportToDB(db);
	}
	sqlite3_close(db);
	system("pause");
	return 0;
}
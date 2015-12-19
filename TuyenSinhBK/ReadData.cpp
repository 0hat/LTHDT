#include "ReadData.h"
#include <string>



ReadData::ReadData(int id)
{
	studentID = id;
	StdDB.open("csdl-bk.csv");
	AspDB.open("dangkynv-bk.csv");
	if (!StdDB.good() || !AspDB.good())
	{
		std::cout << "input files do not found \nPlease check for csdl-bk.csv and dangkynv-bk.csv\n" 
				  << "Make sure that the 2 files locate at the same folder with TuyenSinhBK.exe file" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}


void ReadData::skipSomeLines(std::fstream& fs) {
	int linesToSkip = studentID * 100;
	std::string tmp;
	for (int count = 1; count <= linesToSkip; count++) {
		getline(fs, tmp);
	}
}

void ReadData::readAndCreateStudentProfileList(std::vector<StudentProfile>& StudentList)
{
	std::string StdTmp;
	std::string AspTmp;
	skipSomeLines(StdDB);
	skipSomeLines(AspDB);
	for (size_t i = 1; i <= 100; i++) {
		getline(StdDB, StdTmp);
		getline(AspDB, AspTmp);
		StudentProfile tempStd(StdTmp, AspTmp); // create new temporary Student Profile
		StudentList.push_back(tempStd);			// push temporary Student Profile to containing vector
	}
}


ReadData::~ReadData()
{
}
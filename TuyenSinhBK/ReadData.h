#pragma once
#include <iostream>
#include <fstream>
#include "StudentProfile.h"

class ReadData
{
private:
	std::fstream StdDB;
	std::fstream AspDB;
	int studentID; // ID sinh viên trong danh sách lớp, từ đó xác định dữ liệu cần xử lý
				   // sinh viên có số thứ tự là ID sẽ xử lý hồ sơ học sinh từ ID * 100 tới (ID + 1) * 100 - 1

public:
	void skipSomeLines(std::fstream&);
	void readAndCreateStudentProfileList(std::vector<StudentProfile>&);
	/*void readStdDB();
	void readAspDB();*/
	ReadData(int);
	~ReadData();
};
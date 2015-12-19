#pragma once
#include <iostream>
#include <string>
#include "sqlite3.h"

class Aspiration
{
	friend class StudentProfile;
private:
	
	std::string sbd;
	int nvSo;
	std::string maNguyenVong;
	float diemXetTuyen;
public:
	
	Aspiration(std::string, int, std::string, float);
	Aspiration();
	~Aspiration();
};
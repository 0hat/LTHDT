#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "sqlite3.h"
#include "Aspiration.h"
class StudentProfile
{
private:
	//chỉ lấy những thông tin cần thiết cho việc xử lý thông tin về nguyện vọng
	//họ tên, ngày sinh bỏ qua vì không cần thiết.

	std::string soBaoDanh;
	std::string khuVuc; // KV1, KV2, KV2-NT, KV3
	std::string doiTuong; // Khong, NDT1, NDT2
	std::string uuTien; // Khong, UT
	float diemThi[13]; //
	std::vector<Aspiration> AspirationList; //contain aspirations of a student
	
public:
	
	void exportToDB(sqlite3*);
	float diemUuTien();
	float pointCalculating(std::string, std::vector<std::string>);
	Aspiration makeAnAspiration(std::string manv, std::string subjectList);
	float getMark(std::string);
	void removeDoubleQoutationMark(std::string&);
	void splitStdLine(std::string, std::vector<std::string>&);
	void splitAspLine(std::string, std::vector<std::string>&);
	StudentProfile();
	StudentProfile(std::string, std::string);
	~StudentProfile();
};
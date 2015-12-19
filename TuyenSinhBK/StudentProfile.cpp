#include "StudentProfile.h"
#include <vector>


StudentProfile::StudentProfile()
{
}


StudentProfile::~StudentProfile()
{
}



StudentProfile::StudentProfile(std::string StdInfo, std::string AspInfo)
{	
	std::vector<std::string> StdVector;
	std::vector<std::string> AspVector;
	splitStdLine(StdInfo, StdVector);
	splitAspLine(AspInfo, AspVector);
	for (size_t i = 0; i < StdVector.size(); i++) {
		removeDoubleQoutationMark(StdVector[i]);
	}
	
	for (size_t i = 0; i < AspVector.size(); i++) {
		removeDoubleQoutationMark(AspVector[i]);
	}

	soBaoDanh = StdVector[0];
	khuVuc = StdVector[3];
	doiTuong = StdVector[4];
	uuTien = StdVector[5];
	for (size_t i = 6; i < 19; i++) {
		diemThi[i-6] = (StdVector[i] == "NA") ? 0 : std::stof(StdVector[i]);
	}
	for (size_t i = 1; i < AspVector.size(); i += 2) {
		Aspiration tempAsp = makeAnAspiration(AspVector[i], AspVector[i + 1]);
		AspirationList.push_back(tempAsp);
	}
}





void StudentProfile::splitStdLine(std::string str, std::vector<std::string>& arr) {
	std::string tempString = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (str[i] != ',') tempString += str[i];
		else {
			arr.push_back(tempString);
			tempString = "";
		}
		if (i == str.length() - 1) {
			arr.push_back(tempString);
		}
	}
}


void StudentProfile::splitAspLine(std::string str, std::vector<std::string>& arr) {
	std::string tempString = "";
	for (size_t i = 0; i < str.length(); i++) {
		if (!(str[i] == ',' && str[i - 1] == '\"')) tempString += str[i];
		else {
			arr.push_back(tempString);
			tempString = "";
		}
		if (str[i] == ',' && str[i + 1] == 'N') break; // detect the first "NA" in the line and stop getting info from this line
		if (i == str.length() - 1) {
			arr.push_back(tempString);
		}
	}
}





void StudentProfile::exportToDB(sqlite3* mydb)
{
	for each (Aspiration var in AspirationList)
	{
		std::string sqlstring = "INSERT INTO NVXT VALUES (\'" + soBaoDanh + "\'" + ", " + std::to_string(var.nvSo) + ", " + "\'" + var.maNguyenVong + "\'" + ", " + std::to_string(var.diemXetTuyen) + ");";
		const char* sql = sqlstring.c_str();
		sqlite3_exec(mydb, sql, 0, 0, 0);
	}
}


float StudentProfile::diemUuTien()
{
	float bonusPoint = 0;
	bonusPoint += (khuVuc == "KV1") ? 1.5f : ((khuVuc == "KV2") ? 0.5f : (khuVuc == "KV2-NT") ? 1.0f : 0.0f);
	bonusPoint += (doiTuong == "NDT1") ? 2.0f : ((doiTuong == "NDT2") ? 1.0f : 0.0f);
	bonusPoint /= 3;
	bonusPoint += (uuTien == "Khong") ? 0.0f : 1.0f;
	return bonusPoint;
}

float StudentProfile::pointCalculating(std::string manv, std::vector<std::string> sbjvector)
{
	float diemXT;
	float subjectPoint = 0;
	
	if (sbjvector[3] == "1") {
		std::string mainsubject;
		if (manv == "TA1" || manv == "TA2") {
			mainsubject = "Anh";
		} else{
			mainsubject = "Toan";
		}
		for (size_t i = 0; i < 3; i++) {
			float sbjpoint = getMark(sbjvector[i]);
			if (sbjvector[i] == mainsubject) subjectPoint += 2 * sbjpoint;
			else subjectPoint += sbjpoint;
		}
		subjectPoint /= 4;
		diemXT = subjectPoint + diemUuTien();
	}
	else {
		for (size_t i = 0; i < 3; i++) {
			float sbjpoint = getMark(sbjvector[i]);
			subjectPoint += sbjpoint;
		}
		subjectPoint /= 3;
		diemXT = subjectPoint + diemUuTien();
	}
	return diemXT;
}

Aspiration StudentProfile::makeAnAspiration(std::string manv, std::string subjectList)
{
	std::vector<std::string> sbjlist;
	std::string tempString = "";
	int nvso = AspirationList.size() + 1;
	float diemxt;
	for (size_t i = 0; i < subjectList.length(); i++) {
		if (subjectList[i] != ',') tempString += subjectList[i];
		else {
			sbjlist.push_back(tempString);
		}
		if (i == subjectList.length() - 1) {
			sbjlist.push_back(tempString);
		}
		
	}
	diemxt = pointCalculating(manv, sbjlist);
	Aspiration tempAsp(soBaoDanh, nvso, manv, diemxt);
	return tempAsp;
}





float StudentProfile::getMark(std::string subjectName)
{
	std::map<std::string, int> MyMap;
	MyMap["Toan"] = 0;
	MyMap["Van"] = 1;
	MyMap["Ly"] = 2;
	MyMap["Hoa"] = 3;
	MyMap["Sinh"] = 4;
	MyMap["Su"] = 5;
	MyMap["Dia"] = 6;
	MyMap["Anh"] = 7;
	MyMap["Nga"] = 8;
	MyMap["Phap"] = 9;
	MyMap["Trung"] = 10;
	MyMap["Duc"] = 11;
	MyMap["Nhat"] = 12;
	return diemThi[MyMap[subjectName]];
}


void StudentProfile::removeDoubleQoutationMark(std::string& str) {
	if (str[0] == '\"' && str[str.length() - 1] == '\"') {
		std::string newstr = "";
		for (size_t i = 1; i < str.length() - 1; i++) newstr += str[i];
		str = newstr;
	}
}
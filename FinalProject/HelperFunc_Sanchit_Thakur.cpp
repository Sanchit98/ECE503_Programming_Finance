#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<sstream>
#include<time.h>
#include<iomanip>
using namespace std;
#include "HelperFunc.h"

string HelperFunc::convertToString(double d) const
{
	stringstream ss;
	ss << fixed << setprecision(2) << d; 
	return ss.str();
}

string HelperFunc::convert2String(double d) const
{
	stringstream ss;
	ss << d;
	return ss.str();
}

string HelperFunc::convertTimeToString(long d) const
{
	stringstream ss;
	ss << d;
	return ss.str();
}

HelperFunc::HelperFunc()
{
}

string HelperFunc::getTime() const
{
	time_t now = time(0);
	tm *loc_time = localtime(&now); 
	//Formatting the time
	string time = convert2String(loc_time->tm_hour) + ":" +
		convert2String(loc_time->tm_min) + ":" + convert2String(loc_time->tm_sec);
	return time;
}

time_t HelperFunc::getTimeSec() const
{
	time_t seconds = time(0);
	return seconds;
}

string HelperFunc::getDate() const
{
	time_t now = time(0);
	tm *loc_time = localtime(&now); 
	//Formatting the date
	string time = convert2String(1 + loc_time->tm_mon) + "/" +
		convert2String(loc_time->tm_mday) + "/" + convert2String(1900 + loc_time->tm_year);
	return time;
}

void HelperFunc::cleanFile(char * file)
{
	ofstream ofs;
	ofs.open(file);
	if (ofs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return;
	}
	else {
		ofs << ""; 
		ofs.close();
	}
}

int HelperFunc::getLineNum(char * file) const
{
	//To get the number of lines in a file
	int num = 0;
	ifstream ifs;
	ifs.open(file);
	if (ifs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return 0;
	}
	else {
		string line;
		while (getline(ifs, line)) {
			num++;
		}
		ifs.close();
	}
	return num;
}

string HelperFunc::searchFile(char* file, string key) const
{
	//To search the file for a specific key
	string result = "";
	ifstream ifs;
	ifs.open(file);
	if (ifs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
	}
	else {
		string line;
		while (getline(ifs, line)) {
			if (split(line, 1) == key) {
				result = line;
				break;
			}
		}
	}
	return result;
}

bool HelperFunc::checkFile(char * file) const
{
	fstream fs;
	bool result;
	//fs.open(file, ios::in||ios::out); 
	string opt(file);
	fs.open(opt.c_str(), ios::in|ios::out);
	int ch;
	ch = fs.get(); 
	if (ch == EOF) { 
		result = false;
	}
	else {
		result = true;
	}
	fs.close();
	return result;
}

void HelperFunc::printAllLines(char * file) const
{
	//To print all the lines in the file
	ifstream ifs;
	ifs.open(file);
	if (ifs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return;
	}
	else {
		string line;
		while (getline(ifs, line)) {
			cout << line << endl; 
		}
		ifs.close();
	}
}

void HelperFunc::addToLastLine(char * file, string str)
{
	//To add to last line of the file
	ofstream ofs;
	ofs.open(file, ios::app);
	if (ofs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return;
	}
	else {
		ofs << str; 
		ofs.close();
	}
}

string HelperFunc::getLastLine(char* file) const
{
	//To get the last line of the file
	string lastline;
	ifstream ifs;
	ifs.open(file);
	if (ifs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return "";
	}
	else {
		while (getline(ifs, lastline)) {}
		ifs.close();
	}
	return lastline;
}

string HelperFunc::split(string str, int num) const
{
	stringstream strs(str);
	string tok;
	int count = 0;
	while (getline(strs, tok, '\t') && ((++count) != num)) {}
	return tok;
}

void HelperFunc::writeBalanceToFile(char * file, string s)
{
	//To write balance to the file
	cleanFile(file);
	fstream fs;
	fs.open(file);
	if (fs.fail()) {
		cout << "Error: " << file << " cannot open" << endl;
		return;
	}
	else {
		fs << s;
		fs.close();
	}
}
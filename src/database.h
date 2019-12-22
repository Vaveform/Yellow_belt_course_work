#pragma once

#include "date.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <stdexcept>
#include <exception>

using namespace std;

struct Entry{
private:
	Date date;
	string activity;
public:
	Entry(const Date& d, const string& e);
	Date GetDate() const;
	string GetEvent() const;
	friend ostream& operator<<(ostream& stream, const Entry& pair);
};

ostream& operator<<(ostream& stream, const Entry& pair);

class Database
{
private:
	map<Date, vector<string>> data;
	map<Date, set<string>> repeated;
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& output) const;
	Entry Last(const Date& date) const;
//	vector<Entry> FindIf()
};

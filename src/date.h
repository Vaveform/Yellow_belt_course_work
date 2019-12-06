#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>

class Date{
private:
	int day;
	int month;
	int year;
public:
	Date();
	Date(const int& new_day, const int& new_month, const int& new_year);
	int GetDay() const;
	int GetMonth() const;
	int GetYear() const;
	bool operator< (const Date& rhd) const;
	friend std::ostream& operator<<(std::ostream& stream, const Date& d);
};

std::ostream& operator<<(std::ostream& stream, const Date& d);

Date ParseDate(std::istream& stream);

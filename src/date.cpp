#include "date.h"

Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}

Date::Date(const int& new_day, const int& new_month, const int& new_year)
{
	day = new_day;
	month = new_month;
	year = new_year;
}
int Date::GetDay() const {
	return day;
}

int Date::GetMonth() const{
	return month;
}

int Date::GetYear() const{
	return year;
}

bool Date::operator< (const Date& rhd) const{
	int sum_days_lhd = 12 * 31 * year + 31 * month + day;
	int sum_days_rhd = 12 * 31 * rhd.GetYear() + 31 * rhd.GetMonth() + rhd.GetDay();
	return sum_days_lhd < sum_days_rhd;
}

std::ostream& operator<<(std::ostream& stream, const Date& d){
	stream << std::setfill('0') << std::setw(4) << d.GetYear() << "-"
							  << std::setw(2) << d.GetMonth() << "-"
							  << std::setw(2) << d.GetDay();
		return stream;
}

Date ParseDate(std::istream& stream){
	std::string error,input_date;
	stream >> error;
	input_date = error;
	std::istringstream inp(input_date);
	int new_year, new_month, new_day;
	char symbol1 , symbol2;
	inp >> new_year >> symbol1 >> new_month >> symbol2;
	if(inp.peek() == -1){
		throw std::runtime_error("Wrong date format: " + error);
	}
	inp >> new_day;
	if(!inp.eof() || symbol1 != '-' || symbol2 != '-'){
		throw std::runtime_error("Wrong date format: " + error);
	}
	else{
		if(new_month > 12 || new_month < 1){
			throw std::runtime_error("Month value is invalid: " + std::to_string(new_month));
		}
		else{
			if(new_day > 31 || new_day < 1){
				throw std::runtime_error("Day value is invalid: " + std::to_string(new_day));
			}
			else{
				return Date(new_day, new_month, new_year);
			}
		}
	}
};

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
	template <typename Func>
	vector<Entry> FindIf(Func predicate)
	{
		vector<Entry> result;
		auto begin_key = data.begin();
		auto begin_vec = data.begin()->second.begin();
		while(begin_key != data.end())
		{
			while(begin_vec != begin_key->second.end())
			{
				begin_vec = find_if(begin_vec, begin_key->second.end(), [begin_key, predicate](const string& e){
					return predicate(begin_key->first, e);
				});
				if(begin_vec != begin_key->second.end())
				{
					Entry tmp(begin_key->first, *begin_vec);
					result.push_back(tmp);
					begin_vec++;
				}
			}
			if(begin_key != data.end()){
				begin_key++;
				begin_vec = begin_key->second.begin();
			}
		}
		return result;
	}
};

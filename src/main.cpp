#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"
#include <iostream>
#include <stdexcept>
#include <map>
#include <algorithm>

using namespace std;

string ParseEvent(istream& is)
{
	string result;
	getline(is, result, '\n');
	auto pos = find_if(result.begin(), result.end(), [](const char& elem){
		return elem != ' ';
	});
	result.erase(result.begin(),pos);
	return result;
}

void TestAll();

int main() {
    TestAll();
//  Database db;
//
//  for (string line; getline(cin, line); ) {
//    istringstream is(line);
//
//    string command;
//    is >> command;
//    if (command == "Add")
//    {
//      const auto date = ParseDate(is);
//      const auto event = ParseEvent(is);
//      db.Add(date, event);
//    }
//    else if (command == "Print")
//    {
//      db.Print(cout);
//    }
//    else if (command == "Del")
//    {
//      auto condition = ParseCondition(is); // shared_ptr<Node> condition
//      auto predicate = [condition](const Date& date, const string& event) {
//        return condition->Evaluate(date, event);
//      };
//      int count = db.RemoveIf(predicate);
//      cout << "Removed " << count << " entries" << endl;
//    }
//    else if (command == "Find")
//    {
//      auto condition = ParseCondition(is);
//      auto predicate = [condition](const Date& date, const string& event) {
//        return condition->Evaluate(date, event);
//      };
//
//      const auto entries = db.FindIf(predicate);
//      for (const auto& entry : entries) {
//        cout << entry << endl;
//      }
//      cout << "Found " << entries.size() << " entries" << endl;
//    }
//    else if (command == "Last")
//    {
//      try {
//          cout << db.Last(ParseDate(is)) << endl;
//      } catch (invalid_argument&) {
//          cout << "No entries" << endl;
//      }
//    }
//    else if (command.empty())
//    {
//      continue;
//    }
//    else
//    {
//      throw logic_error("Unknown command: " + command);
//    }
//  }
  return 0;
}

void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
  }
}
void TestDateClass(){
	  {
		  istringstream is("2018-12-12");
		  AssertEqual(ParseDate(is), Date{2018,12,12}, "Date constructor1");
	  }
	  {
		  istringstream is1("1986-11-25");
		  istringstream is2("1986-11-25");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date, Date{1986,11,25}, "Date constructor2");
		  AssertEqual(second_date, Date{1986,11,25}, "Date constructor3");
		  AssertEqual(first_date == second_date, true, "Test operator == for class date");
	  }
	  {
		  istringstream is1("1986-11-26");
		  istringstream is2("1986-11-25");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date != second_date, true, "Test1 operator != for class date");
	  }
	  {
		  istringstream is1("1986-12-25");
		  istringstream is2("1986-11-25");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date != second_date, true, "Test2 operator != for class date");
	  }
	  {
		  istringstream is1("1987-11-25");
		  istringstream is2("1986-11-25");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date != second_date, true, "Test3 operator != for class date");
	  }
	  {
		  istringstream is1("1986-12-14");
		  istringstream is2("1986-10-15");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date > second_date, true, "Test1 operator > for class date");
	  }
	  {
		  istringstream is1("1982-2-2");
		  istringstream is2("1982-2-4");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date < second_date, true, "Test1 operator < for class date");
	  }
	  {
		  istringstream is1("1982-2-2");
		  istringstream is2("1985-2-4");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date <= second_date, true, "Test1 operator <= for class date");
	  }
	  {
		  istringstream is1("1982-9-2");
		  istringstream is2("1982-12-4");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date <= second_date, true, "Test2 operator <= for class date");
	  }
	  {
		  istringstream is1("1982-2-2");
		  istringstream is2("1982-2-2");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date <= second_date, true, "Test3 operator <= for class date");
	  }
	  {
		  istringstream is1("1986-12-2");
		  istringstream is2("1986-12-1");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date >= second_date, true, "Test1 operator >= for class date");
	  }
	  {
		  istringstream is1("1986-12-5");
		  istringstream is2("1986-12-5");
		  auto first_date = ParseDate(is1);
		  auto second_date = ParseDate(is2);
		  AssertEqual(first_date >= second_date, true, "Test2 operator >= for class date");
	  }
  }
void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  tr.RunTest(TestDateClass, "TestDateClass");
}

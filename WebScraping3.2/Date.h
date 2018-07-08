#pragma once
#include <fstream>
#include <iostream> 
#include <time.h> 

typedef unsigned __int8 uint8;

class Date
{
public:
	Date();
	~Date();
	
	static time_t t_lastDate;
	static tm* lastDate;

	static time_t t_date;
	static tm* date;

	static tm* date30;
	static time_t t_date30;

	static __int8 __range;

	double operator-=(Date&b) { return difftime(mktime(date), mktime(lastDate)); }

	static void selectRange();

	static std::string Parse(tm* date);
private:
	static std::string d_path;
	static size_t seconds;

	static void InitLastDate();
	static void InitDate_30();
	static void InitDate();
	static void InitSeconds();

	static void NewLastDate();

	// Helpers
	static void subSelectRange(uint8 n1, uint8 n3);
};

double operator-(Date &a, Date&b) { return a -= b; }

__int8 Date::__range = 0;

tm* Date::lastDate = new tm();
time_t Date::t_lastDate;

tm* Date::date = NULL;
time_t Date::t_date;

tm* Date::date30;
time_t Date::t_date30;

std::string Date::d_path = ConnectHttp::path + "/_help/lastdate.d24";
size_t Date::seconds;

Date::Date()
{
	InitDate();
	InitLastDate();
	InitSeconds();
	InitDate_30();
	selectRange();
}

Date::~Date()
{
	//NewLastDate(); //TODO IMPORTANT
	delete lastDate;
	delete date;
}

inline void Date::selectRange()
{
	__int8 n1=0,n3=5;
	Date::subSelectRange(0, 5);
}

inline std::string Date::Parse(tm * date)
{
	return std::string();
}

inline void Date::InitLastDate()
{
	// Check whether exists dir path and creates it
	std::string dir = ConnectHttp::path + "/_help";
	File::mkdir(dir);
	std::ifstream f(d_path.c_str());
	if (!f.fail())
	{
		std::string line;
		int *value = &(lastDate->tm_sec);
		while (std::getline(f, line)) {
			*value = stoi(line);
			value++;
		}
		f.close();
	}
	else if (!File::isFile(d_path))
		NewLastDate();
	else
		std::cout << "Error file: * Date.h *";
	t_lastDate = mktime(lastDate);
}

inline void Date::InitDate_30()
{
	t_date30 = t_date;
	t_date30 -= 30*i_Range2;
	t_date30 = t_date30 < t_lastDate ? t_lastDate : t_date30;
	date30=localtime(&t_date30);
}



inline void Date::NewLastDate()
{
	std::ofstream f(d_path.c_str());
	if (!f.fail()) {
		int *value = &(date->tm_sec);
		for (int i = 0; i < 9; i++) {
			f << *value << std::endl;
			value++;
		}
		f.close();
	}
}

inline void Date::InitDate()
{
	time_t t;
	time(&t);
	date = localtime(&t);
	t_date = mktime(date);
}

inline void Date::InitSeconds()
{
	seconds=(size_t) difftime(t_date, t_lastDate);
}

inline void Date::subSelectRange(uint8 n1, uint8 n3)
{
	if (n3 - n1 == 1) {
		Date::__range = (i_Range1[n1] < seconds) ? n1 : n3;
		return;
	}
	uint8 n2 = (n1 +1+ n3) / 2;
	i_Range1[n2] < seconds ? subSelectRange(n1, n2) : subSelectRange(n2, n3);	
}

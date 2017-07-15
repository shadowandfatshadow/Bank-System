#include<iostream>
#include<cmath>
#include"date.h"
using namespace std;
namespace{							//namespace使下面的定义只在当前文件有效
	//表示在某月1日前有多少天
	const int DAY_BEFORE_MONTH[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
}

Date::Date(int year, int month, int day){
	this->year = year;
	this->month = month;
	this->day = day;

	if (day < 0 || day > getMaxDay()){
		cout << "无效输入" << endl;
		show();
		cout << endl;
		exit(1);
	}
	int years = year - 1;
	totalDays = years * 365 + years / 4 - years / 100 + years / 400		//这个算法计算从公元元年1月1日到这天的天数
				+ DAY_BEFORE_MONTH[month]
				+ day;
	if (isLeapYear() && month > 2){
		totalDays++;
	}
}

//获得当月有多少天
int Date::getMaxDay() const{
	if (isLeapYear() && month == 2){
		return 29;
	}
	else{
		return DAY_BEFORE_MONTH[month] - DAY_BEFORE_MONTH[month - 1];
	}
}

void Date::show()const{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}

istream& operator >> (istream & in, Date &date){
	int year, month, day;
	char c1, c2;
	in >> year >> c1 >> month >> c2 >> day;
	date = Date(year, month, day);
	return in;
}

ostream& operator << (ostream & out, const Date &date){
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}










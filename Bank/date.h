/*日期类*/

#ifndef _DATE_H
#define _DATE_H

#include<iostream>

class Date{
private:
	int year;
	int month;
	int day;
	int totalDays;					//该日期是从公元元年1月1日开始的第几天
public:
	Date(){};
	Date(int year, int month, int day);
	int getYear() const{
		return year;
	}
	int getMonth() const{
		return month;
	}
	int getDay() const{
		return day;
	}
	int getMaxDay() const;			//获得当月有多少天
	bool isLeapYear()const{			//判断是否为闰年
		return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	}
	void show() const;				//输出当前日期
	//计算两个日期之间差多少天
	int distance(const Date &date) const{
		return totalDays - date.totalDays;
	}
	int operator - (const Date& date)const {
		return totalDays - date.totalDays;
	}
	//判断两个日期的先后顺序
	bool operator < (const Date& date)const{
		return totalDays < date.totalDays;
	}

};

std::istream & operator >> (std::istream & in, Date & date);
std::ostream & operator << (std::ostream & out,const Date & date);

#endif
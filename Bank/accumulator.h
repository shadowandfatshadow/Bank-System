#ifndef _ACCUMULATOR_H
#define _ACCUMULATOR_H

#include"date.h"
class Accumulator
{
private:
	Date lastDate;						//上次变更数值的日期
	double value;						//数值的当前值
	double sum;							//数值按日累加之和

public:
	Accumulator(const Date &date, double value) :lastDate(date), value(value), sum(0){}

	//获得日期的累加结果
	double getSum(const Date& date) const{
		return sum + value*(date - lastDate);
	}
	//在date将数值变更为value
	void change(const Date& date, double value){
		sum = getSum(date);
		lastDate = date;
		this->value = value;
	}
	//初始化，将日期变为date，数值变为value，累加器清零
	void reset(const Date& date, double value){
		lastDate = date;
		this->value = value;
		sum = 0;
	}
};


#endif
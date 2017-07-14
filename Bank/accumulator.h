#ifndef _ACCUMULATOR_H
#define _ACCUMULATOR_H

#include"date.h"
class Accumulator
{
private:
	Date lastDate;						//�ϴα����ֵ������
	double value;						//��ֵ�ĵ�ǰֵ
	double sum;							//��ֵ�����ۼ�֮��

public:
	Accumulator(const Date &date, double value) :lastDate(date), value(value), sum(0){}

	//������ڵ��ۼӽ��
	double getSum(const Date& date) const{
		return sum + value*(date - lastDate);
	}
	//��date����ֵ���Ϊvalue
	void change(const Date& date, double value){
		sum = getSum(date);
		lastDate = date;
		this->value = value;
	}
	//��ʼ���������ڱ�Ϊdate����ֵ��Ϊvalue���ۼ�������
	void reset(const Date& date, double value){
		lastDate = date;
		this->value = value;
		sum = 0;
	}
};


#endif
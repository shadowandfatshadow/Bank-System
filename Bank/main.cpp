#include<iostream>
#include<cmath>
#include"SavingsAccount.h"


int main(){
	Date date(2008, 11, 1);
	//建立几个用户
	SavingsAccount s1(date, "2014110103", 0.015);
	SavingsAccount s2(date, "2014110104", 0.015);
	CreditAccount c1(date, "c1234", 10000, 0.0005, 50);

	//11月的几笔账目
	s1.deposit(Date(2008, 11, 5), 5000, "salary");
	s2.deposit(Date(2008, 11, 25), 10000, "sell stock");
	c1.withdraw(Date(2008, 11, 15), 2000, "buy something");

	//计算信用卡
	c1.settle(Date(2008, 12, 1));

	//12月的几笔账目
	c1.deposit(Date(2008, 12, 5), 5500, "reply the credit");
	s1.withdraw(Date(2008, 12, 20), 4000, "salary");

	//结算所有账户的信息
	s1.settle(Date(2009, 1, 1));
	s2.settle(Date(2009, 1, 1));
	c1.settle(Date(2009, 1, 1));
	
	//输出用户信息
	cout << endl;
	s1.show();	
	cout << endl;
	s2.show();
	cout << endl;
	c1.show();
	cout << endl;

	cout << "Total:" << Account::getTotal() << endl;

	return 0;
}
#include<iostream>
#include<cmath>
#include"SavingsAccount.h"
using namespace std;

int main(){
	Date date(2008, 11, 1);
	//建立几个用户
	SavingsAccount(date, "2014110103", 0.015),
	SavingsAccount(date, "2014110104", 0.015),
	CreditAccount(date, "2014110107", 0.015)


	//11月的几笔账目
	accounts[0].deposit(Date(2008, 11, 5), 5000, "salary");
	accounts[1].deposit(Date(2008, 11, 25), 10000, "sell stock");

	//12月的几笔账目
	accounts[0].deposit(Date(2008, 12, 5), 5500, "salary");
	accounts[1].withdraw(Date(2008, 12, 20), 4000, "buy food");

	//结算所有账户的信息
	cout << endl;
	for (int i = 0; i < n; i++){
		accounts[i].settle(Date(2009, 1, 1));
		accounts[i].show();
	}
	cout << "total is :" << SavingsAccount::getTotal() << endl;

	return 0;
}
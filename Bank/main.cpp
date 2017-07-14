#include<iostream>
#include<cmath>
#include"SavingsAccount.h"
using namespace std;

int main(){
	Date date(2008, 11, 1);
	//���������û�
	SavingsAccount(date, "2014110103", 0.015),
	SavingsAccount(date, "2014110104", 0.015),
	CreditAccount(date, "2014110107", 0.015)


	//11�µļ�����Ŀ
	accounts[0].deposit(Date(2008, 11, 5), 5000, "salary");
	accounts[1].deposit(Date(2008, 11, 25), 10000, "sell stock");

	//12�µļ�����Ŀ
	accounts[0].deposit(Date(2008, 12, 5), 5500, "salary");
	accounts[1].withdraw(Date(2008, 12, 20), 4000, "buy food");

	//���������˻�����Ϣ
	cout << endl;
	for (int i = 0; i < n; i++){
		accounts[i].settle(Date(2009, 1, 1));
		accounts[i].show();
	}
	cout << "total is :" << SavingsAccount::getTotal() << endl;

	return 0;
}
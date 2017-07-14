#include<iostream>
#include<cmath>
#include"Account.h"


int main(){
	Date date(2008, 11, 1);
	//建立几个用户
	SavingsAccount s1(date, "2014110103", 0.015);
	SavingsAccount s2(date, "2014110104", 0.015);
	CreditAccount c1(date, "c1234", 10000, 0.0005, 50);

	Account* accounts[] = { &s1, &s2, &c1 };
	const int n = sizeof(accounts) / sizeof(Account*);			//账户总数
	//c选项的意思是在这个月改变天数，d选项是进入下个月
	cout << "(d)存钱 (w)取钱 (s)显示 (c)change day  (n)next month  (e) exit" << endl;
	char cmd;

	do{
		date.show();
		cout << "\tTotal:" << Account::getTotal << "\tcommand>";
		int index, day;
		double amount;
		string desc;
		cin >> cmd;
		switch (cmd){
		case 'd':
			cout << "请输入账号下标和要存入的金额" << endl;
			cin >> index >> amount;					//输下标和金额，不人性化
			cout << "请为这笔钱做一个解释" << endl;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "请输入账号下标和要取出的金额" << endl;
			cin >> index >> amount;
			cout << "请为这笔钱做一个解释" << endl;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
			for (int i = 0; i < n; i++){
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':
			cin >> day;
			if (day < date.getDay()){
				cout << "无法选之前的日子";
			}
			else if (day > date.getMaxDay()){
				cout << "这个月没有这一天哦";
			}
			else{
				date = Date(date.getYear(), date.getMonth(), day);
			}
			break;
		case 'n':
			if (date.getMonth() == 12){
				date = Date(date.getYear() + 1, 1, 1);
			}
			else{
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}
			for (int i = 0; i < n; i++){
				accounts[i]->settle(date);
			}
			break;
		}
	} while (cmd != 'e');

	return 0;
}
#include<iostream>
#include<cmath>
#include"Account.h"
#include"Array.h"


int main(){
	Date date(2008, 11, 1);

	Array<Account*>accounts(0);					//创建账户数组，元素个数为0；

	//c选项的意思是在这个月改变天数，d选项是进入下个月
	cout << "(a)添加用户 (d)存钱 (w)取钱 (s)显示 (c)改变日期  (n)跳转到下个月  (e) exit" << endl;
	char cmd;

	do{
		date.show();
		cout << "\tTotal:" << Account::getTotal() << "\tcommand>";

		char type;
		int index, day;						//下标，要更改的天数
		double amount,credit,rate,fee;
		string id,desc;
		Account* account;

		cin >> cmd;
		switch (cmd){
		case 'a':
			cout << "请输入添加账户的类型：(s)储蓄账户 (c)信用卡账户" << endl;
			cin >> type;
			if (type == 's'){
				cout << "请输入账户id" << endl;
				cin >> id;
				cout << "请输入利率：";
				cin >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "请输入账户id" << endl;
				cin >> id;
				cout << "请输入透支额度：";
				cin >> credit;
				cout << endl;
				cout << "请输入利率：";
				cin >> rate;
				cout << endl;
				cout << "请输入信用卡年费：";
				cin >> fee;
				cout << endl;
				account = new CreditAccount(date, id,credit,rate,fee);
			}
			else{
				cout << "选择错误！" << endl;
				break;
			}
			accounts.resize(accounts.getSize() + 1);				//修改数组大小
			accounts[accounts.getSize() - 1] = account;				//将数组最后一个元素赋值为当前创建的对象
			break;
		case 'd':
			cout << "请输入账号下标和要存入的金额,并添加解释" << endl;
			cin >> index >> amount;					//输下标和金额，不人性化
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "请输入账号下标和要取出的金额，并添加解释" << endl;
			cin >> index >> amount;
			getline(cin, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
			for (int i = 0; i < accounts.getSize(); i++){
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
			for (int i = 0; i < accounts.getSize(); i++){
				accounts[i]->settle(date);
			}
			break;
		}
	} while (cmd != 'e');

	for (int i = 0; i < accounts.getSize(); i++){
		delete accounts[i];
	}

	return 0;
}
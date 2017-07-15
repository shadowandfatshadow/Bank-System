#include<iostream>
#include<cmath>
#include"Account.h"
//#include"Array.h"
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
using namespace std;

struct deleter{
	template<typename T>void operator () (T* p){
		delete p;
	}
};

class Controller{											//控制器，用来存储账户列表和处理命令
private:
	Date date;
	vector<Account*> accounts;
	bool end;											//用户是否输入了结束命令
public:
	Controller(const Date & date) :date(date), end(false){}
	~Controller();
	const Date& getDate()const{ return date; }
	bool isEnd(){
		return end;
	}
	//执行一条命令，返回该命令是否改变了当前状态(即是否需要保存该条命令)
	bool runCommand(const string & cmdLine);
};

Controller::~Controller(){
	for_each(accounts.begin(), accounts.end(), deleter());
}

bool Controller::runCommand(const string & cmdLine){
	istringstream str(cmdLine);			//istringstream类用于执行C++风格的串流的输入操作。
	
	char type,cmd;
	int index, day;						//下标，要更改的天数
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	Date date1, date2;

	str >> cmd;
	switch (cmd){
		case 'a':
			cout << "请输入添加账户的类型：(s)储蓄账户 (c)信用卡账户" << endl;
			str >> type;
			if (type == 's'){
				cout << "请输入账户id" << endl;
				str >> id;
				cout << "请输入利率：";
				str >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "请输入账户id" << endl;
				str >> id;
				cout << "请输入透支额度：";
				str >> credit;
				cout << endl;
				cout << "请输入利率：";
				str >> rate;
				cout << endl;
				cout << "请输入信用卡年费：";
				str >> fee;
				cout << endl;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			else{
				cout << "选择错误！" << endl;
				return true;
			}
			//			accounts.resize(accounts.getSize() + 1);				//修改数组大小
			//			accounts[accounts.getSize() - 1] = account;				//将数组最后一个元素赋值为当前创建的对象

			accounts.push_back(account);							//添加到末尾
			return true;
		case 'd':
//			cout << "请输入账号下标和要存入的金额,并添加解释" << endl;
			str >> index >> amount;					//输下标和金额，不人性化
			getline(str, desc);
			accounts[index]->deposit(date, amount, desc);
			return true;
		case 'w':
//			cout << "请输入账号下标和要取出的金额，并添加解释" << endl;
			str >> index >> amount;
			getline(str, desc);
			accounts[index]->withdraw(date, amount, desc);
			return true;
		case 's':
			//			for (int i = 0; i < accounts.getSize(); i++){
			//这个size_t就是unsigned int
			for (size_t i = 0; i < accounts.size(); i++){			//vector用size就可以得到数组元素个数
				cout << "[" << i << "]";
				cout << endl;
			}
			return false;
		case 'c':
			str >> day;
			if (day < date.getDay()){
				cout << "无法选之前的日子";
			}
			else if (day > date.getMaxDay()){
				cout << "这个月没有这一天哦";
			}
			else{
				date = Date(date.getYear(), date.getMonth(), day);
			}
			return true;
		case 'n':
			if (date.getMonth() == 12){
				date = Date(date.getYear() + 1, 1, 1);
			}
			else{
				date = Date(date.getYear(), date.getMonth() + 1, 1);
			}
			for (vector<Account*>::iterator it = accounts.begin(); it != accounts.end(); ++it){
				(*it)->settle(date);
			}
			return true;
		case 'q':
//			cout << "请输入两个日期：形式如下：xxxx-xx-xx" << endl;
			str >> date1 >> date2;
			Account::query(date1, date2);
			return false;
		case 'e':
			end = true;
			return false;
		}
	cout << "invalid command:" << cmdLine << endl;
	return false;
}

int main(){
	Date date(2008, 11, 1);

	Controller controller(date);
	string cmdLine;
	const char* FILE_NAME = "commands.txt";
	ifstream fileIn(FILE_NAME);					//以读模式打开文件
	if (fileIn){
		while (getline(fileIn,cmdLine))
		{
			controller.runCommand(cmdLine);
		}
		fileIn.close();
	}

	ofstream fileOut(FILE_NAME, ios_base::app);		//以追加模式打开文件
	cout << "(a)添加用户 (d)存钱 (w)取钱 (s)显示 (c)改变日期  (n)跳转到下个月 (q)查询 (e) exit" << endl;
	while (!controller.isEnd()){					//从标准输入读入命令并执行，直到退出
		cout << controller.getDate() << "\tTotal:" << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		if (controller.runCommand(cmdLine)){
			fileOut << cmdLine << endl;				//将命令写入文件
		}
	}
	return 0;

	/*
//	Array<Account*>accounts(0);					//创建账户数组，元素个数为0；

	vector<Account*>accounts;						//创建账户数组，元素个数为0；

	//c选项的意思是在这个月改变天数，d选项是进入下个月
	cout << "(a)添加用户 (d)存钱 (w)取钱 (s)显示 (c)改变日期  (n)跳转到下个月 (q)查询 (e) exit" << endl;
	char cmd;

	do{
		date.show();
		cout << "\tTotal:" << Account::getTotal() << "\tcommand>";

		char type;
		int index, day;						//下标，要更改的天数
		double amount,credit,rate,fee;
		string id,desc;
		Account* account;
		Date date1, date2;

		str >> cmd;
		switch (cmd){
		case 'a':
			cout << "请输入添加账户的类型：(s)储蓄账户 (c)信用卡账户" << endl;
			str >> type;
			if (type == 's'){
				cout << "请输入账户id" << endl;
				str >> id;
				cout << "请输入利率：";
				str >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "请输入账户id" << endl;
				str >> id;
				cout << "请输入透支额度：";
				str >> credit;
				cout << endl;
				cout << "请输入利率：";
				str >> rate;
				cout << endl;
				cout << "请输入信用卡年费：";
				str >> fee;
				cout << endl;
				account = new CreditAccount(date, id,credit,rate,fee);
			}
			else{
				cout << "选择错误！" << endl;
				break;
			}
//			accounts.resize(accounts.getSize() + 1);				//修改数组大小
//			accounts[accounts.getSize() - 1] = account;				//将数组最后一个元素赋值为当前创建的对象

			accounts.push_back(account);							//添加到末尾
			break;
		case 'd':
			cout << "请输入账号下标和要存入的金额,并添加解释" << endl;
			str >> index >> amount;					//输下标和金额，不人性化
			getline(str, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "请输入账号下标和要取出的金额，并添加解释" << endl;
			str >> index >> amount;
			getline(str, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
//			for (int i = 0; i < accounts.getSize(); i++){
			//这个size_t就是unsigned int
			for (size_t i = 0; i < accounts.size(); i++){			//vector用size就可以得到数组元素个数
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':
			str >> day;
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
//			for (int i = 0; i < accounts.getSize(); i++){
//				accounts[i]->settle(date);
//
//			}

			for (vector<Account*>::iterator it = accounts.begin(); it != accounts.end(); ++it){
				(*it)->settle(date);
			}
			break;
		case 'q':
			cout << "请输入两个日期：形式如下：xxxx-xx-xx" << endl;
			date1 = Date::read();
			date2 = Date::read();
			Account::query(date1, date2);
			break;
		}
	} while (cmd != 'e');

//	for (int i = 0; i < accounts.getSize(); i++){
//		delete accounts[i];
//	}


	for_each(accounts.begin(), accounts.end(), deleter());
	return 0;
	*/
}
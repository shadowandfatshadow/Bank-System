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

class Controller{											//�������������洢�˻��б�ʹ�������
private:
	Date date;
	vector<Account*> accounts;
	bool end;											//�û��Ƿ������˽�������
public:
	Controller(const Date & date) :date(date), end(false){}
	~Controller();
	const Date& getDate()const{ return date; }
	bool isEnd(){
		return end;
	}
	//ִ��һ��������ظ������Ƿ�ı��˵�ǰ״̬(���Ƿ���Ҫ�����������)
	bool runCommand(const string & cmdLine);
};

Controller::~Controller(){
	for_each(accounts.begin(), accounts.end(), deleter());
}

bool Controller::runCommand(const string & cmdLine){
	istringstream str(cmdLine);			//istringstream������ִ��C++���Ĵ��������������
	
	char type,cmd;
	int index, day;						//�±꣬Ҫ���ĵ�����
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	Date date1, date2;

	str >> cmd;
	switch (cmd){
		case 'a':
			cout << "����������˻������ͣ�(s)�����˻� (c)���ÿ��˻�" << endl;
			str >> type;
			if (type == 's'){
				cout << "�������˻�id" << endl;
				str >> id;
				cout << "���������ʣ�";
				str >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "�������˻�id" << endl;
				str >> id;
				cout << "������͸֧��ȣ�";
				str >> credit;
				cout << endl;
				cout << "���������ʣ�";
				str >> rate;
				cout << endl;
				cout << "���������ÿ���ѣ�";
				str >> fee;
				cout << endl;
				account = new CreditAccount(date, id, credit, rate, fee);
			}
			else{
				cout << "ѡ�����" << endl;
				return true;
			}
			//			accounts.resize(accounts.getSize() + 1);				//�޸������С
			//			accounts[accounts.getSize() - 1] = account;				//���������һ��Ԫ�ظ�ֵΪ��ǰ�����Ķ���

			accounts.push_back(account);							//��ӵ�ĩβ
			return true;
		case 'd':
//			cout << "�������˺��±��Ҫ����Ľ��,����ӽ���" << endl;
			str >> index >> amount;					//���±�ͽ������Ի�
			getline(str, desc);
			accounts[index]->deposit(date, amount, desc);
			return true;
		case 'w':
//			cout << "�������˺��±��Ҫȡ���Ľ�����ӽ���" << endl;
			str >> index >> amount;
			getline(str, desc);
			accounts[index]->withdraw(date, amount, desc);
			return true;
		case 's':
			//			for (int i = 0; i < accounts.getSize(); i++){
			//���size_t����unsigned int
			for (size_t i = 0; i < accounts.size(); i++){			//vector��size�Ϳ��Եõ�����Ԫ�ظ���
				cout << "[" << i << "]";
				cout << endl;
			}
			return false;
		case 'c':
			str >> day;
			if (day < date.getDay()){
				cout << "�޷�ѡ֮ǰ������";
			}
			else if (day > date.getMaxDay()){
				cout << "�����û����һ��Ŷ";
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
//			cout << "�������������ڣ���ʽ���£�xxxx-xx-xx" << endl;
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
	ifstream fileIn(FILE_NAME);					//�Զ�ģʽ���ļ�
	if (fileIn){
		while (getline(fileIn,cmdLine))
		{
			controller.runCommand(cmdLine);
		}
		fileIn.close();
	}

	ofstream fileOut(FILE_NAME, ios_base::app);		//��׷��ģʽ���ļ�
	cout << "(a)����û� (d)��Ǯ (w)ȡǮ (s)��ʾ (c)�ı�����  (n)��ת���¸��� (q)��ѯ (e) exit" << endl;
	while (!controller.isEnd()){					//�ӱ�׼����������ִ�У�ֱ���˳�
		cout << controller.getDate() << "\tTotal:" << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		if (controller.runCommand(cmdLine)){
			fileOut << cmdLine << endl;				//������д���ļ�
		}
	}
	return 0;

	/*
//	Array<Account*>accounts(0);					//�����˻����飬Ԫ�ظ���Ϊ0��

	vector<Account*>accounts;						//�����˻����飬Ԫ�ظ���Ϊ0��

	//cѡ�����˼��������¸ı�������dѡ���ǽ����¸���
	cout << "(a)����û� (d)��Ǯ (w)ȡǮ (s)��ʾ (c)�ı�����  (n)��ת���¸��� (q)��ѯ (e) exit" << endl;
	char cmd;

	do{
		date.show();
		cout << "\tTotal:" << Account::getTotal() << "\tcommand>";

		char type;
		int index, day;						//�±꣬Ҫ���ĵ�����
		double amount,credit,rate,fee;
		string id,desc;
		Account* account;
		Date date1, date2;

		str >> cmd;
		switch (cmd){
		case 'a':
			cout << "����������˻������ͣ�(s)�����˻� (c)���ÿ��˻�" << endl;
			str >> type;
			if (type == 's'){
				cout << "�������˻�id" << endl;
				str >> id;
				cout << "���������ʣ�";
				str >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "�������˻�id" << endl;
				str >> id;
				cout << "������͸֧��ȣ�";
				str >> credit;
				cout << endl;
				cout << "���������ʣ�";
				str >> rate;
				cout << endl;
				cout << "���������ÿ���ѣ�";
				str >> fee;
				cout << endl;
				account = new CreditAccount(date, id,credit,rate,fee);
			}
			else{
				cout << "ѡ�����" << endl;
				break;
			}
//			accounts.resize(accounts.getSize() + 1);				//�޸������С
//			accounts[accounts.getSize() - 1] = account;				//���������һ��Ԫ�ظ�ֵΪ��ǰ�����Ķ���

			accounts.push_back(account);							//��ӵ�ĩβ
			break;
		case 'd':
			cout << "�������˺��±��Ҫ����Ľ��,����ӽ���" << endl;
			str >> index >> amount;					//���±�ͽ������Ի�
			getline(str, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "�������˺��±��Ҫȡ���Ľ�����ӽ���" << endl;
			str >> index >> amount;
			getline(str, desc);
			accounts[index]->withdraw(date, amount, desc);
			break;
		case 's':
//			for (int i = 0; i < accounts.getSize(); i++){
			//���size_t����unsigned int
			for (size_t i = 0; i < accounts.size(); i++){			//vector��size�Ϳ��Եõ�����Ԫ�ظ���
				cout << "[" << i << "]";
				accounts[i]->show();
				cout << endl;
			}
			break;
		case 'c':
			str >> day;
			if (day < date.getDay()){
				cout << "�޷�ѡ֮ǰ������";
			}
			else if (day > date.getMaxDay()){
				cout << "�����û����һ��Ŷ";
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
			cout << "�������������ڣ���ʽ���£�xxxx-xx-xx" << endl;
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
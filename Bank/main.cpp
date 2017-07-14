#include<iostream>
#include<cmath>
#include"Account.h"


int main(){
	Date date(2008, 11, 1);
	//���������û�
	SavingsAccount s1(date, "2014110103", 0.015);
	SavingsAccount s2(date, "2014110104", 0.015);
	CreditAccount c1(date, "c1234", 10000, 0.0005, 50);

	Account* accounts[] = { &s1, &s2, &c1 };
	const int n = sizeof(accounts) / sizeof(Account*);			//�˻�����
	//cѡ�����˼��������¸ı�������dѡ���ǽ����¸���
	cout << "(d)��Ǯ (w)ȡǮ (s)��ʾ (c)change day  (n)next month  (e) exit" << endl;
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
			cout << "�������˺��±��Ҫ����Ľ��" << endl;
			cin >> index >> amount;					//���±�ͽ������Ի�
			cout << "��Ϊ���Ǯ��һ������" << endl;
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "�������˺��±��Ҫȡ���Ľ��" << endl;
			cin >> index >> amount;
			cout << "��Ϊ���Ǯ��һ������" << endl;
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
			for (int i = 0; i < n; i++){
				accounts[i]->settle(date);
			}
			break;
		}
	} while (cmd != 'e');

	return 0;
}
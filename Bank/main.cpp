#include<iostream>
#include<cmath>
#include"Account.h"
#include"Array.h"


int main(){
	Date date(2008, 11, 1);

	Array<Account*>accounts(0);					//�����˻����飬Ԫ�ظ���Ϊ0��

	//cѡ�����˼��������¸ı�������dѡ���ǽ����¸���
	cout << "(a)����û� (d)��Ǯ (w)ȡǮ (s)��ʾ (c)�ı�����  (n)��ת���¸���  (e) exit" << endl;
	char cmd;

	do{
		date.show();
		cout << "\tTotal:" << Account::getTotal() << "\tcommand>";

		char type;
		int index, day;						//�±꣬Ҫ���ĵ�����
		double amount,credit,rate,fee;
		string id,desc;
		Account* account;

		cin >> cmd;
		switch (cmd){
		case 'a':
			cout << "����������˻������ͣ�(s)�����˻� (c)���ÿ��˻�" << endl;
			cin >> type;
			if (type == 's'){
				cout << "�������˻�id" << endl;
				cin >> id;
				cout << "���������ʣ�";
				cin >> rate;
				cout << endl;
				account = new SavingsAccount(date, id, rate);
			}
			else if (type == 'c'){
				cout << "�������˻�id" << endl;
				cin >> id;
				cout << "������͸֧��ȣ�";
				cin >> credit;
				cout << endl;
				cout << "���������ʣ�";
				cin >> rate;
				cout << endl;
				cout << "���������ÿ���ѣ�";
				cin >> fee;
				cout << endl;
				account = new CreditAccount(date, id,credit,rate,fee);
			}
			else{
				cout << "ѡ�����" << endl;
				break;
			}
			accounts.resize(accounts.getSize() + 1);				//�޸������С
			accounts[accounts.getSize() - 1] = account;				//���������һ��Ԫ�ظ�ֵΪ��ǰ�����Ķ���
			break;
		case 'd':
			cout << "�������˺��±��Ҫ����Ľ��,����ӽ���" << endl;
			cin >> index >> amount;					//���±�ͽ������Ի�
			getline(cin, desc);
			accounts[index]->deposit(date, amount, desc);
			break;
		case 'w':
			cout << "�������˺��±��Ҫȡ���Ľ�����ӽ���" << endl;
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
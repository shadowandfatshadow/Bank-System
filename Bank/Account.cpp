#include<iostream>
#include<cmath>
#include"Account.h"
#include"accumulator.h"
using namespace std;

//��̬������ʼ��
double Account::total = 0;

//Account���ʵ��
Account::Account(const Date& date, const string& id):id(id),balance(0){
	date.show();
	cout << "\t#" << id << "created" << endl;
}
void Account::record(const Date& date, double amount, const string &desc){
	amount = floor(amount * 100 + 0.5) / 100;				//����С�������λ,floor������ȡ����+0.5��Ϊ����������
	balance += amount;										//���仯
	total += amount;										//�ܽ��仯
	date.show();
	cout << "\t" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;

}

void Account::show()const{
	cout << "#" << id << "\tBanlance:" << balance ;
}

void Account::err(const string& msg)const{
	cout << "Error" << msg << endl;
}

//SavingsAccount����غ�����ʵ��
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)
:Account(date,id),rate(rate),acc(date,0){}


void SavingsAccount::deposit(const Date& date, double amount,const string& desc){
	record(date, amount,desc);
	acc.change(date, getBalance());
}

void SavingsAccount::withdraw(const Date& date, double amount, const string& desc){
	if (amount > getBalance()){								//ȡǮ̫��϶�����
		cout << "�Բ�����û��ô��Ǯ������������" << endl;
	}
	else{
		record(date, -amount,desc);
		acc.change(date, getBalance());
	}
}

void  SavingsAccount::settle(const Date& date){
	double interest = acc.getSum(date) * rate / (date-Date(date.getYear() - 1,1,1));		//������Ϣ
	if (interest != 0){
		record(date, interest,"interest");
	}
	acc.reset(date, getBalance());
}

//CreditAccount����غ�����ʵ��
CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
	:Account(date,id), credit(credit), rate(rate), fee(fee), acc(date, 0){}

void CreditAccount::deposit(const Date& date, double amount, const string& desc){
	record(date, amount, desc);
	acc.change(date, getBalance());
}

void CreditAccount::withdraw(const Date& date, double amount, const string& desc){
	if (amount > getCredit()){								//ȡǮ̫��϶�����
		cout << "�Բ�����û��ô��Ǯ������������" << endl;
	}
	else{
		record(date, -amount, desc);
		acc.change(date, getBalance());
	}
}

void  CreditAccount::settle(const Date& date){
	double interest = acc.getSum(date) * rate;
	if (interest != 0){
		record(date, interest, "interest");
	}
	if (date.getMonth() == 1){
		record(date, -fee, "annual fee");
	}
	acc.reset(date, getDebt());
}

void CreditAccount::show()const{
	Account::show();
	cout << "\tAvailable credit:" << getAvailableCredit();
}

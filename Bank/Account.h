#ifndef _SAVINGSACCOUNT_H 
#define _SAVINGSACCOUNT_H

#include"accumulator.h"
#include <string>
using namespace std;

class Account{										//�˻��࣬���Ǹ����࣬���������������˻��������˻���֮���
private:
	string id;										//�˺�
	double balance;									//���
	static double total;							//�����˻����ܽ��
protected:
	//��������ʹ�õĹ��캯����idΪ�˻�
	Account(const Date& date, const string& id);
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(const Date& date, double amount, const string &desc);
	//���������Ϣ
	void err(const string& msg)const;
public:
	string getId()const{						//����Ҫ�ı����״̬�ĳ�Ա������������Ϊconst��Ա����
		return id;
	}
	double getBalance()const{
		return balance;
	}
	static double getTotal(){
		return total;
	}

	virtual void deposit(const Date& date, double amount, const string &desc) = 0;		//���麯�� �����ֽ�
	virtual void withdraw(const Date& date, double amount, const string &desc) = 0;	//ȡ���ֽ�	
	//������Ϣ��ÿ��һ��һ�յ��ô˺���
	virtual void settle(const Date &date) = 0;										
	//��ʾ
	virtual void show()const;
};




class SavingsAccount:public Account{					//�����˻���	
private:
	double rate;										//������
	Accumulator acc;									//����������Ϣ���ۼ���
public:
	SavingsAccount(const Date& date, const string &id, double rate);
	double getRate()const{
		return rate;
	}

	void deposit(const Date& date, double amount,const string &desc);				//�����ֽ�
	void withdraw(const Date& date, double amount, const string &desc);				//ȡ���ֽ�
	//������Ϣ��ÿ��һ��һ�յ��ô˺���
	void settle(const Date& date);
};

class CreditAccount:public Account{
private:
	Accumulator acc;
	double credit;											//���ö��
	double rate;												//Ƿ���������
	double fee;												//���ÿ����
	double getDebt()const {									//���Ƿ���	
		double balance = getBalance();
		return (balance > 0 ? balance : 0);
	}

public:
	CreditAccount(const Date& date,const string& id, double credit, double rate, double fee);
	double getCredit()const{
		return credit;
	}
	double getRate()const{
		return rate;
	}
	double getFee()const{
		return fee;
	}
	double getAvailableCredit()const{
		if (getBalance() < 0){
			return credit + getBalance();
		}else{
			return credit;
		}
	}

	void deposit(const Date& date, double amount, const string &desc);				//�����ֽ�
	void withdraw(const Date& date, double amount, const string &desc);				//ȡ���ֽ�
	//������Ϣ��ÿ��һ��һ�յ��ô˺���
	void settle(const Date& date);
	void show()const;
};


#endif

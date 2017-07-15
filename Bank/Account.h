/*�˻��࣬���������˻������ÿ��˻�*/

#ifndef _SAVINGSACCOUNT_H 
#define _SAVINGSACCOUNT_H

#include"accumulator.h"
#include <string>
#include	<map>
#include <istream>
using namespace std;

class Account;										//ǰ������
class AccountRecord{									//��Ŀ��¼
private:
	Date date;										//����
	const Account* account;							//�˻�
	double amount;									//���
	double balance;									//���
	string desc;										//����
public:
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const string& desc);
	void show()const;
};


//���������洢�˻���¼�Ķ���ӳ������
typedef std::multimap<Date, AccountRecord> RecordMap;

class Account{										//�˻��࣬���Ǹ����࣬���������������˻��������˻���֮���
private:
	string id;										//�˺�
	double balance;									//���
	static double total;								//�����˻����ܽ��
	static RecordMap recordMap;						//��Ŀ��¼
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
	//��ѯָ��ʱ���ڵ���Ŀ��¼
	static void query(const Date& begin, const Date& end);
	virtual void show(std::ostream &out)const;
};

inline std::ostream& operator << (std::ostream &out, const Account &account){
	account.show(out);
	return out;
}


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
	virtual void show(std::ostream &out)const;
};


#endif

/*账户类，包含储蓄账户和信用卡账户*/

#ifndef _SAVINGSACCOUNT_H 
#define _SAVINGSACCOUNT_H

#include"accumulator.h"
#include <string>
#include	<map>
#include <istream>
using namespace std;

class Account;										//前置声明
class AccountRecord{									//账目记录
private:
	Date date;										//日期
	const Account* account;							//账户
	double amount;									//金额
	double balance;									//余额
	string desc;										//描述
public:
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const string& desc);
	void show()const;
};


//定义用来存储账户记录的多重映射类型
typedef std::multimap<Date, AccountRecord> RecordMap;

class Account{										//账户类，这是个基类，可以派生出储蓄账户，信用账户啊之类的
private:
	string id;										//账号
	double balance;									//余额
	static double total;								//所有账户的总金额
	static RecordMap recordMap;						//账目记录
protected:
	//供派生类使用的构造函数，id为账户
	Account(const Date& date, const string& id);
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(const Date& date, double amount, const string &desc);
	//报告错误信息
	void err(const string& msg)const;
public:
	string getId()const{						//不需要改变对象状态的成员函数可以声明为const成员函数
		return id;
	}
	double getBalance()const{
		return balance;
	}
	static double getTotal(){
		return total;
	}

	virtual void deposit(const Date& date, double amount, const string &desc) = 0;		//纯虚函数 存入现金
	virtual void withdraw(const Date& date, double amount, const string &desc) = 0;	//取出现金	
	//结算利息，每年一月一日调用此函数
	virtual void settle(const Date &date) = 0;										
	//查询指定时间内的账目记录
	static void query(const Date& begin, const Date& end);
	virtual void show(std::ostream &out)const;
};

inline std::ostream& operator << (std::ostream &out, const Account &account){
	account.show(out);
	return out;
}


class SavingsAccount:public Account{					//储蓄账户类	
private:
	double rate;										//年利率
	Accumulator acc;									//辅助计算利息的累加器
public:
	SavingsAccount(const Date& date, const string &id, double rate);
	double getRate()const{
		return rate;
	}

	void deposit(const Date& date, double amount,const string &desc);				//存入现金
	void withdraw(const Date& date, double amount, const string &desc);				//取出现金
	//结算利息，每年一月一日调用此函数
	void settle(const Date& date);
};

class CreditAccount:public Account{
private:
	Accumulator acc;
	double credit;											//信用额度
	double rate;												//欠款的日利率
	double fee;												//信用卡年费
	double getDebt()const {									//获得欠额款	
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

	void deposit(const Date& date, double amount, const string &desc);				//存入现金
	void withdraw(const Date& date, double amount, const string &desc);				//取出现金
	//结算利息，每年一月一日调用此函数
	void settle(const Date& date);
	virtual void show(std::ostream &out)const;
};


#endif

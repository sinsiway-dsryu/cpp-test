#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdio>
// #include <ctime>

struct dgt_bank_account {
	char* name;
	char* account_number;
	char account_create_time[20];
	char transaction_time[20];
	unsigned int amount_money;	
};

class BankAccount {
  private:
	dgt_bank_account* Account;

  public:
	BankAccount();
	~BankAccount();
	void init(char* name);
	// static const time_t ACCOUNT_CREATE_TIME;
	inline char* getAccountName() { return Account->name; }
	inline char* getAccountNumber() { return Account->account_number; }
	inline char* getAccountCreateTime() { return Account->account_create_time; }
	inline char* getTransactionTime() { return Account->transaction_time; }
	inline unsigned int getAmountMoney() { return Account->amount_money; }
	void setAccountName(char* name);
	void setAccountNumber();
	// void setTimeString(char time_string[], time_t raw_time);
	void setCurrentTime(char time_string[]);
	void deposit(unsigned int money);
	void withdraw(unsigned int money); 
};
#endif //BANK_ACCOUNT

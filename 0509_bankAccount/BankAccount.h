#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

class BankAccount {
  private:
	char*	Name;
	char	AccountCreationTime[20];
	int	AmountOfMoney;
//	char*	Transaction;
//	char*	TransactionTime;

  public:
	~BankAccount();
	void	init(char* name);
	void	deposit(int money);
	void	withdraw(int money);  
	void	printAccountInfo();
	void	printAmountOfMoney();
	void	setCurrentTime(char time_string[]);

};
#endif //BANK_ACCOUNT

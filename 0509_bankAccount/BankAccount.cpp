#include "BankAccount.h" 
#include <cstring>
#include <ctime>

BankAccount::BankAccount() {}
BankAccount::~BankAccount() {
	delete Account->name;
	delete Account->account_number;
	delete Account;
}

void BankAccount::init(char* param_name) {
	// create struct
	Account = new dgt_bank_account();
	memset(Account, 0, sizeof(dgt_bank_account));
	setAccountName(param_name); // account name
	setAccountNumber(); // account number
	// const int ACCOUNT_CREATE_TIME = time(NULL); // set account creation time
	setCurrentTime(Account->account_create_time);
	Account->amount_money = 0; // amount of money
}

void BankAccount::setAccountName(char* param_name) {
	// Name = (char*)malloc(strlen(name) + 1); // by cstdlib
	Account->name = new char[strlen(param_name)+1];
	memset(Account->name,0,strlen(param_name)+1);
	strcpy(Account->name,param_name);
}

void BankAccount::setAccountNumber() {
	char* account_number = (char*)"12-00-93";
	Account->account_number = new char[strlen(account_number)+1];
	memset(Account->account_number,0,strlen(account_number)+1);
	strcpy(Account->account_number,account_number);
}

void BankAccount::setCurrentTime(char time_string[]) {
	time_t raw_time = time(NULL);
	struct tm* p_time = localtime(&raw_time);
	strftime(time_string, 20, "%Y/%m/%d %H:%M:%S", p_time);
}

void BankAccount::deposit(unsigned int money) {
	Account->amount_money += money;
	setCurrentTime(Account->transaction_time);
}

void BankAccount::withdraw(unsigned int money) {
	Account->amount_money -= money;
	setCurrentTime(Account->transaction_time);
}
#include "BankAccount.h" 

void BankAccount::init(char* name) {
	// name 
	Name = (char*)malloc(strlen(name) + 1);
	strcpy(Name, name);
	// amount of money
	AmountOfMoney = 0;
	// account creation time
	setCurrentTime(AccountCreationTime);
	// account number
	setAccountNumber();
}

void BankAccount::deposit(int money) {
	AmountOfMoney += money;
	setCurrentTime(TransactionTime);
	printf("deposit $%d | time: %s\n",money,TransactionTime);
}

void BankAccount::withdraw(int money) {
	AmountOfMoney -= money;
	setCurrentTime(TransactionTime);
	printf("withdraw $%d | time: %s\n",money,TransactionTime);
}

void BankAccount::printAccountCreateInfo() {
	printf("name: %s | account number: %s\ncreate time: %s | money: $%d\n",Name,AccountNumber,AccountCreationTime,AmountOfMoney);
}

void BankAccount::printAccountInfo() {
	printf("name: %s | account number: %s | ",Name,AccountNumber);
}

void BankAccount::printAmountOfMoney() {
	printf("remain money: %d\n",AmountOfMoney);
}

void BankAccount::setCurrentTime(char time_string[]) {
	time_t raw_time = time(NULL);
	struct tm* p_time = localtime(&raw_time);
	strftime(time_string, 20, "%Y/%m/%d %H:%M:%S", p_time);
}

void BankAccount::setAccountNumber() {
	AccountNumber = new char[9];
	strcpy(AccountNumber,"12-00-93");
}

BankAccount::~BankAccount() {
	free(Name);
	delete(AccountNumber);
}

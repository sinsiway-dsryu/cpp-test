#include "BankAccount.h" 

void BankAccount::init(char* name) {
	// name 
	Name = (char*)malloc(strlen(name) + 1);
	strcpy(Name, name);
	// amount of money
	AmountOfMoney = 0;
	// account creation time
	setCurrentTime(AccountCreationTime);
}

void BankAccount::deposit(int money) {
	AmountOfMoney += money;
	printf("deposit $%d ",money);
}

void BankAccount::withdraw(int money) {
	AmountOfMoney -= money;
	printf("withdraw $%d ",money);
}

void BankAccount::printAccountInfo() {
	printf("name: %s | create time: %s | money: $%d\n",Name,AccountCreationTime,AmountOfMoney);
}

void BankAccount::printAmountOfMoney() {
	printf(" - remain money: %d\n",AmountOfMoney);
}

void BankAccount::setCurrentTime(char time_string[]) {
	time_t raw_time = time(NULL);
	struct tm* p_time = localtime(&raw_time);
	strftime(time_string, 20, "%Y/%m/%d %H:%M:%S", p_time);
}

BankAccount::~BankAccount() {
	free(Name);
}

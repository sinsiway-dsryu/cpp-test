#include "BankAccount.h"

void bankFeature(int number, BankAccount* bank_account);
void printAccountCreateInfo(BankAccount* bank_account);
void printAccountInfo(BankAccount* bank_account);
void printBankFeatureResult(char* bank_feature_name, int money, BankAccount* bank_account);

int main(int argc, char* argv[]) {

	// input account name
	char input_name[32];
	printf("create accout by input your name : ");
	scanf("%s", input_name);
	// create bank account
	BankAccount bank_account;
	bank_account.init(input_name);
	printAccountCreateInfo(&bank_account);
	// run bank feature 
	int bank_feature_number = 0; 
	do {
	   printf("0. account info\n");
	   printf("1. deposit\n");
	   printf("2. withdraw\n");
	   printf("3. exit\n");
	   printf("choose a feature : ");
	   scanf("%d", &bank_feature_number);
	   bankFeature(bank_feature_number, &bank_account);
	} while(bank_feature_number != 3);

	return 0;
}

void bankFeature(int number, BankAccount* bank_account) {
	switch(number) { 
	case 0: {
		  printAccountInfo(bank_account);
		  break;
		}
	case 1: {
	 	  int deposit = 0;
		  printf("deposit $ : ");
		  scanf("%d", &deposit); 
		  bank_account->deposit(deposit);
		  printBankFeatureResult((char*)"deposit", deposit, bank_account);
		  printAccountInfo(bank_account);
		  break;
		}
	case 2: {
		  int withdraw = 0;
		  printf("withdraw $ : ");
		  scanf("%d", &withdraw);
		  bank_account->withdraw(withdraw);
		  printBankFeatureResult((char*)"withdraw", withdraw, bank_account);
		  printAccountInfo(bank_account);
		  break;
		}
	}
}

void printAccountCreateInfo(BankAccount* bank_account) {
	printf("name: %s | account number: %s\ncreate time: %s\n"
	// ,bank_account.getAccountName()
	// ,bank_account.getAccountNumber()
	// ,bank_account.getAccountCreateTime());
	,bank_account->getAccountName()
	,bank_account->getAccountNumber()
	,bank_account->getAccountCreateTime());
}

void printAccountInfo(BankAccount* bank_account) {
	printf("name: %s | account number: %s | amount of money: %d\n"
	,bank_account->getAccountName()
	,bank_account->getAccountNumber()
	,bank_account->getAmountMoney());
}

void printBankFeatureResult(char* bank_feature_name, int money, BankAccount* bank_account) {
	printf("%s : %d | time : %s\n", bank_feature_name, money, bank_account->getTransactionTime());
}
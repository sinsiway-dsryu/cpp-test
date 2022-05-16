#include "BankAccount.h"

void bankFeature(int number, BankAccount* account);

int main(int argc, char* argv[]) {

	// create bank account
	char input_name[32];
	printf("create accout by input your name : ");
	scanf("%s", input_name);

	BankAccount account;
	account.init(input_name);
	account.printAccountCreateInfo();

	// run bank feature 
	int bank_feature_number = 0; 
	do {
	   printf("0. account info\n");
	   printf("1. deposit\n");
	   printf("2. withdraw\n");
	   printf("3. exit\n");
	   printf("choose a feature : ");
	   scanf("%d", &bank_feature_number);
	   bankFeature(bank_feature_number, &account);
	} while(bank_feature_number != 3);

	return 0;
}

void bankFeature(int number, BankAccount* account) {
	switch(number) { 
	case 0: {
		  account->printAccountInfo();
		  account->printAmountOfMoney();
		  break;
		}
	case 1: {
	 	  int deposit = 0;
		  printf("deposit $ : ");
		  scanf("%d", &deposit); 
		  account->deposit(deposit);
		  account->printAccountInfo();
		  account->printAmountOfMoney();
		  break;
		}
	case 2: {
		  int withdraw = 0;
		  printf("withdraw $ : ");
		  scanf("%d", &withdraw);
		  account->withdraw(withdraw);
		  account->printAccountInfo();
		  account->printAmountOfMoney();
		  break;
		}
	}
}

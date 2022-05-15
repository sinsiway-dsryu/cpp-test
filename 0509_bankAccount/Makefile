app.out : BankAccountMain.o BankAccount.o
	g++ -o app.out BankAccountMain.o BankAccount.o

BankAccountMain.o : BankAccount.h BankAccountMain.cpp
	g++ -c -o BankAccountMain.o BankAccountMain.cpp

BankAccount.o : BankAccount.h BankAccount.cpp
	g++ -c -o BankAccount.o BankAccount.cpp

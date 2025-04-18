#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <iostream>
#include "Transactions.h"
#include "Transactions_List.h"

// Bank account type to be mentioned in derived classes
enum AccountType { SPENDING, RESERVE, GROWTH };


// Define the abstract bank account to be used in Growth_Account, Reserve_Account, and Spending_Account
class Bank_Account {
	// Protected fields that are confidential in nature
protected:
	// Account specific identifiable information
	long long accountNumber;
	std::string userID;
	std::string userPassword;

	// Balance of the account
	float balance;

	// Account owner's identifiable information
	std::string ownerFirstName;
	std::string ownerLastName;
	std::string ownerEmail;
	std::string ownerAddress;
	char ownerGender;
	long long ownerPhoneNumber;

	// Bank account type
	AccountType type;

	// Transactions
	TransactionList transactions;
	void logTransaction(float amount, const std::string& srcDestination);

public:
	// Constructor
	Bank_Account() = default;
	Bank_Account(long long accountNumber, std::string& userID, std::string& userPassword,
		float balance, std::string& ownerFirstName, std::string& ownerLastName,
		std::string& ownerEmail, long long ownerPhoneNumber, char& ownerGender,
		std::string& ownerAddress, AccountType accType);

	// Destructor
	virtual ~Bank_Account() = default;

	// Pure virtual methods (must be implemented by derived classes)
	virtual void deposit(float amount) = 0;
	virtual void withdraw(float amount) = 0;
	virtual void transfer(float amount, Bank_Account& targetAccount) = 0;
	virtual void displayAccountInformation() const = 0;
	virtual void authenticate(std::string& inputUserID, std::string& inputPassword) = 0;
	virtual void updateAccountInformation() = 0;
	virtual AccountType getAccountType() const = 0;

	// Common functionality for the accounts
	float getBalance() const;
	long long getAccountNumber() const;

	// Method for displaying detailed user information
	void displayDetailedAcctInfo() const;

	// User-related methods
	std::string getUserID() const;
	std::string getUserPassword() const;
	std::string getOwnerFirstName() const;
	std::string getOwnerLastName() const;
	std::string getOwnerEmail() const;
	std::string getOwnerAddress() const;
	char getOwnerGender() const;
	long long getOwnerPhoneNumber() const;

	// Setter methods
	void setUserID(const std::string& userID);
	void setUserPassword(const std::string& password);
	void setOwnerFirstName(const std::string& firstName);
	void setOwnerLastName(const std::string& lastName);
	void setOwnerEmail(const std::string& email);
	void setOwnerAddress(const std::string& address);
	void setOwnerGender(char gender);
	void setOwnerPhoneNumber(long long phoneNumber);

	// Specific method for recording the transferring of money
	void recordTransaction(float amount, const std::string& srcDestination) {
		logTransaction(amount, srcDestination);
	}
	virtual void displayTransactions() const;
};

#endif // BANK_ACCOUNT_H

//
// Created by conta on 2/26/2025.
//

#include "../headers/Reserve_Account.h"
#include <iostream>

// Constructor Definition
// The balance to earn interest is a fixed $1.00 minimum, with an Interest Rate / APY of 0.01%.
Reserve_Account::Reserve_Account(long long accountNumber, std::string& userID, std::string& userPassword,
	float balance, std::string& ownerFirstName, std::string& ownerLastName,
	std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
	std::string& ownerAddress, float overdraftLimit)
	: Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName, ownerLastName,
		ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress, AccountType::RESERVE),
	interest(RESERVE), overdraftManager(overdraftLimit) {
}

// Getter for the interest rate (dynamic based on balance)
float Reserve_Account::getInterestRate() const {
	return interest.getRate(balance);
}

// Deposit money into Reserve Account
void Reserve_Account::deposit(float amount) {
	balance += amount;

	// Log the transaction
	logTransaction(amount, "Deposit");

	std::cout << "Deposited $" << amount << " into Reserve Account. New balance: $" << balance << std::endl;
}

// Withdraw money from Reserve Account
void Reserve_Account::withdraw(float amount) {
	// If the user has an account balance higher than the amount they want to withdraw,
	// Subtract the withdrawal amount from the user's account balance
	if (overdraftManager.isWithdrawalAllowed(balance, amount)) {

		// Subtract money from balance
		balance -= amount;

		// Log the transaction
		logTransaction(abs(amount), "Withdrawal");

		// Output Message
		std::cout << "Withdrew $" << amount << " from Reserve Account. New balance: $" << balance << std::endl;
	}

	else
	{
		// Insufficient funds, overdraft protection
		std::cout << "-- Withdrawal denied! Exceeds overdraft limit of $" << overdraftManager.getOverdraftLimit() << std::endl;
		return; // Could cause errors, still debugging
	}
}

// Transfer money from Reserve Account into another account
void Reserve_Account::transfer(float amount, Bank_Account& targetAccount) {
	// Check if withdrawal is allowed based on overdraft limit
	if (!overdraftManager.isWithdrawalAllowed(balance, amount)) {
		// Insufficient funds, overdraft protection
		std::cout << "-- Transfer denied! Exceeds overdraft limit of $" << overdraftManager.getOverdraftLimit() << std::endl;

		// Log Error
		logTransaction(0, "Failed transfer due to insufficient funds"); 
		return;
	}

	// Perform withdrawal
	balance -= amount;

	// Deposit into target account
	targetAccount.deposit(amount);

	// Log successful transactions
	logTransaction(-amount, "Transfer to Account " + std::to_string(targetAccount.getAccountNumber()));
	targetAccount.recordTransaction(amount, "Transfer from Account " + std::to_string(accountNumber));

	std::cout << "Transferred $" << amount << " from Reserve Account to account #" << targetAccount.getAccountNumber() << std::endl;
}

// Display information for the Reserve Account
void Reserve_Account::displayAccountInformation() const {
	std::cout << "Reserve Account Information:\n";

	// Account Number
	std::cout << "Account Number: " << accountNumber << std::endl;

	// Account Owner
	std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;

	// Account Balance
	std::cout << "Balance: $" << balance << std::endl;

	// Interest Rate %
	std::cout << "\nInterest Rate: " << getInterestRate() << "%" << std::endl;

	// Simple Interest Rate
	std::cout << "Account Balance Next Year: $" << balance + interest.calculateInterest(balance, 1) << std::endl;

	// Compound Interest Rate
	std::cout << "Account Balance in 5 Years (Compound Interest): $"
		<< interest.calculateCompoundInterest(balance, 5, 12) << std::endl;
}

// Authenticate user
void Reserve_Account::authenticate(std::string& inputUserID, std::string& inputPassword) {
	if (inputUserID == userID && inputPassword == userPassword) {
		std::cout << "Authentication successful." << std::endl;
	}
	else {
		std::cout << "Authentication failed." << std::endl;
	}
}

// Update Account Information (needs to be implemented)
void Reserve_Account::updateAccountInformation() {
	std::cout << "Update Account Information:" << std::endl;
}
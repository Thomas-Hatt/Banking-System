//
// Created by conta on 2/26/2025.
//

#include "../headers/Spending_Account.h"
#include <iostream>

// Constructor Definition
Spending_Account::Spending_Account(long long accountNumber, std::string& userID, std::string& userPassword,
	float balance, std::string& ownerFirstName, std::string& ownerLastName,
	std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
	std::string& ownerAddress, float overdraftLimit)
	: Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName, ownerLastName,
		ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress, AccountType::SPENDING), overdraftManager(overdraftLimit)
{
}

// Deposit money into Spending Account
void Spending_Account::deposit(float amount) {
	balance += amount;

	// Log the transaction
	logTransaction(amount, "Deposit");

	std::cout << "Deposited $" << amount << " into Spending Account. New balance: $" << balance << std::endl;
}

// Withdraw money from Spending Account
void Spending_Account::withdraw(float amount) {
	// If the user has an account balance higher than the amount they want to withdraw,
	// Subtract the withdrawal amount from the user's account balance
	if (overdraftManager.isWithdrawalAllowed(balance, amount)) {

		// Subtract money from balance
		balance -= amount;

		// Log the transaction
		logTransaction(-amount, "Withdrawal");

		// Output Message
		std::cout << "Withdrew $" << amount << " from Spending Account. New balance: $" << balance << std::endl;
	}

	else
	{
		// Insufficient funds, overdraft protection
		std::cout << "-- Withdrawal denied! Exceeds overdraft limit of $" << overdraftManager.getOverdraftLimit() << std::endl;
		return; // Could cause errors, still debugging
	}
}

// Transfer money from Spending Account into another account
void Spending_Account::transfer(float amount, Bank_Account& targetAccount) {
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

	std::cout << "Transferred $" << amount << " from Reserve Account to account " << targetAccount.getAccountNumber() << std::endl;
}

// Display information for the Spending Account
void Spending_Account::displayAccountInformation() const {
	std::cout << "Spending Account Information:" << std::endl;
	std::cout << "Account Number: " << accountNumber << std::endl;
	std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;
	std::cout << "Balance: $" << balance << std::endl;
}

// Authenticate user
void Spending_Account::authenticate(std::string& inputUserID, std::string& inputPassword) {
	if (inputUserID == userID && inputPassword == userPassword) {
		std::cout << "Authentication successful." << std::endl;
	}
	else {
		std::cout << "Authentication failed." << std::endl;
	}
}

// Update Account Information (needs to be implemented)
void Spending_Account::updateAccountInformation() {
	std::cout << "Update Account Information:" << std::endl;
}
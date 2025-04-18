//
// Created by conta on 2/26/2025.
//

#include "../headers/Growth_Account.h"
#include <iostream>

// Constructor Definition
// - For balances between $1.00 and $2,499.99, the Interest Rate / APY is 0.02%.
// - For balances at $2, 500.00 and above, the Interest Rate / APY is 0.03 % .
Growth_Account::Growth_Account(long long accountNumber, std::string& userID, std::string& userPassword,
	float balance, std::string& ownerFirstName, std::string& ownerLastName,
	std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
	std::string& ownerAddress, float overdraftLimit)
	: Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName, ownerLastName,
		ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress, AccountType::GROWTH),
	interest(GROWTH), overdraftManager(overdraftLimit)
{
}


// Getter for the interest rate (dynamic based on balance)
float Growth_Account::getInterestRate() const {
	return interest.getRate(balance);
}

// Deposit money into Growth Account
void Growth_Account::deposit(float amount) {
	balance += amount;

	// Log the transaction
	logTransaction(amount, "Deposit");

	std::cout << "Deposited $" << amount << " into Growth Account. New balance: $" << balance << std::endl;
}

// Withdraw money from Growth Account
void Growth_Account::withdraw(float amount) {
	// If the user has an account balance higher than the amount they want to withdraw,
	// Subtract the withdrawal amount from the user's account balance
	if (overdraftManager.isWithdrawalAllowed(balance, amount)) {

		// Subtract money from balance
		balance -= amount;

		// Log the transaction
		logTransaction(abs(amount), "Withdrawal");

		std::cout << "Withdrew $" << amount << " from Growth Account. New balance: $" << balance << std::endl;
	}

	else
	{
		// Insufficient funds, overdraft protection
		std::cout << "-- Withdrawal denied! Exceeds overdraft limit of $" << overdraftManager.getOverdraftLimit() << std::endl;
		return; // Could cause errors, still debugging
	}
}

// Transfer money from Growth Account into another account
void Growth_Account::transfer(float amount, Bank_Account& targetAccount) {
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

	std::cout << "Transferred $" << amount << " from Growth Account to account #" << targetAccount.getAccountNumber() << std::endl;
}

// Display information for the Growth Account
void Growth_Account::displayAccountInformation() const {
	std::cout << "Growth Account Information:\n";

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
void Growth_Account::authenticate(std::string& inputUserID, std::string& inputPassword) {
	if (inputUserID == userID && inputPassword == userPassword) {
		std::cout << "Authentication successful." << std::endl;
	}
	else {
		std::cout << "Authentication failed." << std::endl;
	}
}

// Update Account Information (needs to be implemented)
void Growth_Account::updateAccountInformation() {
	std::cout << "Update Account Information:" << std::endl;
}
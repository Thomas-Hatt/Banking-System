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
	std::string& ownerAddress, float interestRate)
	: Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName, ownerLastName,
		ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress, AccountType::GROWTH),

	interestRate(interestRate)
{
}


// Getter for the interest rate (dynamic based on balance)
float Growth_Account::getInterestRate() const {
	// User must have a balance of $1.00 or more to return interestRate
	if (balance >= 1.0f)
	{
		// Return 0.01%
		return interestRate;
	}
	else
	{
		return 0.0f;
	}
}

// Deposit money into Growth Account
void Growth_Account::deposit(float amount) {
	balance += amount;
	std::cout << "Deposited $" << amount << " into Growth Account. New balance: $" << balance << std::endl;
}

// Withdraw money from Growth Account
void Growth_Account::withdraw(float amount) {
	// If the user has an account balance higher than the amount they want to withdraw,
	// Subtract the withdrawal amount from the user's account balance
	if (balance >= amount) {
		balance -= amount;
		std::cout << "Withdrew $" << amount << " from Growth Account. New balance: $" << balance << std::endl;
	}

	// Insufficient funds
	else
	{
		std::cout << "Insufficient funds for withdrawal." << std::endl;
	}
}

// Transfer money from Growth Account into another account
void Growth_Account::transfer(float amount, Bank_Account& targetAccount) {
	// If the user has an account balance higher than the amount they want to transfer,
	// Subtract the transfer amount from the user's account balance
	if (balance >= amount) {
		balance -= amount;
		// Deposit the money
		targetAccount.deposit(amount);

		// Confirm that the money was transferred (needs more robust error handling)
		std::cout << "Transfered $" << amount << " from Growth Account to account "
			<< targetAccount.getAccountNumber() << std::endl;
	}

	// Insufficient funds
	else
	{
		std::cout << "Insufficient funds for transfer." << std::endl;
	}
}

// Display information for the Growth Account
void Growth_Account::displayAccountInformation() const {
	std::cout << "Growth Account Information:" << std::endl;
	std::cout << "Account Number: " << accountNumber << std::endl;
	std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;
	std::cout << "Balance: $" << balance << std::endl;
	std::cout << "Interest Rate: $" << getInterestRate() << "%" << std::endl;

	// If the Interest Rate is greater than 0%, display next year's account balance
	if (interestRate > 0.0f)
	{
		// Simple Interest = P * r * t
		// P is the Principal amount
		// r is the Annual interest rate
		// t is the time period in years
		// Example calculation: (1000 * (0.01 / 100)) + 1000
		float simpleInterestReturn = (balance * (interestRate / 100)) + balance;
		std::cout << "Account Balance Next Year: $" << simpleInterestReturn << std::endl;
	}
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
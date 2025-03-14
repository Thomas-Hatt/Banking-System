//
// Created by conta on 2/26/2025.
//

#include "../headers/Spending_Account.h"
#include <iostream>

// Constructor Definition
Spending_Account::Spending_Account(long long accountNumber, std::string& userID, std::string& userPassword,
	float balance, std::string& ownerFirstName, std::string& ownerLastName,
	std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
	std::string& ownerAddress)
	: Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName, ownerLastName,
		ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress, AccountType::SPENDING)
{
}

// Deposit money into Spending Account
void Spending_Account::deposit(float amount) {
	balance += amount;
	std::cout << "Deposited $" << amount << " into Spending Account. New balance: $" << balance << std::endl;
}

// Withdraw money from Spending Account
void Spending_Account::withdraw(float amount) {
	// If the user has an account balance higher than the amount they want to withdraw,
	// Subtract the withdrawal amount from the user's account balance
	if (balance >= amount) {
		balance -= amount;
		std::cout << "Withdrew $" << amount << " from Spending Account. New balance: $" << balance << std::endl;
	}

	// Insufficient funds
	else
	{
		std::cout << "Insufficient funds for withdrawal." << std::endl;
	}
}

// Transfer money from Spending Account into another account
void Spending_Account::transfer(float amount, Bank_Account& targetAccount) {
	// If the user has an account balance higher than the amount they want to transfer,
	// Subtract the transfer amount from the user's account balance
	if (balance >= amount) {
		balance -= amount;
		// Deposit the money
		targetAccount.deposit(amount);

		// Confirm that the money was transferred (needs more robust error handling)
		std::cout << "Transfered $" << amount << " from Spending Account to account "
			<< targetAccount.getAccountNumber() << std::endl;
	}

	// Insufficient funds
	else
	{
		std::cout << "Insufficient funds for transfer." << std::endl;
	}
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
#include "../headers/Bank_Account.h"
#include <iostream>
#include <string>

// Constructor definition
Bank_Account::Bank_Account(long long accountNumber, std::string& userID, std::string& userPassword,
	float balance, std::string& ownerFirstName, std::string& ownerLastName,
	std::string& ownerEmail, long long ownerPhoneNumber, char& ownerGender,
	std::string& ownerAddress, AccountType accType)
	:
	accountNumber(accountNumber), userID(userID), userPassword(userPassword), balance(balance),
	ownerFirstName(ownerFirstName), ownerLastName(ownerLastName), ownerEmail(ownerEmail),
	ownerPhoneNumber(ownerPhoneNumber), ownerGender(ownerGender), ownerAddress(ownerAddress), type(accType) {
}


// Implement getter methods
long long Bank_Account::getAccountNumber() const {
	return accountNumber;
}

std::string Bank_Account::getUserID() const {
	return userID;
}

std::string Bank_Account::getUserPassword() const {
	return userPassword;
}

float Bank_Account::getBalance() const {
	return balance;
}

std::string Bank_Account::getOwnerFirstName() const {
	return ownerFirstName;
}

std::string Bank_Account::getOwnerLastName() const {
	return ownerLastName;
}

std::string Bank_Account::getOwnerEmail() const {
	return ownerEmail;
}

std::string Bank_Account::getOwnerAddress() const {
	return ownerAddress;
}

char Bank_Account::getOwnerGender() const {
	return ownerGender;
}

long long Bank_Account::getOwnerPhoneNumber() const {
	return ownerPhoneNumber;
}

void Bank_Account::logTransaction(float amount, const std::string& srcDestination) {
	std::string txnID = "TXN" + std::to_string(generateTransactionNumber());
	transactions.addTransaction(txnID, amount, srcDestination);
}

void Bank_Account::displayTransactions() const {
	transactions.displayAllTransactions();
}

// Detailed Account Information
void Bank_Account::displayDetailedAcctInfo() const
{
	std::cout << "\n-- Detailed User Information --:" << std::endl;
	std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;
	std::cout << "Gender: " << ownerGender << std::endl;
	std::cout << "Phone Number: " << ownerPhoneNumber << std::endl;
	std::cout << "Email Address: " << ownerEmail << std::endl;
	std::cout << "Owner's Physical Address: " << ownerAddress << std::endl;
	
	std::cout << "\nUser ID: " << userID << std::endl;
	std::cout << "Password: " << userPassword << std::endl;
}

// -------------------------------------------------------------------

// Implement Setter Methods
void Bank_Account::setUserPassword(const std::string& password) {
	userPassword = password;
}

void Bank_Account::setOwnerFirstName(const std::string& firstName) {
	ownerFirstName = firstName;
}

void Bank_Account::setOwnerLastName(const std::string& lastName) {
	ownerLastName = lastName;
}

void Bank_Account::setOwnerEmail(const std::string& email) {
	ownerEmail = email;
}

void Bank_Account::setOwnerAddress(const std::string& address) {
	ownerAddress = address;
}

void Bank_Account::setOwnerGender(char gender) {
	ownerGender = gender;
}

void Bank_Account::setOwnerPhoneNumber(long long phoneNumber) {
	ownerPhoneNumber = phoneNumber;
}
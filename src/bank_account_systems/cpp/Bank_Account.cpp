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
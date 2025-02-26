#include "Bank_Account.h"
#include <iostream>
#include <string>

// Constructor definition
Bank_Account::Bank_Account(int accountNumber, const std::string &userID, const std::string &userPassword,
                           float balance, const std::string &ownerFirstName, const std::string &ownerLastName,
                           const std::string &ownerEmail, const std::string &ownerAddress, char ownerGender,
                           int ownerPhoneNumber)
                           :
                           accountNumber(accountNumber), userID(userID), userPassword(userPassword), balance(balance),
                           ownerFirstName(ownerFirstName), ownerLastName(ownerLastName), ownerEmail(ownerEmail),
                           ownerAddress(ownerAddress), ownerGender(ownerGender), ownerPhoneNumber(ownerPhoneNumber) {}

// Implement getter methods
int Bank_Account::getAccountNumber() const {
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

int Bank_Account::getOwnerPhoneNumber() const {
  return ownerPhoneNumber;
}
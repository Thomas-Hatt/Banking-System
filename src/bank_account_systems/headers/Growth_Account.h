//
// Created by conta on 2/26/2025.
//

#ifndef GROWTH_ACCOUNT_H
#define GROWTH_ACCOUNT_H

#include "../headers/Bank_Account.h"
#include <iostream>

// Derived Class: Growth Account
class Growth_Account : public Bank_Account {
private:
	const float interestRate;
public:
	Growth_Account(long long accountNumber, std::string& userID, std::string& userPassword,
		float balance, std::string& ownerFirstName, std::string& ownerLastName,
		std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
		std::string& ownerAddress, float interestRate);

	// Getters
	float getInterestRate() const;

	// Override pure virtual functions
	void deposit(float amount) override;
	void withdraw(float amount) override;
	void transfer(float amount, Bank_Account& targetAccount) override;
	void displayAccountInformation() const override;
	void authenticate(std::string& inputUserID, std::string& inputPassword) override;
	void updateAccountInformation() override;
	AccountType getAccountType() const override { return type; }
};

#endif //GROWTH_ACCOUNT_H

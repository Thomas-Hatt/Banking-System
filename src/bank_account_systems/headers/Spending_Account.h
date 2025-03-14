//
// Created by conta on 2/26/2025.
//

#ifndef SPENDING_ACCOUNT_H
#define SPENDING_ACCOUNT_H

#include <iostream>
#include <string>
#include "../headers/Bank_Account.h"

// Derived account: Spending Account
class Spending_Account : public Bank_Account {
public:
	Spending_Account(long long accountNumber, std::string& userID, std::string& userPassword,
		float balance, std::string& ownerFirstName, std::string& ownerLastName,
		std::string& ownerEmail, long long ownerPhoneNumber, char ownerGender,
		std::string& ownerAddress);

	// Override pure virtual functions
	void deposit(float amount) override;
	void withdraw(float amount) override;
	void transfer(float amount, Bank_Account& targetAccount) override;
	void displayAccountInformation() const override;
	void authenticate(std::string& inputUserID, std::string& inputPassword) override;
	void updateAccountInformation() override;
	AccountType getAccountType() const override { return type; }
};

#endif //SPENDING_ACCOUNT_H

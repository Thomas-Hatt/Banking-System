//
// Created by conta on 2/26/2025.
//

#ifndef GROWTH_ACCOUNT_H
#define GROWTH_ACCOUNT_H

#include <iostream>

// Derived Class: Growth Account
class Growth_Account : public Bank_Account {
private:
    float interestRate;
public:
    Growth_Account(int accountNumber, const std::string &userID, const std::string &userPassword,
                    float balance, const std::string &ownerFirstName, const std::string &ownerLastName,
                    const std::string &ownerEmail, int ownerPhoneNumber, char ownerGender,
                    const std::string &ownerAddress, float interestRate);

    // Override pure virtual functions
    void deposit(float amount) override;
    void withdraw(float amount) override;
    void transfer(float amount, Bank_Account &targetAccount) override;
    void displayAccountInformation() const override;
    void authenticate(std::string &inputUserID, std::std::string &inputPassword) override;
    void updateAccountInformation() override;
};



#endif //GROWTH_ACCOUNT_H

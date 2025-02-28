//
// Created by conta on 2/26/2025.
//

#ifndef RESERVE_ACCOUNT_H
#define RESERVE_ACCOUNT_H
#include "../cpp/Bank_Account.cpp"
#include <iostream>

// Derived account: Reserve Account
class Reserve_Account : public Bank_Account {
private:
    const float interestRate;
public:
    Reserve_Account(int accountNumber, std::string &userID, std::string &userPassword,
                    float balance, std::string &ownerFirstName, std::string &ownerLastName,
                    std::string &ownerEmail, int ownerPhoneNumber, char ownerGender,
                    std::string &ownerAddress, float interestRate);

    // Getters
    float getInterestRate() const;

    // Override pure virtual functions
    void deposit(float amount) override;
    void withdraw(float amount) override;
    void transfer(float amount, Bank_Account &targetAccount) override;
    void displayAccountInformation() const override;
    void authenticate(std::string &inputUserID, std::string &inputPassword) override;
    void updateAccountInformation() override;
};




#endif //RESERVE_ACCOUNT_H

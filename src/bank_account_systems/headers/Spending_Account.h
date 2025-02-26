//
// Created by conta on 2/26/2025.
//

#ifndef SPENDING_ACCOUNT_H
#define SPENDING_ACCOUNT_H

#include <iostream>
#include <string>
#include <Bank_Account.h>

class Spending_Account : public Bank_Account {

public:
    Spending_Account(int accountNumber, const std::string &userID, const std::string &userPassword,
                    float balance, const std::string &ownerFirstName, const std::string &ownerLastName,
                    const std::string &ownerEmail, int ownerPhoneNumber, char ownerGender,
                    const std::string &ownerAddress);

    // Override pure virtual functions
    void deposit(float amount) override;
    void withdraw(float amount) override;
    void transfer(float amount, Bank_Account &targetAccount) override;
    void displayAccountInformation() const override;
    void authenticate(std::string &inputUserID, std::std::string &inputPassword) override;
    void updateAccountInformation() override;
};



#endif //SPENDING_ACCOUNT_H

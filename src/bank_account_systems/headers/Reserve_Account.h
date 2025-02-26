//
// Created by conta on 2/26/2025.
//

#ifndef RESERVE_ACCOUNT_H
#define RESERVE_ACCOUNT_H

#include <iostream>

// Derived account: Reserve Account
class Reserve_Account : public Bank_Account {
    private:
      // The balance to earn interest is a fixed $1.00 minimum, with an Interest Rate / APY of 0.01%.
      const float interestRate;
    public:
      Reserve_Account(int accountNumber, const std::string &userID, const std::string &userPassword,
                      float balance, const std::string &ownerFirstName, const std::string &ownerLastName,
                      const std::string &ownerEmail, int ownerPhoneNumber, char ownerGender,
                      const std::string &ownerAddress, float interestRate);

      // Getters
      float getInterestRate() const;

      // Override pure virtual functions
      void deposit(float amount) override;
      void withdraw(float amount) override;
      void transfer(float amount, Bank_Account &targetAccount) override;
      void displayAccountInformation() const override;
      void authenticate(std::string &inputUserID, std::std::string &inputPassword) override;
      void updateAccountInformation() override;
};



#endif //RESERVE_ACCOUNT_H

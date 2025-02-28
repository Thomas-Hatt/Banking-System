#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <iostream>

// Define the abstract bank account to be used in Growth_Account, Reserve_Account, and Spending_Account
class Bank_Account {
    // Protected fields that are confidential in nature
    protected:
      // Account specific identifiable information
      int accountNumber;
      std::string userID;
      std::string userPassword;

      // Balance of the account
      float balance;

      // Account owner's identifiable information
      std::string ownerFirstName;
      std::string ownerLastName;
      std::string ownerEmail;
      std::string ownerAddress;
      char ownerGender;
      int ownerPhoneNumber;

      public:
        // Constructor
        Bank_Account() = default;
        Bank_Account(int accountNumber, std::string &userID, std::string &userPassword,
                     float balance, std::string &ownerFirstName, std::string &ownerLastName,
                     std::string &ownerEmail, std::string &ownerAddress, char &ownerGender,
                     int ownerPhoneNumber);

        // Destructor
        virtual ~Bank_Account() = default;

        // Pure virtual functions (must be implemented by derived classes)
        virtual void deposit(float amount) = 0;
        virtual void withdraw(float amount) = 0;
        virtual void transfer(float amount, Bank_Account &targetAccount) = 0;
        virtual void displayAccountInformation() const = 0;
        virtual void authenticate(std::string &inputUserID, std::tring &inputPassword) = 0;
        virtual void updateAccountInformation() = 0;

        // Common functionality for the accounts
        float getBalance() const;
        int getAccountNumber() const;

        // User-related methods
        std::string getUserID() const;
        std::string getUserPassword() const;
        std::string getOwnerFirstName() const;
        std::string getOwnerLastName() const;
        std::string getOwnerEmail() const;
        std::string getOwnerAddress() const;
        char getOwnerGender() const;
        int getOwnerPhoneNumber() const;

        // Operator overloading for deposit, withdraw, and transfer
};

#endif // BANK_ACCOUNT_H

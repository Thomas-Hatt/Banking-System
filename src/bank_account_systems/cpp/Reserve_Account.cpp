//
// Created by conta on 2/26/2025.
//

#include "Reserve_Account.h"
#include <iostream>

// Constructor Definition
// The balance to earn interest is a fixed $1.00 minimum, with an Interest Rate / APY of 0.01%.
Reserve_Account::Reserve_Account(int accountNumber, const std::string &userID, const std::string &userPassword,
                      float balance, const std::string &ownerFirstName, const std::string &ownerLastName,
                      const std::string &ownerEmail, int ownerPhoneNumber, char ownerGender,
                      const std::string &ownerAddress, float interestRate)
                      : Bank_Account(accountNumber, userID, userPassword, balance, ownerFirstName,
                      ownerLastName, ownerEmail, ownerPhoneNumber, ownerGender, ownerAddress), interestRate(0.01f)
{}

// Getter for the interest rate (dynamic based on balance)
float Reserve_Account::getInterestRate() const {
  // User must have a balance of $1.00 or more to return interestRate
  if (balance >= 1.0f)
    {
      // Return 0.01%
      return interestRate;
    }
  else
    {
      return 0.0f;
    }
}

// Deposit money into Reserve Account
void Reserve_Account::deposit(float amount) {
      balance += amount;
      std::cout << "Deposited $" << amount << " into Reserve Account. New balance: $" << balance << std::endl;
  }

  // Withdraw money from Reserve Account
 void Reserve_Account::withdraw(float amount) {
   // If the user has an account balance higher than the amount they want to withdraw,
   // Subtract the withdrawal amount from the user's account balance
   if (balance >= amount) {
     balance -= amount;
     std::cout << "Withdrew $" << amount << " from Reserve Account. New balance: $" << balance << std::endl;
   }

   // Insufficient funds
   else
   {
       std::cout << "Insufficient funds for withdrawal." << std::endl;
   }
 }

 // Transfer money from Reserve Account into another account
 void Reserve_Account::transfer(float amount, Bank_Account &targetAccount) {
    // If the user has an account balance higher than the amount they want to transfer,
    // Subtract the transfer amount from the user's account balance
    if (balance >= amount) {
        balance -= amount;
        // Deposit the money
        targetAccount.deposit(amount);

        // Confirm that the money was transferred (needs more robust error handling)
        std::cout << "Transfered $" << amount << " from Reserve Account to account "
                  << targetAccount.getAccountNumber() << std::endl;
        }

    // Insufficient funds
    else
    {
        std::cout << "Insufficient funds for transfer." << std::endl;
    }
 }

 // Display information for the Reserve Account
 void Reserve_Account::displayAccountInformation() const {
   std::cout << "Reserve Account Information:" << std::endl;
   std::cout << "Account Number: " << accountNumber << std::endl;
   std::cout << "Owner: " << ownerFirstName << " " << ownerLastName << std::endl;
   std::cout << "Balance: $" << balance << std::endl;
   std::cout << "Interest Rate: $" << getInterestRate() << "%" << std::endl;

   // If the Interest Rate is greater than 0%, display next year's account balance
   if (interestRate > 0.0f)
     {
     // Simple Interest = P * r * t
     // P is the Principal amount
     // r is the Annual interest rate
     // t is the time period in years
     // Example calculation: (1000 * (0.01 / 100)) + 1000
     float simpleInterestReturn = (balance * (interestRate / 100)) + balance;
     std::cout << "Account Balance Next Year: $" << simpleInterestReturn << std::endl;
     }
 }

 // Authenticate user
 bool Reserve_Account::authenticate(std::string &inputUserID, std::std::string &inputPassword) const {
   return (inputUserID == userID && inputPassword == userPassword);
 }

 // Update Account Information (needs to be implemented)
 void Reserve_Account::updateAccountInformation() {
   std::cout << "Update Account Information:" << std::endl;
 }
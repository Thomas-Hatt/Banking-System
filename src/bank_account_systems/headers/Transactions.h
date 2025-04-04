#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <string>
#include <iostream>

class Transaction {
private:
    // Unique ID of the transaction
    std::string transactionID;

    // Source/destination of the transaction (e.g., Spending, Growth, Reserve, Store)
    std::string srcDestination;

    // Amount involved in the transaction
    float amount;

public:
    // Constructor
    Transaction(const std::string& id, float amt, const std::string& src);

    // Method to display transaction details
    void displayTransactionDetails() const;

    // Getters for accessing transaction fields
    std::string getTransactionID() const;
    std::string getSrcDestination() const;
    float getAmount() const;
};

#endif // TRANSACTION_H
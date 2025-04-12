#include "../headers/Transactions.h"

#include <stdexcept> // For exceptions

Transaction::Transaction(const std::string& id, float amt, const std::string& src) {
	if (id.empty()) {
		throw std::invalid_argument("Transaction ID cannot be empty.");
	}
	if (amt < 0) {
		throw std::invalid_argument("Amount cannot be negative.");
	}
	if (src.empty()) {
		throw std::invalid_argument("Source/Destination cannot be empty.");
	}

	transactionID = id;
	amount = amt;
	srcDestination = src;
}

// Displays transaction details
/* For example:
*   Transaction ID: TXN-5901283512
	Source/Destination: Deposit
	Amount: $581
*/
void Transaction::displayTransactionDetails() const {
	std::cout << "\nTransaction ID: " << transactionID << std::endl;
	std::cout << "Source/Destination: " << srcDestination << std::endl;
	std::cout << "Amount: $" << amount << std::endl;
}

// Getter for transaction ID
std::string Transaction::getTransactionID() const
{
	return transactionID;
}

// Getter for source destination
std::string Transaction::getSrcDestination() const
{
	return srcDestination;
}

// Getter for amount of money
float Transaction::getAmount() const
{
	return amount;
}
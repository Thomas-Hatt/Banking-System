#ifndef TRANSACTIONSLIST_H
#define TRANSACTIONSLIST_H

#include "Transactions.h"
#include <random>
#include <iostream>

/*
* The purpose of this class is to create and display transactions made from a bank account by the user
*/

// Generate a random 10-digit integer to be used in the transaction number
// For example, TXN-5186102674
inline long long generateTransactionNumber() {
	std::random_device rand;
	std::mt19937 gen(rand());
	std::uniform_int_distribution<long long> dis(1000000000LL, 9999999999LL);
	return dis(gen);
}

// Linked list node structure for transactions
struct TransactionNode {
	Transaction* transaction;
	TransactionNode* next;

	// Constructor to initialize a node
	TransactionNode(Transaction* txn) : transaction(txn), next(nullptr) {}
};

class TransactionList {
private:
	// Pointer to the first transaction node
	TransactionNode* head;

public:
	// Constructor to initialize an empty list
	TransactionList() : head(nullptr) {}

	// Destructor to delete all nodes and transactions
	~TransactionList() {
		TransactionNode* current = head;
		while (current) {
			TransactionNode* next = current->next;

			// Delete the transaction object
			delete current->transaction;

			// Delete the node
			delete current;
			current = next;
		}
	}

	void addTransaction(const std::string& txnID, float amount, const std::string& srcDestination) {
		try {
			// Create a new Transaction object
			Transaction* newTransaction = new Transaction(txnID, amount, srcDestination);

			// Create a new TransactionNode and add it to the list
			TransactionNode* newNode = new TransactionNode(newTransaction);

			// Add to the linked list
			if (!head) {
				head = newNode;
			}
			else {
				TransactionNode* temp = head;
				while (temp->next) temp = temp->next;
				temp->next = newNode;
			}
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Error adding transaction: " << e.what() << std::endl;
		}
	}

	// Display all transactions in the list
	void displayAllTransactions() const {
		if (!head) {
			// If there are no transactions available, display a message and return
			std::cout << "No transactions available." << std::endl;
			return;
		}

		// Loop through all transactions and display the details
		TransactionNode* current = head;
		while (current) {
			current->transaction->displayTransactionDetails();
			current = current->next;
		}
	}
};

#endif // TRANSACTIONLIST_H
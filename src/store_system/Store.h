//
// Created by conta on 2/26/2025.
//

#ifndef STORE_H
#define STORE_H

#include "items/headers/product.h"
#include <string>
#include <iostream>
#include "../bank_account_systems/headers/Bank_Account.h"

class Store {
public:
	// Constructor
	Store();

	// Update the product details to include a new name, price, and quantity
	void updateProductDetails(const std::string& productName, float newPrice, int newQuantity);

	// Add the product to the user's cart
	void addToCart(const std::string& productName, int quantity);

	// Checkout function
	void checkout();

	// Display product catalog
	void displayCatalog() const;

	// Display the user's cart
	void displayCart();

	// Clear the user's cart
	void clearCart();

	// Setter for current bank account
	void setCurrentAccount(Bank_Account* account);

private:
	// Initialize catalog
	void initializeCatalog();

	// 100 max products in the store, as an example. Will be updated nearing code completion
	static const int MAX_PRODUCTS = 100;

	// Product objects, catalog array has a max size as 100
	Product catalog[MAX_PRODUCTS];

	// Product objects, cart array has a max size as 100
	Product cart[MAX_PRODUCTS];

	// Size of the catalog
	int catalogSize;

	// Size of the cart
	int cartSize;

	// Add a pointer to the current account
	Bank_Account* currentAccount;

	// Calculate total cost
	float calculateTotalCost() const;

	// Helper function to find product in catalog by name
	int findProductIndex(const std::string& productName) const;
};

#endif //STORE_H
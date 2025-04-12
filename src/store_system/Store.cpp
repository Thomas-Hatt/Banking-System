//
// Created by conta on 2/26/2025.
//

#include "Store.h"
#include <iostream>

// Constructor
Store::Store() : catalogSize(0), cartSize(0) {
	initializeCatalog();
}

void Store::initializeCatalog() {
	// Add items (product name, price, and quantity)
	catalog[0] = Product("Bread", 2.50f, 100);
	catalog[1] = Product("Milk", 3.00f, 90);
	catalog[2] = Product("Chicken", 5.50f, 100);
	catalog[3] = Product("Cereal", 3.50f, 100);
	catalog[4] = Product("Water", 1.50f, 125);

	// Set the catalog size to the number of products added
	catalogSize = 5;
}

// Update product details
void Store::updateProductDetails(const std::string& productName, float newPrice, int newQuantity) {
	// Create a variable to track if a product was found
	bool found = false;

	// Loop through the catalog
	for (int i = 0; i < catalogSize; ++i) {
		if (catalog[i].getProductName() == productName) {

			// Ensure price and quantity are positive numbers
			if (newPrice < 0 || newQuantity < 0) {
				std::cout << "Error: Price/quantity cannot be negative.\n";
				return;
			}

			// Set the new price
			catalog[i].setPrice(newPrice);

			// Set the new quantity
			catalog[i].setQuantity(newQuantity);

			found = true;
			break;
		}
	}

	// Error: Product not found
	if (!found) {
		std::cout << "Product not found." << std::endl;
	}
}

// Add item to shopping cart
void Store::addToCart(const std::string& productName, int quantity) {

	// Ensure quantity is positive
	if (quantity <= 0) {
		std::cout << "Error: Quantity must be positive.\n";
		return;
	}

	bool found = false;
	for (int i = 0; i < catalogSize; ++i) {
		// Ensure the product name exists
		if (catalog[i].getProductName() == productName) {
			found = true;

			// Ensure there is enough stock
			if (catalog[i].getQuantity() < quantity) {
				std::cout << "Insufficient stock." << std::endl;
				return;
			}

			// Ensure the cartSize is not greater than the max products
			if (cartSize < MAX_PRODUCTS) {
				cart[cartSize] = catalog[i];
				cart[cartSize].setQuantity(quantity);
				cartSize++;
				catalog[i].setQuantity(catalog[i].getQuantity() - quantity);
			}

			// Error: cart is full
			else {
				std::cout << "Cart is full!" << std::endl;
			}

			// Success message
			std::cout << "\nSuccessfully added " << quantity << " " << catalog[i].getProductName() << " To your cart!" << std::endl;
			std::cout << "Total " << catalog[i].getProductName() << " Remaining: " << catalog[i].getQuantity() << std::endl;

			// Exit after handling
			return;
		}
	}
	if (!found) {
		std::cout << "Product not found." << std::endl;
	}
}

// Checkout
void Store::checkout(float& accountBalance) {

	// Initialize empty confirmation character
	char userConfirmCheckout;

	// Ensure cart size isn't 0
	if (cartSize == 0) {
		std::cout << "Cart is empty." << std::endl;
		return;
	}

	// Create a variable for the total cost
	float totalCost = 0;

	// Loop through the cart and get the total price of everything
	for (int i = 0; i < cartSize; ++i) {
		totalCost += cart[i].getPrice() * cart[i].getQuantity();
	}

	// Get user confirmation
	do {
		std::cout << "Are you sure you are ready for checkout? Your current total is $" << totalCost << ". Y/N: ";
		std::cin >> userConfirmCheckout;

		// Convert to uppercase to allow lowercase input
		userConfirmCheckout = std::toupper(userConfirmCheckout);

		if (userConfirmCheckout != 'Y' && userConfirmCheckout != 'N') {
			std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << std::endl;
		}

	} while (userConfirmCheckout != 'Y' && userConfirmCheckout != 'N');

	// Ensure the total cost is not greater than the amount of money the user has
	if (accountBalance >= totalCost) {

		// Subtract the money from the account
		accountBalance -= totalCost;

		// Output message
		std::cout << "Checkout successful! Total cost: $" << totalCost << std::endl;

		// Reset cartSize
		cartSize = 0;
	}

	// Error: Insufficient money
	else {
		std::cout << "Checkout failed! You do not have enough money. Total cost: $" << totalCost << std::endl;
		return;
	}
}

// Display the catalog
void Store::displayCatalog() const {
	std::cout << "----------------------------" << std::endl;
	std::cout << "Product Catalog:" << std::endl;
	for (int i = 0; i < catalogSize; ++i) {
		catalog[i].displayProductInfo();
		std::cout << std::endl;
	}
}

// Display shopping cart
void Store::displayCart() const {
	std::cout << "----------------------------" << std::endl;
	std::cout << "Shopping Cart:" << std::endl;
	for (int i = 0; i < cartSize; ++i) {
		cart[i].displayProductInfo();
		std::cout << std::endl;
	}
}
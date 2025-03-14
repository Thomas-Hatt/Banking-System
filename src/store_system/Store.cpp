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
	for (int i = 0; i < catalogSize; ++i) {
		if (catalog[i].getProductName() == productName) {
			catalog[i].setPrice(newPrice);
			catalog[i].setQuantity(newQuantity);
			break;
		}
	}
}

// Add item to shopping cart
void Store::addToCart(const std::string& productName, int quantity) {
	for (int i = 0; i < catalogSize; ++i) {
		if (catalog[i].getProductName() == productName && catalog[i].getQuantity() >= quantity) {
			if (cartSize < MAX_PRODUCTS) {
				cart[cartSize] = catalog[i];
				cart[cartSize].setQuantity(quantity);
				cartSize++;
				catalog[i].setQuantity(catalog[i].getQuantity() - quantity);
			}
			else {
				std::cout << "Cart is full!" << std::endl;
			}
			break;
		}
	}
}

// Checkout
void Store::checkout(float& accountBalance) {
	float totalCost = 0;
	for (int i = 0; i < cartSize; ++i) {
		totalCost += cart[i].getPrice() * cart[i].getQuantity();
	}

	if (accountBalance >= totalCost) {
		accountBalance -= totalCost;
		std::cout << "Checkout successful! Total cost: $" << totalCost << std::endl;
		cartSize = 0;
	}
	else {
		std::cout << "Checkout failed! You do not have enough money. Total cost: $" << totalCost << std::endl;
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
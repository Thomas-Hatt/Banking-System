//
// Created by conta on 2/26/2025.
//

#ifndef STORE_H
#define STORE_H

#include "items/headers/product.h"
#include <string>
#include <iostream>

class Store {
public:
	// Constructor
	Store();

	// Methods
	void updateProductDetails(const std::string& productName, float newPrice, int newQuantity);
	void addToCart(const std::string& productName, int quantity);
	void checkout(float& accountBalance);

	// Display methods
	void displayCatalog() const;
	void displayCart() const;

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
};

#endif //STORE_H

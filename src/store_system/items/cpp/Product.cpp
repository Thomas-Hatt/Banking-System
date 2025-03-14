//
// Created by conta on 2/27/2025.
//

#include "../headers/Product.h"
#include <iostream>
#include <string>

// Constructor implementation
Product::Product(const std::string& productName, double price, int quantity)
	: productName(productName), price(price), quantity(quantity) {
}

// Default constructor implementation
Product::Product() : productName(""), price(0.0), quantity(0) {}

// Getter implementations
std::string Product::getProductName() const {
	return productName;
}

double Product::getPrice() const {
	return price;
}

int Product::getQuantity() const {
	return quantity;
}

// Setter implementations
void Product::setPrice(double price) {
	this->price = price;
}

void Product::setQuantity(int quantity) {
	this->quantity = quantity;
}

// Other method implementations
void Product::updateQuantity(int quantity) {
	this->quantity += quantity;
}

void Product::displayProductInfo() const {
	std::cout << "Product: " << productName << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Quantity: " << quantity << std::endl;
}
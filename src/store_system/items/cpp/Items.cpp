//
// Created by conta on 2/27/2025.
//

#include "Items.h"
#include <iostream>
#include <string>

// Constructor implementation
Product::Product(const std::string &productName, double price, int quantity)
    :
 name(productName), price(price), quantity(quantity) {}

// Getter implementations
std::string Product::getName() const {
  return name;
}

double Product::getPrice() const {
  return price;
}

int Product::getQuantity() const {
  return quantity;
}

// Setter implementations
void Product::setName(const std::string &name) {
  this->name = name;
}

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
  std::cout << "Product: " name << std::endl;
  std::cout << "Price: " << price << std::endl;
  std::cout << "Quantity: " << quantity << std::endl;
}
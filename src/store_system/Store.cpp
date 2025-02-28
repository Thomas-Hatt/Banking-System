//
// Created by conta on 2/26/2025.
//

#include "Store.h"
#include <iostream>

// Constructor
Store::Store() catalogSize(0), cartSize(0) {
  initializeCatalog();
}

// Initialize the catalog
void Store::initializeCatalog() {
  // Add items (product name, price, and quantity)
  catalog[0] = Product("Bread", 2.50f, 100);
  catalog[1] = Product("Milk", 3.00f, 90);
  catalog[2] = Product("Chicken", 5.50f, 100);
  catalog[3] = Product("Cereal", 3.50f, 100);
  catalog[4] = Product("Water", 1.50f, 125);

  // Set the catalog size equal to the maximum amount of products
  catalogSize = MAX_PRODUCTS;
}

// Update product details
void Store::updateProductDetails(const std::string &productName, float newPrice, int newQuantity) {
  // Loop through the entire catalog
  for (int i = 0; i < catalogSize; ++i) {
    // Verify the item name, then set the new price and quantity
    if (catalog[i].getName() == productName) {
      catalog[i].setPrice(newPrice);
      catalog[i].setQuantity(newQuantity);
      break;
    }
  }
}

// Add item to shopping cart
void Store::addToCart(const std::string &productName, int quantity) {
  // Loop through the entire catalog
  for (int i = 0; i < catalogSize; ++i) {
    // Verify the item name and verify that there is enough quantity for an item
    if (catalog[i].getName() == productName && catalog[i].getQuantity() >= quantity) {
      // Ensure cart size is not bigger than the maximum amount of items
      if (cartSize < MAX_PRODUCTS) {
        // Add the item to the cart
        cart[cartSize] = catalog[i];

        // Increase the cart size
        cart[cartSize++].updateQuantity(quantity);

        // Decrease the catalog quantity
        catalog[i].updateQuantity(-quantity);
      }
      // Too many items
      else {
        std::cout << "Cart is full!" << std::endl;
      }
      break;
    }
  }
}

// Checkout
void store::checkout(float &accountBalance) {
  // Initialize the total cost
  float totalCost = 0;

  // Loop through the cart and get the price of each item
  for (int i = 0; i < cartSize; ++i) {
    totalCost += cart[i].getPrice() * cart[i].getQuantity();
  }

  // Ensure the user has enough money in their account
  if (accountBalance >= totalCost) {
    // Subtract the money from their account
    accountBalance -= totalCost;
    std::cout << "Checkout successful! Total cost: $" << totalCost << std::endl;

    // Empty out the cart
    cartSize = 0;
  }
  else {
    std::cout << "Checkout failed! You do not have enough money. Total cost: $" << totalCost << std::endl;
  }
}

// Display the catalog
void Store::displayCatalog() const {
  std::cout << "Product Catalog:" << std::endl;
  for (int i = 0; i < catalogSize; ++i) {
    catalog[i].displayProductInfo();
    std::cout << std::endl;
  }
}

// Display shopping cart
void Store::displayCart() const {
  std::cout << "Shopping Cart:" << std::endl;
  for (int i = 0; i < cartSize; ++i) {
    cart[i].displayProductInfo();
    std::cout << std::endl;
  }
}
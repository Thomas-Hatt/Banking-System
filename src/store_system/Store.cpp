#include "Store.h"
#include <iostream>

// Constructor
Store::Store() : catalogSize(0), cartSize(0), currentAccount(nullptr) {
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

// Helper function to find product in catalog by name
int Store::findProductIndex(const std::string& productName) const {
	for (int i = 0; i < catalogSize; ++i) {
		if (catalog[i].getProductName() == productName) {
			return i;
		}
	}

	// Not found
	return -1;
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

			// Success message ("Successfully added 5 Chicken to your cart!")
			std::cout << "\nSuccessfully added " << quantity << " " << catalog[i].getProductName() << " to your cart!" << std::endl;

			// Display how much of the product is left ("Total Chicken remaining: 59")
			std::cout << "Total " << catalog[i].getProductName() << " remaining: " << catalog[i].getQuantity() << std::endl;

			// Display the total cost of the cart
			std::cout << "Current Total: $" << calculateTotalCost() << std::endl;

			// Return after adding the item to the cart
			return;
		}
	}
	if (!found) {
		std::cout << "Product not found." << std::endl;
	}
}

// Checkout
void Store::checkout() {

	// Initialize empty confirmation character
	char userConfirmCheckout;

	// Ensure cart size isn't 0
	if (cartSize == 0) {
		// Output message
		std::cout << "Cart is empty." << std::endl;
		return;
	}

	// Ensure a current account is set
	if (!currentAccount) {
		std::cout << "No account is set. Please log in." << std::endl;
		return;
	}

	// Create a variable for the total cost
	float totalCost = calculateTotalCost();

	// Get user confirmation
	do {
		std::cout << "Are you sure you are ready for checkout? Your current total is $" << totalCost << "." << std::endl;
		std::cout << "Y/N: ";
		std::cin >> userConfirmCheckout;

		// Convert to uppercase to allow lowercase input
		userConfirmCheckout = std::toupper(userConfirmCheckout);

		if (userConfirmCheckout != 'Y' && userConfirmCheckout != 'N') {
			std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << std::endl;
		}

	} while (userConfirmCheckout != 'Y' && userConfirmCheckout != 'N');

	// Ensure the total cost is not greater than the amount of money the user has
	if (currentAccount->getBalance() >= totalCost) {

		try
		{
			// Attempt to withdraw funds from the account
			currentAccount->withdraw(totalCost);
		}
		catch (const std::exception& e)
		{
			// User does not have enough money in their account (requires exception to be thrown)
			std::cout << "Checkout failed." << std::endl;
			std::cout << "You currently have $" << currentAccount->getBalance() << " and the total is $" << totalCost << ", which is $" 
				<< abs(currentAccount->getBalance() - totalCost) << " more than your current balance." << std::endl;
			std::cout << "Exception: " << e.what() << std::endl;
			throw;
		}
	}

	// If balance is insufficient but no exception was thrown, prevent checkout
	else {
		std::cout << "Checkout failed." << std::endl;
		std::cout << "You currently have $" << currentAccount->getBalance() << " and the total is $" << totalCost << ", which is $"
			<< abs(currentAccount->getBalance() - totalCost) << " more than your current balance." << std::endl;
		return;
	}

	// Output message
	std::cout << "\nCheckout successful! Total cost: $" << totalCost << std::endl;

	// Reset cartSize
	cartSize = 0;
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
void Store::displayCart() {
	std::cout << "----------------------------" << std::endl;
	std::cout << "Shopping Cart:" << std::endl;
	for (int i = 0; i < cartSize; ++i) {
		cart[i].displayProductInfo();
		std::cout << std::endl;
	}

	// Check to see if the cart is empty
	if (cartSize == 0) {
		// Output message
		std::cout << "Cart is empty." << std::endl;
		return;
	}

	// Initialize empty confirmation character
	char userClearCart;

	// Get user input to confirm if they would like to clear their cart
	do {
		std::cout << "Would you like to clear your cart?" << std::endl;
		std::cout << "Y/N: ";
		std::cin >> userClearCart;

		// Convert to uppercase to allow lowercase input
		userClearCart = std::toupper(userClearCart);

		if (userClearCart != 'Y' && userClearCart != 'N') {
			std::cout << "Invalid input. Please enter 'Y' for Yes or 'N' for No." << std::endl;
		}

	} while (userClearCart != 'Y' && userClearCart != 'N');

	if (userClearCart == 'Y')
	{
		// Clear the user's cart
		clearCart();
	}
	
	return;
}

void Store::clearCart() {
	// Return items to catalog and clear cart
	for (int i = 0; i < cartSize; ++i) {
		int catalogIndex = findProductIndex(cart[i].getProductName());
		if (catalogIndex != -1) {
			catalog[catalogIndex].setQuantity(catalog[catalogIndex].getQuantity() + cart[i].getQuantity());
		}
	}

	// Set cart size to 0
	cartSize = 0;

	// Output message
	std::cout << "\nCart cleared and items returned to catalog." << std::endl;
}

// Setter for current account
void Store::setCurrentAccount(Bank_Account* account) {
	currentAccount = account;
}

// Calculate total cost of items in cart
float Store::calculateTotalCost() const {
	float totalCost = 0.0f;
	for (int i = 0; i < cartSize; ++i) {
		totalCost += cart[i].getPrice() * cart[i].getQuantity();
	}
	return totalCost;
}
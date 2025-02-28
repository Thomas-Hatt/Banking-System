//
// Created by conta on 2/26/2025.
//

#include <iostream>

#include "Main.h"
#include "../src/store_system/Store.h"

void displayMainMenu() {
    std::cout << "Welcome to the Banking System" << std::endl;
    std::cout << "1. Create Account" << std::endl;
    std::cout << "2. Update Account" << std::endl;
    std::cout << "3. Delete Account" << std::endl;
    std::cout << "4. View Accounts" << std::endl;
    std::cout << "5. Review Transactions" << std::endl;
    std::cout << "6. Loan System" << std::endl;
    std::cout << "7. Store System" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

// Main class, to be implemented.
int main() {
    // Create a Store object
    Store store;

    int choice;
    do {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            // To be implemented
            //createAccount();
            break;
        case 2:
            // To be implemented
            //updateAccount();
            break;
        case 3:
            // To be implemented
            //deleteAccount();
            break;
        case 4:
            // To be implemented
            //viewAccounts();
            break;
        case 5:
            // To be implemented
            //reviewTransactions();
            break;
        case 6:
            // To be implemented
            //loanSystem();
            break;
        case 7:
            // Pass the store object to storeSystem
            storeSystem(store);
            break;
        case 8:
            std::cout << "Exiting the program..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 8);

    return 0;
}

// 7. Implement the storeSystem function
void storeSystem(Store& store) {
    int choice;
    do {
        std::cout << "\nStore System Menu:" << std::endl;
        std::cout << "1. Display Catalog" << std::endl;
        std::cout << "2. Add to Cart" << std::endl;
        std::cout << "3. Display Cart" << std::endl;
        std::cout << "4. Checkout" << std::endl;
        std::cout << "5. Return to Main Menu" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                store.displayCatalog();
            break;
            case 2: {
                std::string productName;
                int quantity;
                std::cout << "Enter product name: ";
                std::cin >> productName;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;
                store.addToCart(productName, quantity);
                break;
            }
            case 3:
                store.displayCart();
            break;
            case 4: {
                float accountBalance = 1000.0f;  // Example balance
                store.checkout(accountBalance);
                std::cout << "Remaining balance: $" << accountBalance << std::endl;
                break;
            }
            case 5:
                std::cout << "Returning to main menu..." << std::endl;
            break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);
}
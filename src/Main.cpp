//
// Created by conta on 2/26/2025.
//

#include <iostream>
#include "Main.h"

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

int main() {
    int choice;
    do {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            updateAccount();
            break;
        case 3:
            deleteAccount();
            break;
        case 4:
            viewAccounts();
            break;
        case 5:
            reviewTransactions();
            break;
        case 6:
            loanSystem();
            break;
        case 7:
            storeSystem();
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

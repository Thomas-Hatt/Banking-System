//
// Created by conta on 2/26/2025.
//

#include <iostream>
#include <random>
#include <string>
#include <regex>
#include <cctype>
#include "Main.h"

// Include the store system
#include "../src/store_system/Store.h"

// Include the bank account systems
#include "../src/bank_account_systems/headers/Bank_Account.h"
#include "../src/bank_account_systems/headers/Reserve_Account.h"
#include "../src/bank_account_systems/headers/Growth_Account.h"
#include "../src/bank_account_systems/headers/Spending_Account.h"

// Define a custom output stream operator
std::ostream& operator<<(std::ostream& os, const struct Separator&) {
	return os << std::endl << "----------------" << std::endl;
}

// Define a struct to use with the custom operator
struct Separator {};

// Array of names that can double as first or last names (used to generate random accounts)
std::vector<std::string> names = {
	"Taylor", "Morgan", "Jordan", "Parker",
	"Bailey", "Riley", "Hunter", "Carter",
	"Logan", "Quinn", "Casey", "Avery",
	"Harper", "Reagan", "Emerson"
};

// Linked list node structure for bank account
struct AccountNode {
	Bank_Account* account;
	AccountNode* next;

	AccountNode(Bank_Account* acc) : account(acc), next(nullptr) {}
};

// Generate 10-digit random number (int)
int generate10DigitNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1000000000, 9999999999);
	return dis(gen);
}

// Generate 10-digit random number (overriden to be a long long)
long long generate10DigitNumber(long long) {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<long long> dis(1000000000LL, 9999999999LL);
	return dis(gen);
}

class AccountList {
private:
	// Pointer to the first node in the linked list (head)
	AccountNode* head = nullptr;
public:
	// Deconstructor to delete all accounts and nodes in the linked list
	~AccountList() {
		AccountNode* current = head;
		while (current) {
			AccountNode* next = current->next;
			delete current->account;
			delete current;
			current = next;
		}
	}

	// Add a new bank account to the linked list
	void addAccount(Bank_Account* acc) {
		AccountNode* newNode = new AccountNode(acc);
		if (!head) {
			head = newNode;
		}
		else {
			AccountNode* temp = head;
			while (temp->next) temp = temp->next;
			temp->next = newNode;
		}
	}

	// Checks if a user with the given ID exists in the list
	// Return true if the user exists, otherwise return false
	bool userExists(const std::string& userID) {
		AccountNode* current = head;
		while (current) {
			if (current->account->getUserID() == userID) return true;
			current = current->next;
		}
		return false;
	}

	// Display all accounts in the linked list
	// If no accounts exist, it displays an error message
	void displayAll() {
		// If the linked list is empty, display a message to the user
		if (!head) {
			std::cout << "There are no accounts to display." << std::endl;
			return;
		}

		AccountNode* current = head;
		while (current) {
			current->account->displayAccountInformation();
			std::cout << Separator();
			current = current->next;
		}
	}

	// Finds a specific account by user ID and account type
	Bank_Account* findAccount(const std::string& userID, AccountType type) {
		AccountNode* current = head;
		while (current) {
			if (current->account->getUserID() == userID &&
				current->account->getAccountType() == type) {
				return current->account;
			}
			current = current->next;
		}
		return nullptr;
	}
};

/*
*
-- Validation functions --
*
*/

// Function to validate non-empty input
bool validateNonEmpty(const std::string& input, const std::string& fieldName) {
	if (input.empty()) {
		std::cout << fieldName << " cannot be blank. Please try again.\n";
		return false;
	}
	return true;
}

// Function to validate names (letters, hyphens, apostrophes, and spaces)
bool validateName(const std::string& name, const std::string& fieldName) {
	std::regex pattern("^[A-Za-z-' ]{2,30}$");
	if (!std::regex_match(name, pattern)) {
		std::cout << "Invalid " << fieldName << "! Only letters, hyphens, and apostrophes allowed (2-30 characters).\n";
		return false;
	}
	return true;
}

// Function to validate email addresses
bool validateEmail(const std::string& email) {
	std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
	if (!std::regex_match(email, pattern)) {
		std::cout << "Invalid email format! Use example@domain.com.\n";
		return false;
	}
	return true;
}

// Function to validate addresses (letters, numbers, spaces, and common punctuation)
bool validateAddress(const std::string& address) {
	if (address.length() < 5 || address.length() > 50) {
		std::cout << "Address must be 5-50 characters long.\n";
		return false;
	}
	return true;
}

// Function to validate gender (M, F, O)
bool validateGender(char gender) {
	gender = toupper(gender);
	if (gender != 'M' && gender != 'F' && gender != 'O') {
		std::cout << "Invalid gender! Enter M, F, or O.\n";
		return false;
	}
	return true;
}

// Function to validate phone numbers (10 digits)
bool validatePhoneNumber(const std::string& phone) {
	std::regex pattern(R"(^(\+\d{1,3}[-.\s]?)?(\d{1,4}[-.\s]?)?\d{3,4}[-.\s]?\d{3,4}$)");
	return std::regex_match(phone, pattern);
}

// Function Prototypes
void createAccount(AccountList& accounts);
void viewAccounts(AccountList& accounts);
void storeSystem(Store& store, AccountList& accounts);

// Create an account with randomly generated information (mostly used for debugging)
void generateRandomAccount(AccountList& accounts) {
	// Create a string containing common English letters and numbers
	const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, chars.size() - 1);

	// Generate random UserID - ensure uniqueness
	std::string randomUserID;
	do {
		randomUserID.clear();
		for (int i = 0; i < 8; ++i) {
			randomUserID += chars[dis(gen)];
		}
	} while (accounts.userExists(randomUserID)); // Prevent duplicate IDs

	// Create a default password of "password" (very creative)
	std::string defaultPassword = "password";

	// Randomly generate a first name and last name
	std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<std::size_t> distribution(0, names.size() - 1); // Evenly distribute odds for random selection
	std::string fname = names[distribution(generator)];
	std::string lname = names[distribution(generator)];

	// Generate a random email address - basic format validation
	std::string randomEmail;
	for (int i = 0; i < 8; ++i) {
		randomEmail += chars[dis(gen)];
	}
	randomEmail = randomEmail + "@email.com"; // Ensure valid format

	// Generate a random phone number - ensure 10 digits
	long long phoneLongLong;
	do {
		phoneLongLong = generate10DigitNumber();
	} while (phoneLongLong < 1000000000 || phoneLongLong > 9999999999); // Validate length

	// Create a default gender of "O"
	char defaultGender = 'O';

	// Create a default address
	std::string defaultAddress = "123 Random Street";

	accounts.addAccount(new Spending_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress
	));

	accounts.addAccount(new Reserve_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.01f
	));

	accounts.addAccount(new Growth_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.01f
	));

	// Final output
	std::cout << "All accounts created successfully!\n";
	std::cout << "-- Login Information --" << std::endl;
	std::cout << "User ID: " << randomUserID << std::endl;
	std::cout << "Password: " << defaultPassword << std::endl;
}

/*
 * Create a new bank account for the user
 *
 * This function prompts the user for personal information (name, email, address, etc.),
 * validates the input, and creates the three types of accounts (Spending, Reserve, Growth)
 * for the user. The accounts are added to the AccountList.
 */
void createAccount(AccountList& accounts) {
	// Initialize the user's ID and password variables
	std::string userID, password;

	// Validate User ID
	do {
		std::cout << "Enter User ID (or type 100 to generate a random one): ";
		std::getline(std::cin, userID);

		// Generate a random account (mostly for debugging)
		if (userID == "100") {
			generateRandomAccount(accounts);
			return;  // Exit after generating random accounts
		}
	} while (!validateNonEmpty(userID, "User ID") || accounts.userExists(userID));

	// Validate Password
	do {
		std::cout << "Enter Password: ";
		std::getline(std::cin, password);
		if (password.length() < 6) {
			std::cout << "Password must be at least 6 characters long.\n";
		}
	} while (!validateNonEmpty(password, "Password") || password.length() < 6);

	// Initialize variables for the user's information
	std::string fname, lname, email, address;
	char gender;

	// Validate First Name
	do {
		std::cout << "First Name: ";
		std::getline(std::cin, fname);
	} while (!validateNonEmpty(fname, "First Name") || !validateName(fname, "First Name"));

	// Validate Last Name
	do {
		std::cout << "Last Name: ";
		std::getline(std::cin, lname);
	} while (!validateNonEmpty(lname, "Last Name") || !validateName(lname, "Last Name"));

	// Validate Email
	do {
		std::cout << "Email: ";
		std::getline(std::cin, email);
	} while (!validateNonEmpty(email, "Email") || !validateEmail(email));

	// Validate Address
	do {
		std::cout << "Address: ";
		std::getline(std::cin, address);
	} while (!validateNonEmpty(address, "Address") || !validateAddress(address));

	// Validate Gender
	do {
		std::cout << "Gender (M/F/O): ";
		std::string input;
		std::getline(std::cin, input);
		gender = input.empty() ? ' ' : toupper(input[0]);
	} while (!validateGender(gender));

	// Validate Phone Number
	// In createAccount()
	std::string phone;
	long long int phoneLongInt = 0;
	do {
		std::cout << "Phone number: ";
		std::getline(std::cin, phone);
		try {
			phoneLongInt = std::stoll(phone);
		}
		catch (const std::exception& e) {
			std::cout << "Invalid phone number! Use digits only.\n";
			continue;
		}
	} while (!validatePhoneNumber(phone));

	// Convert user's Phone Number from string to long long
	long long phoneLongLong = std::stoll(phone);



	// Account information:
	// int accountNumber, string& userID, string& userPassword, float balance, string& ownerFirstName, string& ownerLastName,
	// string& ownerEmail, int ownerPhoneNumber, char ownerGender, std::string& ownerAddress
	accounts.addAccount(new Spending_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address
	));

	accounts.addAccount(new Reserve_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address, 0.01f
	));

	accounts.addAccount(new Growth_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address, 0.01f
	));

	std::cout << "All accounts created successfully!\n";
}

// Transaction System
void transactionSystem(AccountList& accounts) {
	// Initialize a variable to get the user's ID
	std::string userID;
	std::cout << "Enter your User ID: ";
	std::cin >> userID;

	int choice;
	do {
		// Display choices
		std::cout << "\nTransaction System Menu:" << std::endl;
		std::cout << "1. Deposit Money" << std::endl;
		std::cout << "2. Withdraw Money" << std::endl;
		std::cout << "3. Transfer Money" << std::endl;
		std::cout << "4. Return to Main Menu" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
			// Case 1: Deposit Money
		case 1: {
			// Initialize variables for the account type and the amount of money
			int accountType;
			float amount;

			// Display message for selecting the account type
			std::cout << "Select Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			
			// Get input for the account type
			std::cin >> accountType;

			// Validate account type input
			if (std::cin.fail() || accountType < 1 || accountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
				continue;
			}

			// Display message for the amount to deposit
			std::cout << "Enter amount to deposit: $";

			// Get input for the amount of money to deposit
			std::cin >> amount;

			// Validate amount input
			if (std::cin.fail() || amount <= 0) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid amount! Must be a positive number.\n";
				continue;
			}

			// Determine the account type
			AccountType type;
			switch (accountType) {
			case 1: type = SPENDING; break;
			case 2: type = RESERVE; break;
			case 3: type = GROWTH; break;
			default:
				// Handle invalid account type input
				std::cout << "Invalid account type!\n";
				continue;
			}

			Bank_Account* account = accounts.findAccount(userID, type);
			if (account) {
				account->deposit(amount);
			}
			else {
				std::cout << "Account not found!\n";
			}
			break;
		}

			  // Case 2: Withdraw money from account (it goes into the void)
		case 2: {
			// Initialize variables for the account type and withdrawal amount
			int accountType;
			float withdrawalAmount;

			// Display message for selecting the account type
			std::cout << "Select Account Type to Withdraw From:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			std::cin >> accountType;

			// Validate account type input
			if (std::cin.fail() || accountType < 1 || accountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
				continue;
			}

			// Display message for the amount to withdraw
			std::cout << "Enter amount to withdraw: $";
			std::cin >> withdrawalAmount;

			// Validate withdrawal amount input
			if (std::cin.fail() || withdrawalAmount <= 0) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid amount! Must be a positive number.\n";
				continue;
			}

			// Determine the account type
			AccountType type;
			switch (accountType) {
			case 1: type = SPENDING; break;
			case 2: type = RESERVE; break;
			case 3: type = GROWTH; break;
			default:
				// Handle invalid account type input
				std::cout << "Invalid account type!\n";
				continue;
			}

			// Find the account
			Bank_Account* account = accounts.findAccount(userID, type);
			if (!account) {
				std::cout << "Account not found!\n";
				continue;
			}

			// Check if the account has enough balance
			if (account->getBalance() < withdrawalAmount) {
				std::cout << "Insufficient funds in account!\n";
				continue;
			}

			// Perform the withdrawal
			account->withdraw(withdrawalAmount);
			std::cout << "Successfully withdrew $" << withdrawalAmount << " from your account.\n";

			break;
		}


			  // Case 3: Transfer money from one account to another account
		case 3: {
			// Initialize variables for the source and destination account types, and the transfer amount
			int sourceAccountType, destinationAccountType;
			float transferAmount;

			// Display message for source account type selection
			std::cout << "Select Source Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			std::cin >> sourceAccountType;

			// Validate source account type input
			if (std::cin.fail() || sourceAccountType < 1 || sourceAccountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
				continue;
			}

			// Display message for destination account type selection
			std::cout << "Select Destination Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			std::cin >> destinationAccountType;

			// Validate destination account type input
			if (std::cin.fail() || destinationAccountType < 1 || destinationAccountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid choice! Please enter a number between 1 and 3.\n";
				continue;
			}

			// Check if source and destination types are the same
			if (sourceAccountType == destinationAccountType) {
				std::cout << "Source and destination accounts cannot be the same!\n";
				continue;
			}

			// Display message to input transfer amount
			std::cout << "Enter amount to transfer: $";
			std::cin >> transferAmount;

			// Validate transfer amount input
			if (std::cin.fail() || transferAmount <= 0) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid transfer amount! Must be a positive number.\n";
				continue;
			}

			// Determine source account type
			AccountType sourceType;
			switch (sourceAccountType) {
			case 1: sourceType = SPENDING; break;
			case 2: sourceType = RESERVE; break;
			case 3: sourceType = GROWTH; break;
			default:
				std::cout << "Invalid source account type!\n";
				continue;
			}

			// Determine destination account type
			AccountType destinationType;
			switch (destinationAccountType) {
			case 1: destinationType = SPENDING; break;
			case 2: destinationType = RESERVE; break;
			case 3: destinationType = GROWTH; break;
			default:
				std::cout << "Invalid destination account type!\n";
				continue;
			}

			// Find the source and destination accounts
			Bank_Account* sourceAccount = accounts.findAccount(userID, sourceType);
			Bank_Account* destinationAccount = accounts.findAccount(userID, destinationType);

			if (!sourceAccount) {
				std::cout << "Source account not found!\n";
				continue;
			}

			if (!destinationAccount) {
				std::cout << "Destination account not found!\n";
				continue;
			}

			// Check if the source account has enough balance
			if (sourceAccount->getBalance() < transferAmount) {
				std::cout << "Insufficient funds in source account!\n";
				continue;
			}

			// Perform the transfer
			sourceAccount->withdraw(transferAmount);
			destinationAccount->deposit(transferAmount);
			std::cout << "Successfully transferred $" << transferAmount
				<< " from " << sourceAccount << " to " << destinationAccount << " account.\n";

			break;
		}

			  // Case 4: Return to the main menu
		case 4:
			std::cout << "Returning to main menu...\n";
			break;

			// Error if the user enters a wrong input
		default:
			std::cout << "Invalid choice!\n";
		}
	} while (choice != 4);
}

// Display all accounts
void viewAccounts(AccountList& accounts) {
	accounts.displayAll();
}

// Display the main menu function
void displayMainMenu() {
	std::cout << Separator();
	std::cout << "Welcome to the Banking System" << std::endl;
	std::cout << "1. Create Account" << std::endl;
	std::cout << "2. Update Account" << std::endl;
	std::cout << "3. Delete Account" << std::endl;
	std::cout << "4. View Accounts" << std::endl;
	std::cout << "5. Transactions" << std::endl;
	std::cout << "6. Loan System" << std::endl;
	std::cout << "7. Store System" << std::endl;
	std::cout << "8. Exit" << std::endl;
	std::cout << "Enter your choice: ";
}

// Main class, to be implemented.
int main() {
	// Create a Store object
	Store store;

	// Linked list manager
	AccountList accounts;

	// User choice
	int choice;
	do {
		// Display the main menu
		displayMainMenu();

		// Get the user's input for the main menu
		std::cin >> choice;

		// Clear buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		switch (choice) {
		case 1:
			// Case 1: Create a new bank account
			createAccount(accounts);
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
			// Case 3: View the bank accounts the user has
			viewAccounts(accounts);
			break;
		case 5:
			// Case 5: Open the transaction menu
			transactionSystem(accounts);
			break;
		case 6:
			// To be implemented
			//loanSystem();
			break;
		case 7:
			// Case 7: Pass the store object to storeSystem
			storeSystem(store, accounts);
			break;
		case 8:
			// Case 8: Exit the program
			std::cout << "Exiting the program..." << std::endl;
			break;
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 8);

	return 0;
}

// 7. Implement the storeSystem function
void storeSystem(Store& store, AccountList& accounts) {
	std::string userID;
	std::cout << "Enter your User ID: ";
	std::cin >> userID;

	// Use findAccount instead of accessing head directly
	Bank_Account* spendingAcc = accounts.findAccount(userID, SPENDING);

	if (!spendingAcc) {
		std::cout << "No spending account found!\n";
		return;
	}

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
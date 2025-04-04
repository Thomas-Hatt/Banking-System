//
// Created by conta on 2/26/2025.
//

#include <iostream>
#include <random>
#include <string>
#include <regex>
#include <algorithm>
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

// Function to trim leading and trailing whitespace from a string
std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\n\r");
	if (start == std::string::npos) {
		return ""; // String is all whitespace
	}
	size_t end = str.find_last_not_of(" \t\n\r");
	return str.substr(start, end - start + 1);
}

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

// Generate random 10-digit integer
int generate10DigitNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1000000000, 9999999999);
	return dis(gen);
}

// Generate 10-digit random number (overriden to be a long long)
// This version of generate10DigitNumber is used when creating a random phone number
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
	// Create a new node
	void addAccount(Bank_Account* acc) {
		AccountNode* newNode = new AccountNode(acc);
		if (!head) {
			// If the list is empty, set the head
			head = newNode;
		}
		else {
			AccountNode* temp = head;

			// Traverse to the last node
			while (temp->next) temp = temp->next;

			// Append at the end
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
	// Purpose: Displays either general or detailed account information based on viewtype
	void displayAcctInfo(int viewType, const std::string& userID) {
		// If the linked list is empty, display a message to the user
		if (!head) {
			std::cout << "\nThere are no accounts to display!" << std::endl;
			return;
		}

		// viewType value '1': Display general account information for each account
		if (viewType == 1)
		{
			AccountNode* current = head;
			while (current) {
				current->account->displayAccountInformation();
				// std::cout << "DEBUG: Calling displayAccountInformation() for -> " << current->account->getAccountNumber() << std::endl;
				std::cout << Separator();
				current = current->next;
			}
		}

		// viewType value '2': Display user-specific detailed account information
		else if (viewType == 2)
		{
			AccountNode* current = head;
			while (current) {
				if (current->account->getUserID() == userID) {
					return current->account->displayDetailedAcctInfo();
				}
				current = current->next;
			}
			std::cout << Separator();
			return;
		}
	}

	// Purpose: Locates an account based on User ID and Account Type
	Bank_Account* findAccount(const std::string& userID, AccountType type) {
		AccountNode* current = head;
		while (current) {
			if (current->account->getUserID() == userID &&
				current->account->getAccountType() == type) {
				return current->account;
			}
			current = current->next;
		}
		// Account not found
		return nullptr;
	}

	// Purpose: Deletes all accounts associated with a user
	void deleteAccounts(const std::string& userInput) {
		// If there are no accounts to delete, return
		if (!head) {
			std::cout << "There are no accounts in the list to delete!" << std::endl;
			return;
		}

		// Trim whitespace from input
		std::string userID = trim(userInput);

		AccountNode* current = head;
		AccountNode* previous = nullptr;
		bool deleted = false;

		while (current) {

			if (current->account->getUserID() == userID) {

				if (previous == nullptr) {
					// Deleting head node
					head = current->next;
				}

				else {
					// Deleting non-head node
					previous->next = current->next;
				}

				delete current->account;
				AccountNode* temp = current;
				current = current->next;
				delete temp;

				// Mark as deleted
				deleted = true;
				continue; // Skip updating 'previous'
			}
			else {
				previous = current;
				current = current->next;
			}
		}

		// Confirm that all accounts were deleted
		if (deleted) {
			// Display confirmation message
			std::cout << "All accounts for User ID '" << userInput << "' were deleted successfully." << std::endl;
		}
	}

	// Public method to iterate through accounts and apply a function
	// Purpose: Updates specific fields for accounts linked to a user
	void updateAccountsForUser(const std::string& userID,
		const std::string& newPassword, const std::string& newFname,
		const std::string& newLname, const std::string& newEmail,
		const std::string& newAddress, char newGender, long long phoneLongLong) {

		AccountNode* current = head;
		while (current) {
			if (current->account->getUserID() == userID) {
				if (!newPassword.empty()) {
					current->account->setUserPassword(newPassword);
				}
				if (!newFname.empty()) {
					current->account->setOwnerFirstName(newFname);
				}
				if (!newLname.empty()) {
					current->account->setOwnerLastName(newLname);
				}
				if (!newEmail.empty()) {
					current->account->setOwnerEmail(newEmail);
				}
				if (!newAddress.empty()) {
					current->account->setOwnerAddress(newAddress);
				}
				if (newGender != '\0') {
					current->account->setOwnerGender(newGender);
				}
				if (phoneLongLong != 0) {
					current->account->setOwnerPhoneNumber(phoneLongLong);
				}
			}
			current = current->next;
		}
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
void viewAccounts(AccountList& accounts, int viewType, const std::string& userID);
void storeSystem(Store& store, AccountList& accounts);
void updateAccount(AccountList& accounts);

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

	// Add spending account
	accounts.addAccount(new Spending_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
	));

	// Add reserve account
	accounts.addAccount(new Reserve_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
	));

	// Add growth account
	accounts.addAccount(new Growth_Account(
		generate10DigitNumber(), randomUserID, defaultPassword, 1000.0f,
		fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
	));

	// Confirm account creation
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

	// Defining a regex for local whitespace removal
	std::regex r("\\s+");

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

	// Trim the userID
	userID = std::regex_replace(userID, r, "");

	// Debug Output of userID
	// std::cout << userID << std::endl;

	// Validate Password
	do {
		std::cout << "Enter Password: ";
		std::getline(std::cin, password);
		if (password.length() < 6) {
			std::cout << "Password must be at least 6 characters long.\n";
		}
	} while (!validateNonEmpty(password, "Password") || password.length() < 6);

	// Trim the password
	password = std::regex_replace(userID, r, "");

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

	// Add the spending account
	accounts.addAccount(new Spending_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address, 0.00f
	));

	// Add the reserve account
	accounts.addAccount(new Reserve_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address, 0.00f
	));

	// Add the growth account
	accounts.addAccount(new Growth_Account(
		generate10DigitNumber(), userID, password, 1000.0f,
		fname, lname, email, phoneLongLong, gender, address, 0.00f
	));

	// Confirm account creation
	std::cout << "\nAll accounts created successfully!" << std::endl;
	std::cout << "-- Login Information --" << std::endl;
	std::cout << "User ID: " << userID << std::endl;
	std::cout << "Password: " << password << std::endl;
}

void updateAccount(AccountList& accounts) {
	// Prompt for User ID
	std::string userID;
	std::cout << "Enter User ID to update account: ";
	std::getline(std::cin, userID);

	// Check if the user exists
	if (!accounts.userExists(userID)) {
		std::cout << "User ID not found. Cannot update account.\n";
		return;
	}

	// Get updated information (you can reuse the validation functions)
	std::string newPassword, newFname, newLname, newEmail, newAddress, phone;
	char newGender;
	long long phoneLongLong = 0;

	// Get and validate new password
	do {
		std::cout << "Enter new Password (or leave blank to keep current): ";
		std::getline(std::cin, newPassword);
		if (!newPassword.empty() && newPassword.length() < 6) {
			std::cout << "Password must be at least 6 characters long.\n";
		}
	} while (!newPassword.empty() && newPassword.length() < 6);

	// Get and validate new first name
	do {
		std::cout << "Enter new First Name (or leave blank to keep current): ";
		std::getline(std::cin, newFname);
	} while (!newFname.empty() && !validateName(newFname, "First Name"));

	// Get and validate new last name
	do {
		std::cout << "Enter new Last Name (or leave blank to keep current): ";
		std::getline(std::cin, newLname);
	} while (!newLname.empty() && !validateName(newLname, "Last Name"));

	// Get and validate new email
	do {
		std::cout << "Enter new Email (or leave blank to keep current): ";
		std::getline(std::cin, newEmail);
	} while (!newEmail.empty() && !validateEmail(newEmail));

	// Get and validate new address
	do {
		std::cout << "Enter new Address (or leave blank to keep current): ";
		std::getline(std::cin, newAddress);
	} while (!newAddress.empty() && !validateAddress(newAddress));

	// Get and validate new gender
	do {
		std::cout << "Enter new Gender (M/F/O, or leave blank to keep current): ";
		std::string input;
		std::getline(std::cin, input);
		newGender = input.empty() ? '\0' : toupper(input[0]);  // Use '\0' to indicate no change
	} while (newGender != '\0' && !validateGender(newGender));

	// Get and validate new phone number
	do {
		std::cout << "Enter new Phone number (or leave blank to keep current): ";
		std::getline(std::cin, phone);
		if (!phone.empty()) {
			try {
				phoneLongLong = std::stoll(phone);
			}
			catch (const std::exception& e) {
				std::cout << "Invalid phone number! Use digits only.\n";
				continue;
			}
			if (!validatePhoneNumber(phone)) {
				phoneLongLong = 0;
			}
		}
	} while (!phone.empty() && (phoneLongLong == 0 && validatePhoneNumber(phone)));

	accounts.updateAccountsForUser(userID, newPassword, newFname, newLname, newEmail, newAddress, newGender, phoneLongLong);

	std::cout << "Account updated successfully!\n";
}


// Transaction System
void transactionSystem(AccountList& accounts) {
	// Initialize a variable to get the user's ID
	std::string userID;
	std::cout << "\nEnter your User ID: ";
	std::cin >> userID;

	int choice;
	do {
		// Display choices
		std::cout << "\nTransaction System Menu:" << std::endl;
		std::cout << "1. Deposit Money" << std::endl;
		std::cout << "2. Withdraw Money" << std::endl;
		std::cout << "3. Transfer Money" << std::endl;
		std::cout << "4. View Past Transactions" << std::endl;
		std::cout << "5. Return to Main Menu" << std::endl;

		std::cout << "\nEnter your choice: ";
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

			// Find the account
			Bank_Account* account = accounts.findAccount(userID, type);
			if (account) {
				// Deposit money into account
				account->deposit(amount);
			}
			else {
				// Display error message if the account is not found
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
				std::cout << "Invalid amount! Must be a positive number." << std::endl;
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
				std::cout << "Invalid account type!" << std::endl;
				continue;
			}

			// Find the account
			Bank_Account* account = accounts.findAccount(userID, type);
			if (!account) {
				std::cout << "Account not found!" << std::endl;
				continue;
			}

			// Perform the withdrawal
			account->withdraw(withdrawalAmount);
			// std::cout << "\nSuccessfully withdrew $" << withdrawalAmount << " from your account." << std::endl;
			break;
		}


			  // Case 3: Transfer money from one account to another account
		case 3: {
			// Initialize variables for the source and destination account types, and the transfer amount
			int sourceAccountType, destinationAccountType;
			float transferAmount;

			// Display message for source account type selection
			std::cout << "\nSelect Source Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			std::cin >> sourceAccountType;

			// Validate source account type input
			if (std::cin.fail() || sourceAccountType < 1 || sourceAccountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "\nInvalid choice! Please enter a number between 1 and 3." << std::endl;
				continue;
			}

			// Display message for destination account type selection
			std::cout << "\nSelect Destination Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";
			std::cin >> destinationAccountType;

			// Validate destination account type input
			if (std::cin.fail() || destinationAccountType < 1 || destinationAccountType > 3) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "\nInvalid choice! Please enter a number between 1 and 3." << std::endl;
				continue;
			}

			// Check if source and destination types are the same
			if (sourceAccountType == destinationAccountType) {
				std::cout << "\nSource and destination accounts cannot be the same!" << std::endl;
				continue;
			}

			// Display message to input transfer amount
			std::cout << "Enter amount to transfer: $";
			std::cin >> transferAmount;

			// Validate transfer amount input
			if (std::cin.fail() || transferAmount <= 0) {
				std::cin.clear(); // Clear the error flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
				std::cout << "Invalid transfer amount! Must be a positive number." << std::endl;
				continue;
			}

			// Determine source account type
			AccountType sourceType;
			switch (sourceAccountType) {
			case 1: sourceType = SPENDING; break;
			case 2: sourceType = RESERVE; break;
			case 3: sourceType = GROWTH; break;
			default:
				std::cout << "Invalid source account type!" << std::endl;
				continue;
			}

			// Determine destination account type
			AccountType destinationType;
			switch (destinationAccountType) {
			case 1: destinationType = SPENDING; break;
			case 2: destinationType = RESERVE; break;
			case 3: destinationType = GROWTH; break;
			default:
				// If the user enters a number other than 1-3, display an error message
				std::cout << "Invalid destination account type!" << std::endl;
				continue;
			}

			// Find the source and destination accounts
			Bank_Account* sourceAccount = accounts.findAccount(userID, sourceType);
			Bank_Account* destinationAccount = accounts.findAccount(userID, destinationType);

			// Check to see if the source account exists
			if (!sourceAccount) {
				std::cout << "Source account not found!" << std::endl;
				continue;
			}

			// Check to see if the destination account exists
			if (!destinationAccount) {
				std::cout << "Destination account not found!" << std::endl;
				continue;
			}

			// Perform the transfer
			sourceAccount->transfer(transferAmount, *destinationAccount);
			/* Example use case #1:
			*
			Spending Account Balance: $100
			Reserve Account Balance: $523
			Attempt: Transfer $50 from Spending Account to Reserve Account
			New Balances:

			Spending Account Balance: $50
			Reserve Account Balance: $573
			*/

			/* Example use case #2:
			*
			Spending Account Balance: $590
			Growth Account Balance: $1662
			Attempt: Transfer $1000 from Spending Account to Growth Account
			Transferring $1000 goes beyond the overdraft limit, so the transaction doesn't go through
			New Balances:

			Spending Account Balance: $590
			Growth Account Balance: $1662
			*/
			break;
		}

			  // Case 4: View Past Transactions
		case 4: {
			int accountType;

			// Ask the user to select the account type they'd like to view the transactions for
			std::cout << "Select Account Type to View Transactions:\n"
				<< "1. Spending\n2. Reserve\n3. Growth\nChoice: ";

			// Grab input
			std::cin >> accountType;

			// If the user enters a number that's not between 1-3, display an error message
			if (std::cin.fail() || accountType < 1 || accountType > 3) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid choice! Please enter a number between 1 and 3." << std::endl;
				continue;
			}

			AccountType type;
			switch (accountType) {
			case 1: type = SPENDING; break;
			case 2: type = RESERVE; break;
			case 3: type = GROWTH; break;
			default:
				std::cout << "Invalid account type!\n";
				continue;
			}

			Bank_Account* account = accounts.findAccount(userID, type);
			if (!account) {
				std::cout << "Account not found!" << std::endl;
				continue;
			}

			std::cout << "\nTransactions for " << userID << " ("
				<< (type == SPENDING ? "Spending" : type == RESERVE ? "Reserve" : "Growth")
				<< " Account):" << std::endl;
			account->displayTransactions(); // Display all transactions
			break;
		}
			  // Case 5: Return to the main menu
		case 5:
			std::cout << "Returning to main menu..." << std::endl;
			break;

			// Error if the user enters a wrong input
		default:
			std::cout << "Invalid choice!" << std::endl;
		}
	} while (choice != 5);
}

// Display all accounts
void viewAccounts(AccountList& accounts, int viewType, const std::string& userID) {
	accounts.displayAcctInfo(viewType, userID);
}

// Display the main menu function
void displayMainMenu() {
	std::cout << "\n---------------------------------------" << std::endl;
	std::cout << "Welcome to the Banking System" << std::endl;
	std::cout << "1. Create Account" << std::endl;
	std::cout << "2. Update Account" << std::endl;
	std::cout << "3. Delete Account" << std::endl;
	std::cout << "4. View Accounts" << std::endl;
	std::cout << "5. Transactions" << std::endl;
	std::cout << "6. Loan System" << std::endl;
	std::cout << "7. Store System" << std::endl;
	std::cout << "8. Exit" << std::endl;
	std::cout << "\nEnter your choice: ";
}

// Main class, to be implemented.
int main() {
	// Create a Store object
	Store store;

	// Linked list manager
	AccountList accounts;

	// User choice variables
	int choice;
	std::string acctDeletionInput;
	std::string inpUserID;

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
			// Case 2: Update accounts
			updateAccount(accounts);
			break;

		case 3:
			// Case 3: Delete accounts

			std::cout << Separator();

			// Get user input
			std::cout << "Enter the User ID of the account you'd like to delete: ";
			std::cin >> acctDeletionInput;

			// Debug Output for the account deletion input
			// std::cout << acctDeletionInput;

			// Delete all accounts associated with user's input
			try {
				// Attempt to delete all accounts associated with user's input
				accounts.deleteAccounts(acctDeletionInput);

				// Successful deletion
				std::cout << "Account(s) deleted successfully!" << std::endl;
			}
			catch (const std::exception& e) {
				// Handle other exceptions
				std::cerr << "Exception caught: " << e.what() << std::endl;
			}
			break;
		case 4:
			// Case 4: View bank accounts (all or detailed user-specific)
			do {
				std::cout << "\n1. View all general account information" << std::endl;
				std::cout << "2. View detailed user-specific account information" << std::endl;
				std::cout << "3. Return to the main menu" << std::endl;

				// Get user input
				std::cout << "\nEnter your choice: ";
				std::cin >> choice;

				// Check if the input is valid
				if (std::cin.fail() || (choice != 1 && choice != 2 && choice != 3)) {
					std::cin.clear(); // Clear error flag
					// Discard invalid input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input. Please enter only 1 or 2." << std::endl;
				}
			} while (choice != 1 && choice != 2);

			// 1: Display general account information for each account
			if (choice == 1)
			{
				// View general accounts, pass a dummy userID string
				viewAccounts(accounts, choice, "f");
			}

			// 2: Display user-specific detailed account information
			else if (choice == 2)
			{
				std::cout << "Enter User ID: ";
				std::cin >> inpUserID;

				// Pass the inputted User ID to loop through the list to find the detailed information
				viewAccounts(accounts, choice, inpUserID);
			}
			// 3: Return to main menu
			else if (choice == 3)
			{
				break;
			}

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

	// Grab userID
	std::string userID;
	std::cout << "Enter your User ID: ";
	std::cin >> userID;

	// Use findAccount instead of accessing head directly
	Bank_Account* spendingAcc = accounts.findAccount(userID, SPENDING);

	if (!spendingAcc) {
		std::cout << "No spending account found!" << std::endl;
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
		std::cout << "\nEnter your choice: ";
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
			// Invalid input, display error message
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 5);
}
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

// Generic string number utility functions
template <typename T>
class NumericUtils {
public:
	// Generate a random number in between a range of 2 numbers
	static T randomRange(T min, T max) {
		// Random number generator
		std::random_device rd;
		std::mt19937_64 gen(rd());

		// Ensure the number is not out of range
		if (min > max) {
			std::cout << "\nInvalid range: min cannot be greater than max." << std::endl;
			return 0;
		}

		// Check if T is an integer
		if constexpr (std::is_integral_v<T>) {
			std::uniform_int_distribution<T> dis(min, max);

			// Return random integer
			return dis(gen);
		}
		else {
			std::uniform_real_distribution<T> dis(min, max);

			// Return random floating point number
			return dis(gen);
		}
	}

	// Boolean value to check if a number is in between two inputted numbers
	static bool isBetween(T value, T min, T max) {
		return (value >= min) && (value <= max);
	}

	// Clamp number values
	static T clamp(T value, T min, T max) {
		// If the value is less than the minimum, return the minimum
		if (value < min) {
			return min;
		}

		// If the value is greater than the maximum, return the maximum
		else if (value > max) {
			return max;
		}

		// Otherwise, return the original value
		else {
			return value;
		}
	}
};

// Generic string validation utility functions
template <typename T>
class StringValidationUtils {
public:
	// // Boolean value to check if a number is in between two inputted numbers, with an added output message
	// Inherits from NumericUtils version of isBetween
	static bool validateRange(T value, T min, T max, const std::string& message) {

		// If the number is not in between the values, output an error message and return
		if (!NumericUtils<T>::isBetween(value, min, max)) {
			std::cout << message << std::endl;
			return false;
		}
		return true;
	}

	// Prompts the user for input and ensures the value falls within the specified range
	// The function loops until the user enters a valid number
	static T getValidatedInput(const std::string& prompt, T min, T max) {
		T value;
		do {
			// Display prompt message
			std::cout << prompt;

			// Get user input
			std::cin >> value;

			// Check for any errors from the input
			if (std::cin.fail()) {
				std::cout << "Invalid input! Please enter a valid number.\n";

				// Clear error flags
				std::cin.clear();

				// Remove invalid input
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				continue;
			}

		} while (!validateRange(value, min, max, // Validate range
			"Invalid input! Value must be between " +
			std::to_string(min) + " and " + std::to_string(max)));

		// Return validated input
		return value;
	}
};

// Template for validating that a string is in between two set number values
// For example, a password must be in between 6 and 30 characters
template <size_t MinLen, size_t MaxLen>
class StringLengthValidator {
public:
	// Validate the length of the string is in between two number values
	static bool validate(const std::string& input) {
		return NumericUtils<size_t>::isBetween(input.length(), MinLen, MaxLen);
	}

	// Display an error message if the input is not in between those values
	// For my password example,
	// "Input must be at least 6 characters" or
	// "Input must be between 6 and 30 characters"
	static std::string getErrorMessage() {
		// Max range
		if constexpr (MaxLen == std::numeric_limits<size_t>::max())
			return "Input must be at least " + std::to_string(MinLen) + " characters";
		else
			return "Input must be between " + std::to_string(MinLen) +
			" and " + std::to_string(MaxLen) + " characters";
	}
};

// Type alias for password and physical address string length requirement
using AddressPasswordValidator = StringLengthValidator<6, 30>;

// Type alias for User ID string length requirement
using UserIDValidator = StringLengthValidator<5, 20>;

// Type alias for phone number string length requirement
using PhoneValidator = StringLengthValidator<10, 10>;

// Linked list node structure for bank account
struct AccountNode {
	Bank_Account* account;
	AccountNode* next;

	AccountNode(Bank_Account* acc) : account(acc), next(nullptr) {}
};

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

		// Check to see if userID is empty
		if (userID.empty()) {
			std::cout << "Error: User ID cannot be empty." << std::endl;
			return;
		}

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

				// Skip updating 'previous'
				continue;
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
	void updateAccountsForUser(const std::string& userIDToUpdate, const std::string& newUserID,
		const std::string& newPassword, const std::string& newFname,
		const std::string& newLname, const std::string& newEmail,
		const std::string& newAddress, char newGender, long long phoneLongLong) {

		AccountNode* current = head;
		while (current) {
			if (current->account->getUserID() == userIDToUpdate) {
				if (!newUserID.empty()) {
					current->account->setUserID(newUserID);
				}
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

// Generic function to get and validate user input
std::string getValidatedInput(const std::string& prompt, bool (*validateFunc)(const std::string&), const std::string& fieldName) {
	std::string input;
	while (true) {
		std::cout << prompt;
		std::getline(std::cin, input);

		// Check for empty input
		if (input.empty()) {
			std::cout << fieldName << " cannot be empty. Please try again.\n";
			continue;
		}

		// Validate input
		if (!validateFunc(input)) {
			continue;
		}

		// Input is non-empty and valid
		break;
	}
	return input;
}

// Generic function to get and validate user input, except this allows for blank inputs (useful for new inputs, such as new first name in updateAccount)
std::string getValidatedEmptyInput(const std::string& prompt, bool (*validateFunc)(const std::string&), const std::string& fieldName) {
	std::string input;
	while (true) {
		std::cout << prompt;
		std::getline(std::cin, input);

		// Check for empty input
		if (input.empty()) {
			return input;
		}

		// Validate input
		if (!validateFunc(input)) {
			continue;
		}

		// Input is non-empty and valid
		break;
	}
	return input;
}

// Function to validate non-empty input
bool validateNonEmpty(const std::string& input, const std::string& fieldName) {
	if (input.empty()) {
		std::cout << fieldName << " cannot be blank. Please try again.\n";
		return false;
	}
	return true;
}

// Function to validate names (letters, hyphens, apostrophes, and spaces)
bool validateName(const std::string& name) {
	std::regex pattern("^[A-Za-z-' ]{2,30}$");
	if (!std::regex_match(name, pattern)) {
		std::cout << "Invalid Name! Only letters, hyphens, and apostrophes allowed (2-30 characters).\n";
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

// Function to validate addresses (ensures length constraints)
bool validateAddress(const std::string& address) {
	// Get the length of the provided address
	size_t addressLength = address.length();

	// Clamp the length between 5 and 50 characters using NumericUtils
	size_t clampedLength = NumericUtils<size_t>::clamp(addressLength, 5, 50);

	// If the original length does not match the clamped length, it's invalid
	if (addressLength != clampedLength) {
		// Tell the user that the address length is out of bounds
		std::cout << "Address must be 5-50 characters long.\n";
		return false;
	}

	// If the length is valid, return true
	return true;
}

// Function to validate gender (M, F, O)
bool validateGender(const char gender) {
	if (gender != 'M' && gender != 'F' && gender != 'O') {
		std::cout << "Invalid gender! Enter M, F, or O.\n";
		return false;
	}
	return true;
}

// Function to validate phone numbers (10 digits)
bool validatePhoneNumber(const std::string& phone) {
	std::regex pattern(R"(^(\+\d{1,3}[-.\s]?)?(\d{1,4}[-.\s]?)?\d{3,4}[-.\s]?\d{3,4}$)");

	// Return phone number
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
	std::uniform_int_distribution<size_t> dis(0, chars.size() - 1);

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

	// Generate a random phone number
	long long phoneLongLong;
	phoneLongLong = NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL);


	// Create a default gender of "O"
	char defaultGender = 'O';

	// Create a default address
	std::string defaultAddress = "123 Random Street";

	// Add spending, reserve, and growth accounts
	try
	{
		// Add spending account
		accounts.addAccount(new Spending_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), randomUserID, defaultPassword, 1000.0f,
			fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
		));

		// Add reserve account
		accounts.addAccount(new Reserve_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), randomUserID, defaultPassword, 1000.0f,
			fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
		));

		// Add growth account
		accounts.addAccount(new Growth_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), randomUserID, defaultPassword, 1000.0f,
			fname, lname, randomEmail, phoneLongLong, defaultGender, defaultAddress, 0.00f
		));
	}

	// Catch any exceptions
	catch (const std::exception& e)
	{
		std::cout << Separator();
		std::cout << "Exception occurred while generating random banking accounts!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
		throw;
	}


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
	// Initialize variables for the user's information
	std::string userID, password, fname, lname, email, address, phone;
	char gender;
	long long int phoneLongLong = 0;

	// Defining a regex for local whitespace removal
	std::regex r("\\s+");

	// Validate User ID
	do {
		std::cout << "Enter User ID (or type 100 to generate a random account): ";
		std::getline(std::cin, userID);

		// Generate a random account (mostly for debugging)
		if (userID == "100") {
			generateRandomAccount(accounts);

			// Exit after generating random accounts
			return;
		}

		// Validate User ID length
		if (!UserIDValidator::validate(userID)) {
			std::cout << UserIDValidator::getErrorMessage() << "\n";
		}

	} while (!UserIDValidator::validate(userID) || accounts.userExists(userID));

	// Trim the userID
	userID = std::regex_replace(userID, r, "");

	// Debug Output of userID
	// std::cout << userID << std::endl;

	// Validate Password
	do {
		std::cout << "Enter Password: ";
		std::getline(std::cin, password);

		// Validate password length
		if (!AddressPasswordValidator::validate(password)) {
			std::cout << AddressPasswordValidator::getErrorMessage() << "\n";
		}
	} while (!AddressPasswordValidator::validate(password));

	// Trim the password
	password = std::regex_replace(password, r, "");

	// Validate First Name
	fname = getValidatedInput("First Name: ", validateName, "First Name");

	// Validate Last Name
	lname = getValidatedInput("Last Name: ", validateName, "Last Name");

	// Validate Email
	email = getValidatedInput("Email: ", validateEmail, "Email");

	// Validate Address
	address = getValidatedInput("Address: ", validateAddress, "Address");

	// Validate Gender
	std::string genderInput = getValidatedInput("Enter gender (M/F/O): ",
		[](const std::string& input) { return !input.empty() && validateGender(input[0]); }, "Gender");

	// Extract character for gender (convert to Char)
	gender = genderInput.empty() ? '\0' : genderInput[0];

	// Validate Phone Number
	do {
		phone = getValidatedInput("Phone Number: ", validatePhoneNumber, "Phone Number");

		// Validate phone string length
		if (!PhoneValidator::validate(phone)) {
			std::cout << PhoneValidator::getErrorMessage() << "\n";
		}
	} while (!PhoneValidator::validate(phone));


	// Convert user's Phone Number from string to long long
	phoneLongLong = std::stoll(phone);

	// Account information:
	// int accountNumber, string& userID, string& userPassword, float balance, string& ownerFirstName, string& ownerLastName,
	// string& ownerEmail, int ownerPhoneNumber, char ownerGender, std::string& ownerAddress, float overDraftLimit

	try
	{
		// Add the spending account
		accounts.addAccount(new Spending_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), userID, password, 1000.0f,
			fname, lname, email, phoneLongLong, gender, address, 0.00f
		));

		// Add the reserve account
		accounts.addAccount(new Reserve_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), userID, password, 1000.0f,
			fname, lname, email, phoneLongLong, gender, address, 0.00f
		));

		// Add the growth account
		accounts.addAccount(new Growth_Account(
			NumericUtils<long long>::randomRange(1000000000LL, 9999999999LL), userID, password, 1000.0f,
			fname, lname, email, phoneLongLong, gender, address, 0.00f
		));
	}
	// Catch any exceptions
	catch (const std::exception& e)
	{
		std::cout << Separator();
		std::cout << "Exception occurred while generating creating new bank accounts!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
		throw;
	}

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
	std::cout << std::endl;

	// Check if the user exists
	if (!accounts.userExists(userID)) {
		std::cout << "User ID not found. Cannot update account.\n";
		return;
	}

	// Get updated information
	std::string newUserID, newPassword, newFname, newLname, newEmail, newAddress, phone;
	char newGender;
	long long phoneLongLong;

	// Get and validate new User ID
	newUserID = getValidatedEmptyInput("Enter new User ID (or leave blank to keep current): ", validateName, "User ID");

	// Get and validate new password
	do {
		std::cout << "Enter new Password (or leave blank to keep current): ";
		std::getline(std::cin, newPassword);
		if (!newPassword.empty() && newPassword.length() < 6) {
			std::cout << "Password must be at least 6 characters long.\n";
		}
	} while (!newPassword.empty() && newPassword.length() < 6);

	// Get and validate new first and last name
	newFname = getValidatedEmptyInput("Enter new First Name (or leave blank to keep current): ", validateName, "First Name");
	newLname = getValidatedEmptyInput("Enter new Last Name (or leave blank to keep current): ", validateName, "Last Name");

	// Get and validate new email
	newEmail = getValidatedEmptyInput("Enter new Email (or leave blank to keep current): ", validateEmail, "Email");

	// Get and validate new address
	newAddress = getValidatedEmptyInput("Enter new Address (or leave blank to keep current): ", validateAddress, "Address");

	// Get and validate new gender
	std::string genderInput = getValidatedEmptyInput("Enter new Gender (M/F/O, or leave blank to keep current): ",
		[](const std::string& input) { return !input.empty() && validateGender(input[0]); }, "Gender");

	// Extract character for gender (convert to Char)
	newGender = genderInput.empty() ? '\0' : genderInput[0];

	// Get and validate new phone number
	phone = getValidatedEmptyInput("Enter new Phone number (or leave blank to keep current): ", validatePhoneNumber, "Phone Number");

	if (phone.empty())
	{ 
		phone = "9999999999";
	}

	// Convert user's Phone Number from string to long long
	phoneLongLong = std::stoll(phone);

	// Update accounts
	try
	{
		accounts.updateAccountsForUser(userID, newUserID, newPassword, newFname, newLname, newEmail, newAddress, newGender, phoneLongLong);
	}
	// Catch any exceptions
	catch (const std::exception& e)
	{
		std::cout << Separator();
		std::cout << "Exception occurred while updating your bank account!" << std::endl;
		std::cout << "Exception: " << e.what() << std::endl;
		throw;
	}

	std::cout << "Account updated successfully!\n";
}


// Transaction System
void transactionSystem(AccountList& accounts) {
	// Initialize a variable to get the user's ID
	std::string userID;
	std::cout << "\nEnter your User ID: ";
	std::cin >> userID;

	// Use findAccount instead of accessing head directly
	Bank_Account* spendingAcc = accounts.findAccount(userID, SPENDING);

	if (!spendingAcc) {
		std::cout << "No accounts found!" << std::endl;
		return;
	}

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
				<< "1. Spending\n2. Reserve\n3. Growth" << std::endl;

			// Validate account type input
			accountType = StringValidationUtils<int>::getValidatedInput(
				"\nSelect Account Type (1-3): ", 1, 3
			);

			// Display message for the amount to deposit
			std::cout << "Enter amount to deposit: $";

			// Get input for the amount of money to deposit
			std::cin >> amount;

			// Validate amount input
			if (std::cin.fail() || amount <= 0) {
				// Clear the error flag
				std::cin.clear();

				// Ignore invalid input
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// Output error message
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
			std::cout << "Select Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth" << std::endl;

			// Validate account type input
			accountType = StringValidationUtils<int>::getValidatedInput(
				"\nSelect Account Type (1-3): ", 1, 3
			);

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
				<< "1. Spending\n2. Reserve\n3. Growth" << std::endl;

			// Validate source account type input
			sourceAccountType = StringValidationUtils<int>::getValidatedInput(
				"\nSelect Account Type (1-3): ", 1, 3
			);

			// Display message for destination account type selection
			std::cout << "\nSelect Destination Account Type:\n"
				<< "1. Spending\n2. Reserve\n3. Growth" << std::endl;

			// Validate destination account type input
			destinationAccountType = StringValidationUtils<int>::getValidatedInput(
				"\nSelect Account Type (1-3): ", 1, 3
			);

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
				<< "1. Spending\n2. Reserve\n3. Growth" << std::endl;

			// Validate account type input
			accountType = StringValidationUtils<int>::getValidatedInput(
				"\nSelect Account Type (1-3): ", 1, 3
			);

			AccountType type;
			switch (accountType) {
			case 1: type = SPENDING; break;
			case 2: type = RESERVE; break;
			case 3: type = GROWTH; break;
			default:
				std::cout << "Invalid account type!\n";
				continue;
			}

			// Search for user's account
			Bank_Account* account = accounts.findAccount(userID, type);
			if (!account) {
				std::cout << "Account not found!" << std::endl;
				continue;
			}

			// Display all transactions
			std::cout << "\nTransactions for " << userID << " ("
				<< (type == SPENDING ? "Spending" : type == RESERVE ? "Reserve" : "Growth")
				<< " Account):" << std::endl;

			account->displayTransactions();
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
	std::cout << "6. Store System" << std::endl;
	std::cout << "7. Exit" << std::endl;
	std::cout << "8. Test Cases for Templates and Exception Handling" << std::endl;
	std::cout << "\nEnter your choice: ";
}

int main() {
	// Create a Store object
	Store store;

	// Test Case Variables
	int test1_case1, test1_case2, test4_case1, test4_case2, test4_case3;
	std::string test5_case1, test5_case2;
	bool test3_case1, test3_case2, test6_case1, test6_case2, test6_case3;
	float test2_case1, test2_case2;

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
			// Catch any exceptions
			catch (const std::exception& e)
			{
				std::cout << Separator();
				std::cout << "Exception occurred while generating random banking accounts!" << std::endl;
				std::cout << "Exception: " << e.what() << std::endl;
				throw;
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

					// Clear error flag
					std::cin.clear();

					// Remove invalid input
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					// Error message output
					std::cout << "Invalid input. Please enter 1, 2, or 3." << std::endl;
				}
			} while (choice != 1 && choice != 2 && choice != 3);

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
			// Case 6: Pass the store object to storeSystem
			storeSystem(store, accounts);
			break;

		case 7:
			// Case 7: Exit the program
			std::cout << "Exiting the program..." << std::endl;
			break;

		case 8:
			// Case 8: Test cases



			// -- Test #1: NumericUtils::randomRange() - Integer Range

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #1 -- --: NumericUtils::randomRange() - Integer Range" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;


			// Test 1 Case 1
			std::cout << "\n1. Test Case: Call NumericUtils<int>::randomRange(10, 20)" << std::endl;
			std::cout << "\n2. Expected Result: A random integer between 10 and 20. The integer must fall within the specified range." << std::endl;

			test1_case1 = NumericUtils<int>::randomRange(10, 20);
			std::cout << "\n3. Output of NumericUtils<int>::randomRange(10, 20): " << test1_case1 << std::endl;

			std::cout << Separator();

			// Test 1 Case 2
			std::cout << "\n1. Exception Test: Call NumericUtils::randomRange<int>(20, 10)." << std::endl;
			std::cout << "\n2. Expected Result: an error message is display stating 'Invalid range: min cannot be greater than max.'." << std::endl;

			test1_case2 = NumericUtils<int>::randomRange(20, 10);




			// -- Test #2: NumericUtils::randomRange() - Floating-Point Range

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #2 -- --: NumericUtils::randomRange() - Floating-Point Range" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;


			// Test 2 Case 1
			std::cout << "\n1. Test Case: Call NumericUtils<float>::randomRange(5.5f, 10.5f)." << std::endl;
			std::cout << "\n2. Expected Result: A random float between 5.5 and 10.5. The float must fall within the specified range." << std::endl;

			test2_case1 = NumericUtils<float>::randomRange(5.5f, 10.5f);
			std::cout << "\n3. Output of NumericUtils<float>::randomRange(5.5f, 10.5f): " << test2_case1 << std::endl;

			std::cout << Separator();

			// Test 2 Case 2
			std::cout << "\n1. Exception Test: Call NumericUtils<float>::randomRange(10.0f, 5.5f)." << std::endl;
			std::cout << "\n2. Expected Result: an error message is display stating 'Invalid range: min cannot be greater than max.'." << std::endl;

			test2_case2 = NumericUtils<float>::randomRange(10.0f, 5.5f);




			// -- Test #3: NumericUtils::isBetween() - Integer Value

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #3 -- --: NumericUtils::isBetween() - Integer Value" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;


			// Test 3 Case 1
			std::cout << "\n1. Test Case: Call NumericUtils::isBetween<int>(15, 10, 20)." << std::endl;
			std::cout << "\n2. Expected Result: 1 (which means True)" << std::endl;

			test3_case1 = NumericUtils<int>::isBetween(15, 10, 20);

			std::cout << "\n3. Output of NumericUtils<int>::isBetween(15, 10, 20): " << test3_case1 << std::endl;

			std::cout << Separator();

			// Test 3 Case 2
			std::cout << "\n1. Test Case: Call NumericUtils::isBetween<int>(5, 10, 20)." << std::endl;
			std::cout << "\n2. Expected Result: 0 (which means False)" << std::endl;

			test3_case2 = NumericUtils<int>::isBetween(5, 10, 20);

			std::cout << "\n3. Output of NumericUtils<int>::isBetween(5, 10, 20): " << test3_case2 << std::endl;




			// -- Test #4: NumericUtils::clamp() - Integer Value

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #4 -- --: NumericUtils::clamp() - Integer Value" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;


			// Test 4 Case 1
			std::cout << "\n1. Test Case: Call NumericUtils<int>::clamp(15, 10, 20)." << std::endl;
			std::cout << "\n2. Expected Result: 15" << std::endl;

			test4_case1 = NumericUtils<int>::clamp(15, 10, 20);

			std::cout << "\n3. Output of NumericUtils<int>::clamp(15, 10, 20): " << test4_case1 << std::endl;

			std::cout << Separator();

			// Test 4 Case 2
			std::cout << "\n1. Test Case: Call NumericUtils<int>::clamp(5, 10, 20)." << std::endl;
			std::cout << "\n2. Expected Result: 10" << std::endl;

			test4_case2 = NumericUtils<int>::clamp(5, 10, 20);

			std::cout << "\n3. Output of NumericUtils<int>::clamp(5, 10, 20): " << test4_case2 << std::endl;

			// Test 4 Case 3
			std::cout << "\n1. Test Case: Call NumericUtils<int>::clamp(25, 10, 20)." << std::endl;
			std::cout << "\n2. Expected Result: 20" << std::endl;

			test4_case3 = NumericUtils<int>::clamp(25, 10, 20);

			std::cout << "\n3. Output of NumericUtils<int>::clamp(25, 10, 20): " << test4_case3 << std::endl;





			// -- Test #5: StringValidationUtils::validateRange() - Integer Value

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #5 -- --: StringValidationUtils::validateRange() - Integer Value" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;


			// Test 5 Case 1
			std::cout << "\n1. Test Case: Call StringValidationUtils<int>::validateRange(15, 10, 20, 'Error: Value out of range.'" << std::endl;
			std::cout << "\n2. Expected Result: No error message should be printed." << std::endl;

			test5_case1 = StringValidationUtils<int>::validateRange(15, 10, 20, "Error: Value out of range.");

			std::cout << "\n3. Output of StringValidationUtils<int>::validateRange(15, 10, 20, 'Error: Value out of range.': " << test5_case1 << std::endl;

			std::cout << Separator();



			// Test 5 Case 2
			std::cout << "\n1. Test Case: Call StringValidationUtils<int>::validateRange(5, 10, 20, 'Error: Value out of range.'" << std::endl;
			std::cout << "\n2. Expected Result: 'Error: Value out of range.'." << std::endl;

			test5_case2 = StringValidationUtils<int>::validateRange(5, 10, 20, "\nError: Value out of range.");





			// -- Test #6: StringLengthValidator::validate()

			std::cout << Separator();

			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;
			std::cout << "\n -- -- Test #6 -- --: StringLengthValidator::validate()" << std::endl;
			std::cout << "\n+++ +++ ++ ++ + +" << std::endl;

			std::cout << "\nTest Setup: 'using PasswordValidator = StringLengthValidator<6, 30>'" << std::endl;
			using PasswordValidator = StringLengthValidator <6, 30>;


			// Test 6 Case 1
			std::cout << "\n1. Test Case: Call 'PasswordValidator::validate('password')'" << std::endl;
			std::cout << "\n2. Expected Result: 1 (which means True)" << std::endl;

			test6_case1 = PasswordValidator::validate("password");

			std::cout << "\n3. Output of PasswordValidator::validate('password'): " << test6_case1 << std::endl;

			std::cout << Separator();



			// Test 6 Case 2
			std::cout << "\n1. Test Case: Call 'PasswordValidator::validate('milk')'" << std::endl;
			std::cout << "\n2. Expected Result: 0 (which means False)" << std::endl;

			test6_case2 = PasswordValidator::validate("milk");

			std::cout << "\n3. Output of PasswordValidator::validate('milk'): " << test6_case2 << std::endl;

			std::cout << Separator();



			// Test 6 Case 3
			std::cout << "\n1. Test Case: Call 'PasswordValidator::validate('ThisIsAVeryLongAndVeryCoolPassword123456789')'" << std::endl;
			std::cout << "\n2. Expected Result: 0 (which means False)" << std::endl;

			test6_case3 = PasswordValidator::validate("ThisIsAVeryLongAndVeryCoolPassword123456789");

			std::cout << "\n3. Output of PasswordValidator::validate('ThisIsAVeryLongAndVeryCoolPassword123456789'): " << test6_case3 << std::endl;

			std::cout << Separator();





			// End
			std::cout << "\nThat concludes the Test Cases for Templates and Exception Handling!" << std::endl;
			break;

		default:
			// Invalid input error message
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 7);

	return 0;
}

// 7. Implement the storeSystem function
void storeSystem(Store& store, AccountList& accounts) {
	// Grab userID
	std::string userID;
	std::cout << "Enter your User ID: ";
	std::cin >> userID;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	// Use findAccount instead of accessing head directly
	Bank_Account* spendingAcc = accounts.findAccount(userID, SPENDING);

	if (!spendingAcc) {
		std::cout << "No accounts found!" << std::endl;
		return;
	}

	// Set the current account in the store
	store.setCurrentAccount(spendingAcc);

	int choice;
	do {
		std::cout << "\nStore System Menu:" << std::endl;
		std::cout << "1. Display Catalog" << std::endl;
		std::cout << "2. Add to Cart" << std::endl;
		std::cout << "3. Display Cart" << std::endl;
		std::cout << "4. Checkout" << std::endl;
		std::cout << "5. Return to Main Menu" << std::endl;
		std::cout << "\nEnter your choice: ";

		// Get user input
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		switch (choice) {
		case 1:
			// Case 1: Display Catalog
			store.displayCatalog();
			break;
		case 2: {
			// Case 2: Add to Cart
			std::string productName;
			std::cout << "Enter product name: ";
			std::getline(std::cin, productName);

			using ProductNameValidator = StringLengthValidator<1, 50>;
			if (!ProductNameValidator::validate(productName)) {
				std::cout << ProductNameValidator::getErrorMessage() << std::endl;
				break;
			}

			int quantity = StringValidationUtils<int>::getValidatedInput("Enter quantity: ", 1, 1000);

			store.addToCart(productName, quantity);
			break;
		}
		case 3:
			// Case 3: Display cart
			store.displayCart();
			break;

		case 4: {
			// Case 4: Checkout
			try {
				// Call store.checkout()
				store.checkout();
			}

			// Handle exceptions from checkout
			catch (const std::runtime_error& e) {
				std::cout << "Checkout failed: " << e.what() << std::endl;
				std::cout << "Remaining balance: $" << spendingAcc->getBalance() << std::endl;
			}
			break;
		}
		case 5:
			// Case 5: Return to main menu
			std::cout << "Returning to main menu..." << std::endl;
			break;
		default:
			// Invalid input, display error message
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	} while (choice != 5);
}
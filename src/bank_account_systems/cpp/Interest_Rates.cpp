#include "../headers/Interest_Rates.h"

// The purpose of this class is to dynamically allocate the interest rates for each respective account type.
/* The following are examples of these interest rates being allocated:
  - There are three main account types:
	- **Spending**:
	  - No interest.
	- **Reserve**:
	  - The balance to earn interest is a fixed $1.00 minimum, with an Interest Rate / APY of 0.01%.
	- **Growth**:
	  - For balances between $1.00 and $2,499.99, the Interest Rate / APY is 0.02%.
	  - For balances at $2,500.00 and above, the Interest Rate / APY is 0.03%.
*/

// Constructor to initialize interest based on account type
InterestRate::InterestRate(AccountType type) : accountType(type) {

	// Check to see if the account is a valid type
	if (type != SPENDING && type != RESERVE && type != GROWTH) {
		throw std::invalid_argument("Invalid AccountType provided.");
	}

	if (type == RESERVE) {
		// Fixed rate for Reserve accounts
		baseRate = 0.01f;
	}
	else if (type == GROWTH) {
		// Default to lower tier Growth rate
		baseRate = 0.02f;
	}
	else {
		// No interest for Spending accounts
		baseRate = 0.0f;
	}
}

// Method to determine applicable rate based on balance
float InterestRate::getRate(float balance) const {
	if (accountType == GROWTH) {
		if (balance >= 2500.00f) {
			// Higher rate for balances above $2500
			return 0.03f;
		}
		else if (balance >= 1.00f) {
			// Lower rate for balances between $1 and $2499.99
			return 0.02f;
		}
	}
	else if (accountType == RESERVE) {
		if (balance >= 1.00f) {
			// Fixed rate for Reserve
			return baseRate;
		}
	}
	// No interest for Spending or insufficient balance
	return 0.0f;
}

// Calculate simple interest based on balance, years, and applicable rate
float InterestRate::calculateInterest(float balance, int years) const {
	float applicableRate = getRate(balance);
	// Simple interest: P * r * t
	return (balance * (applicableRate / 100)) * years;
}

// Compound interest: A = P(1 + r/n)^nt
// Takes in variables for account balance, amount of years, and how many times the interest compounds per year
// As an example, a reserve account that has a balance of $1000 will have $1000.5 after 5 years while compounding once a year at an interest rate of 0.01%
float InterestRate::calculateCompoundInterest(float balance, int years, int compoundPerYear) const {
	float applicableRate = getRate(balance) / 100;
	return balance + balance * pow((1 + applicableRate / compoundPerYear), compoundPerYear * years) - balance;
}
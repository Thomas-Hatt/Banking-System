#ifndef INTERESTRATES_H
#define INTERESTRATES_H

#include "Bank_Account.h"

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

class InterestRate {
private:
	// Variable to store the base interest rate
	float baseRate;

	// Store the account type to determine applicable rates
	AccountType accountType;

public:
	// Constructor: Initialize interest based on account type
	InterestRate(AccountType type);

	// Calculate simple interest based on account type and balance
	float calculateInterest(float balance, int years) const;

	// Calculate compound interest based on account type and balance
	float calculateCompoundInterest(float balance, int years, int compoundPerYear) const;

	// Get the current interest rate for the account type
	float getRate(float balance) const;
};

#endif // INTERESTRATES_H
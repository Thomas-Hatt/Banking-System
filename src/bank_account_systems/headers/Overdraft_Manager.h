#ifndef OVERDRAFT_MANAGER_H
#define OVERDRAFT_MANAGER_H

#include <iostream>

class Overdraft_Manager {
private:
	// Max overdraft allowed
	float overdraftLimit;

public:
	Overdraft_Manager(float limit) : overdraftLimit(limit) {}

	// Check if withdrawal is allowed within overdraft limit
	bool isWithdrawalAllowed(float balance, float amount) const {
		return (balance - amount >= -overdraftLimit);
	}

	float getOverdraftLimit() const { return overdraftLimit; }
};

#endif // OVERDRAFT_MANAGER_H
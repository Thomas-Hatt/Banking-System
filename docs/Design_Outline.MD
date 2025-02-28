### Purpose of This Document

The purpose of this document is to define the general outline of how this program will be created. I go over the basics in the file `Bank_Feature_Analysis.MD`; however, this document will be more feature-filled than that one.

---

## 1. Bank Account Systems

The abstract version of these accounts, referred to as "Abstract Bank Account", will include:

- Account type
- Owner's personally identifiable information (name, age, gender, etc.)
- Account number
- Account balance
- Interest rate

The user will be able to:

- Update their information
- Authenticate their user ID and password matches those stored within the program during login
- Create and delete accounts if they so please

The Abstract Bank Account will have basic transaction management, including:

- Deposit
- Withdraw
- Transfer

Additionally, there will be an overdraft protection implementation to prevent users from spending/withdrawing more money than they have.

## 2. Loan Systems

As described in `Bank_Feature_Analysis`, each loan will be treated as a 12-month loan with the rate rounded towards the middle. Unique identifiers for each loan will include:

- Loan ID
- Borrower's information
- Loan amount
- Interest rate
- Loan term
- Start date
- Expected payoff date

The loans will need to have a repayment system, which will be categorized into:

- Installments (monthly, quarterly, yearly, etc.)
- Interest
- Prepayment options

## 3. Interest Systems

Interest rates will be calculated at a Fixed Interest Rate using the formula:

`Simple Interest = P * r * t`

where:

- `P` is the Principal amount
- `r` is the Annual interest rate
- `t` is the time period in years

Accounts have a balance requirement to earn interest.

## 4. Store Systems

The "store" is a small subsystem where users can spend their money to purchase items. The store system will include:

- **Product Catalog**: Bread, Milk, Chicken, Cereal, and Water
- **Product Details**: Name, price, quantity
- **Shopping Cart**: Items that the user has added to their cart
- **Checkout System**: Deducts the total cost from the user's bank account (must be a spending account) and updates the store's inventory to reflect what was purchased

Upon purchasing the items, they will show up in the transaction history of the user's bank account.

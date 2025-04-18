### Purpose of This Document

The purpose of this document is to provide an overview of features that are included in my analysis of PNC Bank. I chose PNC Bank for my analysis since I use that for my regular banking activities, so I would have a solid grasp of how it works internally without looking at many external sources for guidance.

It's important to note that these features are not exactly the same as how PNC Bank operates, nor does this program function in the same way as PNC Bank or any other banking program.

---

1. **Account Management**
  - Banking systems have the functionality of account management. You can create accounts, update your accounts, and delete your accounts if needed. My program won't work the same, as I'll be dealing with plain text storage instead of encrypted storage in a database.

2. **Account Types**
  - There are three main account types. I'm going to analyze them by their current interest rates for the Virtual Wallet Student as of 2/26/2025.
    - **Spending**:
      - No interest.
    - **Reserve**:
      - The balance to earn interest is a fixed $1.00 minimum, with an Interest Rate / APY of 0.01%.
    - **Growth**:
      - For balances between $1.00 and $2,499.99, the Interest Rate / APY is 0.02%.
      - For balances at $2,500.00 and above, the Interest Rate / APY is 0.03%.

3. **Transaction Review**
  - An ability to review past transactions. There's the main "store" where the user can spend their money. They can review previous transactions from this store, including how many items they bought, the price of the transaction, as well as the date they purchased the items. The user will also be able to withdraw, deposit, and transfer money.

4. **User Authentication**
  - As I stated previously, encryption is not an option so details will be stored locally and authenticated using comparison techniques.

5. **Loan System**
  - For this, I'm going to use the *Personal Unsecured Installment Loan* for my local Zip Code and get the rates for a 12-month period. I'm going to round to the middle of the range for consistency. For example, the rates range for a $1,000 loan is between 12.79% and 24.74%. I'm going to round this to 18.77%.

  - **Loan Amounts and Rates**:
    - **$1,000**: 18.77%
    - **$2,500**: 18.77%
    - **$5,000**: 16.07%
    - **$10,000**: 15.82%
    - **$15,000**: 13.87%
    - **$35,000**: 13.87%

6. **Store System**
  - Small store system. I will include a small store system that the user can purchase items from (because what's the point of having money if you can't use it?). This store system will include some basic items, including Bread, Milk, Chicken, Cereal, and Water. The user can spend their money at this store.

7. **Overdraft Warning**
- Create a valid system to ensure that the user cannot withdraw or spend more money than they have in their account.

Links:
https://www.pnc.com/content/dam/pnc-com/pdf/personal/Checking/VW_Student_fees.pdf
https://www.pnc.com/en/rates/virtual-wallet/33414/NA
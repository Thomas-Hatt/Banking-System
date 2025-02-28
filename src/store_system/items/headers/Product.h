//
// Created by conta on 2/27/2025.
//

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <iostream>


class Product {
    public:
      // Constructor
      Product(const std::string &productName, double price, int quantity);

      // Default constructor
      Product();

      // Getters
      std::string getProductName() const;
      double getPrice() const;
      int getQuantity() const;

      // Setters
      void setPrice(double price);
      void setQuantity(int quantity);

      // Other methods
      void updateQuantity(int quantity);
      void displayProductInfo() const;

      private:
        std::string productName;
        double price;
        int quantity;
};

#endif //ITEMS_H

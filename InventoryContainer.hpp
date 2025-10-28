#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Product.hpp"
#include "MyHashTable.hpp"
using namespace std;

class InventoryContainer {
    public:
        //constructor
        InventoryContainer() = default;

        //destructor
        ~InventoryContainer() = default;

        //member functions
        bool loadCSV(const string& filename);
        
        //accessors
        Product* getProductById(const string& uniqId);
        vector<Product> getProductsByCategory(const string& category);

    private:
        //data members
        MyHashTable<string, Product> mProductsById;
        MyHashTable<string, vector<Product>> mProductsByCategory;

        //private member functions
        string readCSVField(stringstream& ss);

};
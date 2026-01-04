#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <iostream>
#include <fstream>
using namespace std;

struct Products{
    int ID;
    string name;
    string description;
    int price;
    int quantity;
};

// Function declarations
int addProducts(Products &product, fstream &file);
int updateProducts(Products &product, fstream &file, fstream &temp);
int deleteProducts(Products &product, fstream &file, fstream &temp);
int searchProducts(Products &product, fstream &file);
int allProducts(Products &product, fstream &file);
int products();

#endif

#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <fstream>
using namespace std;

struct Customers {
    int ID;
    string name;
    string phone;
    string type;
};

// Function declarations
int addCustomers(Customers &customer, fstream &file);
int updateCustomers(Customers &customer, fstream &file, fstream &temp);
int deleteCustomers(Customers &customer, fstream &file, fstream &temp);
int searchCustomers(Customers &customer, fstream &file);
int allCustomers(Customers &customer, fstream &file);
int customers();

#endif

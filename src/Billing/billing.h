#ifndef BILLING_H
#define BILLING_H

#include <string>
#include <vector>

using namespace std;

struct Bill
{
    int Bill_ID;
    int Transaction_ID;
    int Customer_ID;
    int Sub_Total;
    int Tax;
    int Discount;
    int Grand_Total;
    string DateTime;
};

// Function prototype
int billing();

#endif

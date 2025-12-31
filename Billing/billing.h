#ifndef BILLING_H
#define BILLING_H

#include <string>
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

int generateBill(Bill &bill, fstream &file);
int searchBill(Bill &bill, fstream &file);
int allBills(Bill &bill, fstream &file);
int billing();

#endif

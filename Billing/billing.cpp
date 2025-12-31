#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "billing.h"

using namespace std;

int billing()
{
    Bill bill;
    fstream file;

    // Generate current DateTime
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char dateTime[20];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", ltm);

    int choice;
    do
    {
        cout << "\n--------==== Billing Menu ====--------"
             << "\nGenerate Bill .....PRESS 1"
             << "\nExit to main menu..PRESS 0"
             << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            // ================= Step 1: Read Bill Counter =================
            file.open("Billing/counter.txt", ios::in);
            if (!file.is_open())
            {
                cout << "Error opening counter.txt\n";
                return 0;
            }

            string count;
            getline(file, count);
            bill.Bill_ID = stoi(count);
            file.close();

            cout << "\n--------==== Generate Bill ====--------\n";
            cout << "Enter Transaction ID: ";
            cin >> bill.Transaction_ID;

            // ================= Step 2: Fetch Transaction =================
            fstream transFile("Transactions/transactions.csv", ios::in);
            if (!transFile.is_open())
            {
                cout << "Error opening transactions.csv\n";
                return 0;
            }

            string line;
            bool transFound = false;
            getline(transFile, line); // skip header

            while (getline(transFile, line))
            {
                stringstream ss(line);
                string tidStr, cidStr, pidStr, qtyStr, totalStr, dateStr;

                getline(ss, tidStr, ',');
                getline(ss, cidStr, ',');
                getline(ss, pidStr, ',');
                getline(ss, qtyStr, ',');
                getline(ss, totalStr, ',');
                getline(ss, dateStr); // last column

                if (stoi(tidStr) == bill.Transaction_ID)
                {
                    bill.Customer_ID = stoi(cidStr);
                    bill.Sub_Total = stoi(totalStr);
                    transFound = true;
                    break;
                }
            }
            transFile.close();

            if (!transFound)
            {
                cout << "Transaction not found.\n";
                return 0;
            }

            // ================= Step 3: Fetch Customer Type =================
            fstream custFile("Customers/customers.csv", ios::in);
            if (!custFile.is_open())
            {
                cout << "Error opening customers.csv\n";
                return 0;
            }

            string custLine, customerType;
            bool custFound = false;
            getline(custFile, custLine); // skip header

            while (getline(custFile, custLine))
            {
                stringstream ss(custLine);
                string idStr, nameStr, phoneStr, typeStr;

                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, phoneStr, ',');
                getline(ss, typeStr);

                typeStr.erase(0, typeStr.find_first_not_of(" "));
                typeStr.erase(typeStr.find_last_not_of(" ") + 1);
                customerType = typeStr;
                
                if (stoi(idStr) == bill.Customer_ID)
                {
                    customerType = typeStr;
                    custFound = true;
                    break;
                }
            }
            custFile.close();

            if (!custFound)
            {
                cout << "Customer not found.\n";
                return 0;
            }

            // ================= Step 4: Calculate Discount (NO TAX) =================
            bill.Tax = 0;

            if (customerType == "regular" || customerType == "Regular")
                bill.Discount = bill.Sub_Total * 0.05;
            else
                bill.Discount = 0;

            bill.Grand_Total = bill.Sub_Total - bill.Discount;
            bill.DateTime = dateTime;

            // ================= Step 5: Increment Bill ID =================
            bill.Bill_ID++;

            // ================= Step 6: Save Bill =================
            file.open("Billing/billing.csv", ios::out | ios::app);
            if (!file.is_open())
            {
                cout << "Error opening billing.csv\n";
                return 0;
            }

            file << bill.Bill_ID << ","
                 << bill.Transaction_ID << ","
                 << bill.Customer_ID << ","
                 << bill.Sub_Total << ","
                 << bill.Tax << ","
                 << bill.Discount << ","
                 << bill.Grand_Total << ","
                 << bill.DateTime << "\n";

            file.close();

            // ================= Step 7: Update Counter =================
            file.open("Billing/counter.txt", ios::out);
            if (!file.is_open())
            {
                cout << "Error updating counter.txt\n";
                return 0;
            }
            file << bill.Bill_ID;
            file.close();

            // ================= Step 8: Show Bill =================
            cout << "\n=========== BILL RECEIPT ===========\n";
            cout << "Bill ID        : " << bill.Bill_ID << endl;
            cout << "Transaction ID : " << bill.Transaction_ID << endl;
            cout << "Customer ID    : " << bill.Customer_ID << endl;
            cout << "Customer Type  : " << customerType << endl;
            cout << "-----------------------------------\n";
            cout << "Sub Total      : " << bill.Sub_Total << endl;
            cout << "Discount       : " << bill.Discount << endl;
            cout << "-----------------------------------\n";
            cout << "Grand Total    : " << bill.Grand_Total << endl;
            cout << "Date & Time    : " << bill.DateTime << endl;
            cout << "===================================\n";

            cout << "Bill generated successfully.\n";
        }
        else if (choice != 0)
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

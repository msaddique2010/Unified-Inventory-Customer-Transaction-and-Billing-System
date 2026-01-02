#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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
    char dateTimeArr[20];
    strftime(dateTimeArr, sizeof(dateTimeArr), "%Y-%m-%d %H:%M:%S", ltm);
    string dateTime(dateTimeArr);

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
            // Step 1: Read last Bill ID from counter.txt
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

            cout << "\nEnter Transaction ID to generate bill: ";
            cin >> bill.Transaction_ID;

            // Step 2: Sum all products for this transaction
            fstream transFile("Transactions/transactions.csv", ios::in);
            if (!transFile.is_open())
            {
                cout << "Error opening transactions.csv\n";
                return 0;
            }

            string line;
            bill.Sub_Total = 0;
            int customerID = 0;
            vector<pair<int,int>> products; // productID, qty
            vector<int> amounts;

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
                getline(ss, dateStr);

                if (stoi(tidStr) == bill.Transaction_ID)
                {
                    customerID = stoi(cidStr);
                    int pid = stoi(pidStr);
                    int qty = stoi(qtyStr);
                    int amt = stoi(totalStr);

                    products.push_back({pid, qty});
                    amounts.push_back(amt);
                    bill.Sub_Total += amt;
                }
            }
            transFile.close();

            if (products.empty())
            {
                cout << "Transaction not found.\n";
                continue;
            }

            bill.Customer_ID = customerID;

            // Step 3: Fetch customer type
            fstream custFile("Customers/customers.csv", ios::in);
            if (!custFile.is_open())
            {
                cout << "Error opening customers.csv\n";
                return 0;
            }

            string custLine, customerType;
            getline(custFile, custLine); // skip header
            while (getline(custFile, custLine))
            {
                stringstream ss(custLine);
                string idStr, nameStr, phoneStr, typeStr;
                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, phoneStr, ',');
                getline(ss, typeStr);

                if (stoi(idStr) == bill.Customer_ID)
                {
                    typeStr.erase(0, typeStr.find_first_not_of(" "));
                    typeStr.erase(typeStr.find_last_not_of(" ") + 1);
                    customerType = typeStr;
                    break;
                }
            }
            custFile.close();

            // Step 4: Calculate discount & grand total
            bill.Discount = (customerType == "regular" || customerType == "Regular") ? bill.Sub_Total * 0.05 : 0;
            bill.Grand_Total = bill.Sub_Total - bill.Discount;
            bill.Tax = 0;
            bill.DateTime = dateTime;

            // Increment Bill ID
            bill.Bill_ID++;

            // Step 5: Save bill to billing.csv
            file.open("Billing/billing.csv", ios::out | ios::app);
            if (!file.is_open())
            {
                cout << "Error opening billing.csv\n";
                return 0;
            }
            file << bill.Bill_ID << "," << bill.Transaction_ID << "," << bill.Customer_ID << ","
                 << bill.Sub_Total << "," << bill.Tax << "," << bill.Discount << "," << bill.Grand_Total
                 << "," << bill.DateTime << "\n";
            file.close();

            // Step 6: Update counter.txt
            file.open("Billing/counter.txt", ios::out);
            file << bill.Bill_ID;
            file.close();

            // Step 7: Display Bill
            cout << "\n=========== BILL RECEIPT ===========\n";
            cout << "Bill ID        : " << bill.Bill_ID << "\n";
            cout << "Transaction ID : " << bill.Transaction_ID << "\n";
            cout << "Customer ID    : " << bill.Customer_ID << "\n";
            cout << "Customer Type  : " << customerType << "\n";
            cout << "-----------------------------------\n";
            cout << "ProductID\tQty\tAmount\n";
            for (size_t i = 0; i < products.size(); i++)
                cout << products[i].first << "\t\t" << products[i].second << "\t" << amounts[i] << "\n";
            cout << "-----------------------------------\n";
            cout << "Sub Total      : " << bill.Sub_Total << "\n";
            cout << "Discount       : " << bill.Discount << "\n";
            cout << "Grand Total    : " << bill.Grand_Total << "\n";
            cout << "Date & Time    : " << bill.DateTime << "\n";
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

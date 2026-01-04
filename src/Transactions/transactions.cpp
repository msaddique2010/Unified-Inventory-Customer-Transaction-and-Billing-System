#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>    // To include current date and time

#include "../Products/products.h"
#include "../Customers/customers.h"

using namespace std;

// Sturcture for storing transaction details
struct Sales
{
    int Transaction_ID;
    int Customer_ID;
    int Product_ID;
    int Quantity;
    int totalAmount;
    string dateTime;
};

int transactions()
{
    Products product;
    Customers customer;
    Sales sale;
    fstream file, temp;

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char dateTime[20];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", ltm);

    while (true)
    {
        int choice;
        cout << "\n\n--------==== Manage Transactions ====--------\n"
             << "See All Products.........Press 1: \n"
             << "See All Customers........Press 2: \n"
             << "Make Transaction.........Press 3: \n"
             << "View all Transaction.....Press 4: \n"
             << "Exit to main menu........Press 0: ";
        cin >> choice;

        if (choice == 0)
        {
            cout << "Exiting..";
            break;
        }
        else if (choice == 1)
        {
            allProducts(product, file);
        }
        else if (choice == 2)
        {
            allCustomers(customer, file);
        }
        else if (choice == 3)
        {
            string line;
            // Read last user Transaction_ID from counter.txt
            file.open("Transactions/counter.txt", ios::in);
            if (!file.is_open())
            {
                cout << "Error opening counter.txt\n";
                return 0;
            }
            getline(file, line);
            sale.Transaction_ID = stoi(line); // Convert ID from string to int
            file.close();

            sale.Transaction_ID++; // increments Transaction_ID so that id must be unique

            cout << "\n--------==== Create Transaction ====--------" << endl;
            cin.ignore();
            cout << "Enter Customer ID: ";
            cin >> sale.Customer_ID;

            // Validate customer
            file.open("Customers/customers.csv", ios::in);
            if (!file.is_open())
            {
                cout << "Error opening customers.csv\n";
                return 0;
            }
            bool customerExist = false;
            getline(file, line); // skip header
            while (getline(file, line))     // Run until reaches the end of file
            {
                stringstream ss(line);
                string idStr, nameStr, phoneStr, typeStr;

                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, phoneStr, ',');
                getline(ss, typeStr, ',');

                idStr.erase(0, idStr.find_first_not_of(" "));
                idStr.erase(idStr.find_last_not_of(" ") + 1);
                customer.ID = stoi(idStr);

                if (customer.ID == sale.Customer_ID)
                {
                    customerExist = true;
                    break;
                }
            }
            file.close();
            if (!customerExist)
            {
                cout << "No customer with ID: " << sale.Customer_ID << ".\n";
                continue;
            }

            // Loop to add multiple producst
            char more = 'y';
            while (more == 'y' || more == 'Y')
            {
                cout << "Enter Product ID: ";
                cin >> sale.Product_ID;

                // Validates if product exists or not
                file.open("Products/Products.csv", ios::in);
                if (!file.is_open())
                {
                    cout << "Error opening products.csv\n";
                    return 0;
                }
                bool productExist = false;
                getline(file, line); // skip header
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string idStr, nameStr, descStr, priceStr, qtyStr;

                    getline(ss, idStr, ',');
                    getline(ss, nameStr, ',');
                    getline(ss, descStr, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, qtyStr, ',');

                    if (stoi(idStr) == sale.Product_ID)
                    {
                        product.ID = stoi(idStr);
                        product.quantity = stoi(qtyStr);
                        product.price = stoi(priceStr);
                        productExist = true;
                        break;
                    }
                }
                file.close();
                if (!productExist)
                {
                    cout << "Product not found.\n";
                    continue;
                }

                cout << "Enter Quantity: ";
                cin >> sale.Quantity;

                if (sale.Quantity > product.quantity)
                {
                    cout << "Not enough stock for this product.\n";
                    continue;
                }

                // Update stock
                file.open("Products/Products.csv", ios::in);
                temp.open("Products/temp.csv", ios::out);
                getline(file, line);
                temp << line << endl;
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string idStr, name, desc, priceStr, qtyStr;
                    getline(ss, idStr, ',');
                    getline(ss, name, ',');
                    getline(ss, desc, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, qtyStr, ',');

                    int id = stoi(idStr);
                    int qty = stoi(qtyStr);
                    if (id == sale.Product_ID)
                        qty -= sale.Quantity;

                    temp << id << "," << name << "," << desc << "," << priceStr << "," << qty << "\n";
                }
                file.close();
                temp.close();
                remove("Products/Products.csv");
                rename("Products/temp.csv", "Products/Products.csv");

                sale.totalAmount = sale.Quantity * product.price;

                // Append to transactions.csv
                file.open("Transactions/transactions.csv", ios::out | ios::app);
                file << sale.Transaction_ID << "," << sale.Customer_ID << "," << sale.Product_ID << "," << sale.Quantity << "," << sale.totalAmount << "," << dateTime << "\n";
                file.close();

                cout << "Product added. Add another product? (y/n): ";
                cin >> more;
            }

            // Update counter
            file.open("Transactions/counter.txt", ios::out);
            file << sale.Transaction_ID;
            file.close();

            cout << "\nTransaction completed. Transaction ID: " << sale.Transaction_ID << endl;
        }
        else if (choice == 4)
        {
            string line;
            cout << "\n--------==== Transaction Records ====--------\n";
            file.open("Transactions/transactions.csv", ios::in);
            if (!file.is_open())
            {
                cout << "Error opening transactions.csv\n";
                continue;
            }
            getline(file, line); // skip header
            while (getline(file, line))
            {
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Invalid Input\n";
        }
    }
    return 0;
}

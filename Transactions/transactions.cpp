#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "../Products/products.h"
#include "../Customers/customers.h"

using namespace std;
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
    fstream file;

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char dateTime[20];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", ltm);

    while (true)
    {
        int choice;
        cout << "See All Products.........Press 1: \n"
             << "See All Customers........Press 2: \n"
             << "Make Transaction.........Press 3: \n"
             << "Exit.....................Press 0: ";
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
            // Opens counter.txt to read the last used ID
            file.open("Transactions/counter.txt", ios::in);
            if (!file.is_open())
            {
                cout << "Error in opening counter.txt\n";
                return 0;
            }
            string count;
            getline(file, count);              // Read the UID as string
            sale.Transaction_ID = stoi(count); // Convert UID string to int
            file.close();                      // Close file

            cout << "--------==== Create Transaction ====--------" << endl;
            cin.ignore();
            cout << "Enter Customer ID: "; // Gets username as input
            cin >> sale.Customer_ID;

            cout << "Enter Product ID: "; // Gets Password as input
            cin >> sale.Product_ID;

            cout << "Enter Quantity: "; // Gets Password as input
            cin >> sale.Quantity;

            file.open("Customers/customers.csv", ios::in);
            if (!file.is_open())
            {
                cout << "Error in opening customers.csv\n";
                return 0;
            }

            string line;
            bool exist = false;

            getline(file, line); // Skip header
            while (getline(file, line))
            {
                stringstream ss(line);
                string idStr, nameStr, phoneStr, typeStr;

                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, phoneStr, ',');
                getline(ss, typeStr, ',');

                // Remove spaces
                idStr.erase(0, idStr.find_first_not_of(" "));
                idStr.erase(idStr.find_last_not_of(" ") + 1);
                customer.ID = stoi(idStr);

                nameStr.erase(0, nameStr.find_first_not_of(" "));
                nameStr.erase(nameStr.find_last_not_of(" ") + 1);
                customer.name = nameStr;

                phoneStr.erase(0, phoneStr.find_first_not_of(" "));
                phoneStr.erase(phoneStr.find_last_not_of(" ") + 1);
                customer.phone = phoneStr;

                typeStr.erase(0, typeStr.find_first_not_of(" "));
                typeStr.erase(typeStr.find_last_not_of(" ") + 1);
                customer.type = typeStr;

                if (customer.ID == sale.Customer_ID)
                {
                    exist = true;
                    break;
                }
            }
            file.close();
            if (exist)
            {
                cout << "Customer Exist..." << endl;
                file.open("Products/Products.csv", ios::in);
                if (!file.is_open())
                {
                    cout << "Error in opening products.csv\n";
                    return 0;
                }

                string line;
                bool exist = false;

                getline(file, line); // Skip header
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string idStr, nameStr, descriptionStr, priceStr, quantityStr;

                    getline(ss, idStr, ',');
                    getline(ss, nameStr, ',');
                    getline(ss, descriptionStr, ',');
                    getline(ss, priceStr, ',');
                    getline(ss, quantityStr, ',');

                    // Remove spaces
                    idStr.erase(0, idStr.find_first_not_of(" "));
                    idStr.erase(idStr.find_last_not_of(" ") + 1);
                    product.ID = stoi(idStr);

                    // nameStr.erase(0, nameStr.find_first_not_of(" "));
                    // nameStr.erase(nameStr.find_last_not_of(" ") + 1);
                    // product.name = nameStr;

                    // descriptionStr.erase(0, descriptionStr.find_first_not_of(" "));
                    // descriptionStr.erase(descriptionStr.find_last_not_of(" ") + 1);
                    // product.description = descriptionStr;

                    // priceStr.erase(0, priceStr.find_first_not_of(" "));
                    // priceStr.erase(priceStr.find_last_not_of(" ") + 1);
                    // product.price = stoi(priceStr);

                    // quantityStr.erase(0, quantityStr.find_first_not_of(" "));
                    // quantityStr.erase(quantityStr.find_last_not_of(" ") + 1);
                    // product.quantity = stoi(quantityStr);

                    if (sale.Product_ID == product.ID)
                    {
                        exist = true;
                        break;
                    }
                }
                file.close();
                if (exist)
                {
                    cout << "Product Available..." << endl;
                    file.open("Products/Products.csv", ios::in);
                    if (!file.is_open())
                    {
                        cout << "Error in opening products.csv\n";
                        return 0;
                    }

                    string line;
                    bool exist = false;

                    getline(file, line); // Skip header
                    while (getline(file, line))
                    {
                        stringstream ss(line);
                        string idStr, nameStr, descriptionStr, priceStr, quantityStr;

                        getline(ss, idStr, ',');
                        getline(ss, nameStr, ',');
                        getline(ss, descriptionStr, ',');
                        getline(ss, priceStr, ',');
                        getline(ss, quantityStr, ',');

                        // Remove spaces
                        idStr.erase(0, idStr.find_first_not_of(" "));
                        idStr.erase(idStr.find_last_not_of(" ") + 1);
                        product.ID = stoi(idStr);

                        // nameStr.erase(0, nameStr.find_first_not_of(" "));
                        // nameStr.erase(nameStr.find_last_not_of(" ") + 1);
                        // product.name = nameStr;

                        // descriptionStr.erase(0, descriptionStr.find_first_not_of(" "));
                        // descriptionStr.erase(descriptionStr.find_last_not_of(" ") + 1);
                        // product.description = descriptionStr;

                        // priceStr.erase(0, priceStr.find_first_not_of(" "));
                        // priceStr.erase(priceStr.find_last_not_of(" ") + 1);
                        // product.price = stoi(priceStr);

                        quantityStr.erase(0, quantityStr.find_first_not_of(" "));
                        quantityStr.erase(quantityStr.find_last_not_of(" ") + 1);
                        product.quantity = stoi(quantityStr);

                        if (sale.Product_ID == product.ID && sale.Quantity == product.quantity)
                        {
                            exist = true;
                            break;
                        }
                    }
                    file.close();
                    if (exist)
                    {
                        cout << "Product Quatity is also available.." << endl;
                        cout << "Completed...";
                    }
                    else
                    {
                        cout << "There is not enough quantity of Product with ID: " << sale.Product_ID << endl;
                        return 0;
                    }
                    file.close();
                }
                else
                {
                    cout << "There is no product with ID: " << sale.Product_ID << endl;
                    return 0;
                }
                file.close();
            }
            else
            {
                cout << "There is no customer with ID: " << customer.ID;
            }
            // Step 3: Append new user
            sale.Transaction_ID++; // Increment UID
            file.open("Transactions/transactions.csv", ios::out | ios::app);
            if (!file.is_open())
            {
                cout << "Error in opening products.csv for writing\n";
                return 0;
            }
            file << sale.Transaction_ID << ", " << sale.Customer_ID << ", " << sale.Product_ID << ", " << sale.Quantity << "\n";
            file.close();

            // Step 4: Update counter.txt
            file.open("Transactions/counter.txt", ios::out);
            if (!file.is_open())
            {
                cout << "Error opening counter.txt for writing\n";
                return 0;
            }
            file << sale.Transaction_ID;
            file.close();
            return 0;
        }
        else
        {
            cout << "Invalid Input";
        }
    }

    return 0;
}
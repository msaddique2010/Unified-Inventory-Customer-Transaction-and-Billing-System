#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "products.h"

using namespace std;


int addProducts(Products &product, fstream &file){
    // Opens counter.txt to read the last used UID
    file.open("Products/counter.txt", ios::in);
        if (!file.is_open()) {
            cout << "\n-----------------------------\n"
                 << "Error in opening counter.txt\n"
                 << "-----------------------------\n";
            return 0;
        }
        string count;
        getline(file, count);     // Read the UID as string
        product.ID = stoi(count); // Convert UID string to int
        file.close();             // Close file

        cout << "\n--------==== Add Product ====--------" << endl;
        cin.ignore();
        cout << "Enter Product name: "; // Gets username as input
        getline(cin, product.name);

        cout << "Enter Product Decription: "; // Gets Password as input
        getline(cin, product.description);

        cout << "Enter Product Price: "; // Gets Password as input
        cin >> product.price;

        cout << "Enter Product Quantity: "; // Gets Password as input
        cin >> product.quantity;

        // Step 3: Append new user
        product.ID++; // Increment UID
        file.open("Products/products.csv", ios::out | ios::app);
        if (!file.is_open()) {
            cout << "\n------------------------------------------\n"
                 << "Error in opening products.csv for writing\n"
                 << "------------------------------------------\n";
            return 0;
        }
        file << product.ID << ", " << product.name << ", " << product.description << ", " << product.price << ", " << product.quantity << "\n";

        cout << "\n-----------------------------\n"
             << "  Product added Successfully!  \n"
             << "-----------------------------\n";
        file.close();

        // Step 4: Update counter.txt
        file.open("Products/counter.txt", ios::out);
        if (!file.is_open()) {
            cout << "\n---------------------------------------\n"
                 << "Error opening counter.txt for writing.\n"
                 << "---------------------------------------\n";
            return 0;
        }
        file << product.ID;
    file.close();
    return 0;
}

int updateProducts(Products &product, fstream &file, fstream &temp)
{
    int searchID;
    cout << "\nEnter ID of the product: ";
    cin >> searchID;

    // ---------- Check if product exists ----------
    file.open("Products/products.csv", ios::in);
    if (!file.is_open())
    {
    cout << "\n-----------------------------\n"
         << "Error in opening products.csv\n"
         << "-----------------------------\n";
        return 0;
    }

    string line;
    bool exists = false;

    getline(file, line); // skip header
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr, nameStr;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');

        if (stoi(idStr) == searchID)
        {
            exists = true;
            product.name = nameStr;
            break;
        }
    }
    file.close();

    if (!exists)
    {
        cout << "\n-----------------------------\n"
             << "There is no product with given ID.\n"
             << "-----------------------------\n";
        return 0;
    }

    cout << "---------------------------\n";
    cout << "You Selected: " << product.name << endl;
    cout << "---------------------------\n";

    int whatUpdate;

    do
    {
        cout << "\n--------==== Update Menu ====--------\n"
             << "To Update Name.............Press 1\n"
             << "To Update Description.....Press 2\n"
             << "To Update Price...........Press 3\n"
             << "To Update Quantity........Press 4\n"
             << "Update Whole Product......Press 5\n"
             << "Exit to Product menu......Press 0\n"
             << "Choice: ";
        cin >> whatUpdate;

        if (whatUpdate == 0)
            break;

        file.open("Products/products.csv", ios::in);
        temp.open("Products/temp.csv", ios::out);

        if (!file.is_open() || !temp.is_open())
        {
            cout << "\n-----------------------------\n"
                 << "Error opening file\n"
                 << "-----------------------------\n";
            return 0;
        }

        bool found = false;
        getline(file, line);        // header
        temp << line << endl;       // write header

        while (getline(file, line))
        {
            stringstream ss(line);
            string idStr, nameStr, descStr, priceStr, qtyStr;

            getline(ss, idStr, ',');
            getline(ss, nameStr, ',');
            getline(ss, descStr, ',');
            getline(ss, priceStr, ',');
            getline(ss, qtyStr, ',');

            int id = stoi(idStr);

            if (id == searchID)
            {
                found = true;

                product.name = nameStr;
                product.description = descStr;
                product.price = stoi(priceStr);
                product.quantity = stoi(qtyStr);

                cin.ignore();

                if (whatUpdate == 1)
                {
                    cout << "Enter Product Name: ";
                    getline(cin, product.name);
                }
                else if (whatUpdate == 2)
                {
                    cout << "Enter Product Description: ";
                    getline(cin, product.description);
                }
                else if (whatUpdate == 3)
                {
                    cout << "Enter Product Price: ";
                    cin >> product.price;
                }
                else if (whatUpdate == 4)
                {
                    cout << "Enter Product Quantity: ";
                    cin >> product.quantity;
                }
                else if (whatUpdate == 5)
                {
                    cout << "Enter Product Name: ";
                    getline(cin, product.name);

                    cout << "Enter Product Description: ";
                    getline(cin, product.description);

                    cout << "Enter Product Price: ";
                    cin >> product.price;

                    cout << "Enter Product Quantity: ";
                    cin >> product.quantity;
                }

                temp << id << ", "
                     << product.name << ", "
                     << product.description << ", "
                     << product.price << ", "
                     << product.quantity << endl;
            }
            else
            {
                temp << line << endl;
            }
        }

        file.close();
        temp.close();

        if (found)
        {
            remove("Products/products.csv");
            rename("Products/temp.csv", "Products/products.csv");
            cout << "\n-----------------------------\n"
                 << "Product updated successfully.\n"
                 << "-----------------------------\n";
        }
        else
        {
            remove("Products/temp.csv");
            cout << "\n-----------------------------\n"
                 << "Product ID not found.\n"
                 << "-----------------------------\n";
        }

    } while (whatUpdate != 0);

    cout << "You're exited...\n";
    return 0;
}

int deleteProducts(Products &product, fstream &file, fstream &temp){
    int searchID;
    cout << "Enter ID of the product: ";
    cin >> searchID;

    file.open("Products/products.csv", ios::in);
    temp.open("Products/temp.csv", ios::out);

    if (!file.is_open() || !temp.is_open()) {
        cout << "\n-------------------\n"
             << "Error opening file\n"
             << "-------------------\n";
        return 0;
    }

    string line;
    bool found = false;

    // Copy header
    getline(file, line);
    temp << line << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nameStr, descStr, priceStr, qtyStr;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, descStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, qtyStr, ',');

        int id = stoi(idStr);

        if (id == searchID){
            found = true;
        }
        else {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("Products/products.csv");
        rename("Products/temp.csv", "Products/products.csv");
        cout << "\n-----------------------------\n"
             << "Product deleted Successfully!  \n"
             << "-----------------------------\n";
    }
    else
    {
        remove("Products/temp.csv");
        cout << "\n-----------------------------\n"
             << "Product ID not found.\n"
             << "-----------------------------\n";
    }
    return 0;
}

int searchProducts(Products &product, fstream &file){
    cout << "Enter ID of the product: ";
    cin >> product.ID;

    file.open("Products/products.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\n------------------------------\n"
                 << "Error in opening products.csv\n"
                 << "------------------------------\n";
        return 0;
    }

    string line;
    bool exist = false;

    getline(file, line); // Skip header
    while (getline(file, line)) {
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
        int ID = stoi(idStr);

        nameStr.erase(0, nameStr.find_first_not_of(" "));
        nameStr.erase(nameStr.find_last_not_of(" ") + 1);
        product.name = nameStr;

        descriptionStr.erase(0, descriptionStr.find_first_not_of(" "));
        descriptionStr.erase(descriptionStr.find_last_not_of(" ") + 1);
        product.description = descriptionStr;

        priceStr.erase(0, priceStr.find_first_not_of(" "));
        priceStr.erase(priceStr.find_last_not_of(" ") + 1);
        product.price = stoi(priceStr);

        quantityStr.erase(0, quantityStr.find_first_not_of(" "));
        quantityStr.erase(quantityStr.find_last_not_of(" ") + 1);
        product.quantity = stoi(quantityStr);

        if (ID == product.ID)
        {
            exist = true;
            break;
        }
    }
    file.close();
    if (exist) {
        cout << "--------==== Product Details ====--------" << endl;
        cout << "ID: " << product.ID << endl;
        cout << "Name: " << product.name << endl;
        cout << "Description: " << product.description << endl;
        cout << "Quantity: " << product.quantity << endl;
    }
    else
    {
        cout << "There is no product with ID: " << product.ID;
    }
    return 0;
}

int allProducts(Products &product, fstream &file){
    cout << endl;
    cout << "\n--------==== Product Details ====--------" << endl;

    file.open("Products/products.csv", ios::in);
    if (!file.is_open())
    {
        cout << "\n-----------------------------\n"
             << "Error in opening products.csv\n"
             << "-----------------------------\n\n";
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

        nameStr.erase(0, nameStr.find_first_not_of(" "));
        nameStr.erase(nameStr.find_last_not_of(" ") + 1);
        product.name = nameStr;

        descriptionStr.erase(0, descriptionStr.find_first_not_of(" "));
        descriptionStr.erase(descriptionStr.find_last_not_of(" ") + 1);
        product.description = descriptionStr;

        priceStr.erase(0, priceStr.find_first_not_of(" "));
        priceStr.erase(priceStr.find_last_not_of(" ") + 1);
        product.price = stoi(priceStr);

        quantityStr.erase(0, quantityStr.find_first_not_of(" "));
        quantityStr.erase(quantityStr.find_last_not_of(" ") + 1);
        product.quantity = stoi(quantityStr);

        cout << endl;
        cout << "ID: " << product.ID << endl;
        cout << "Name: " << product.name << endl;
        cout << "Description: " << product.description << endl;
        cout << "Price: " << product.price << endl;
        cout << "Quantity: " << product.quantity << endl;
        cout << "----------------------------------" << endl;

        exist = true;
    }
    if (!exist) {
        cout << "\n-----------------------------\n"
             << "No products available in Products.csv\n"
             << "-----------------------------\n";
    }
    file.close();
    return 0;
}

int products(){
    Products product;
    fstream file;
    fstream temp;

    int choice;
    do {
        cout << "\n--------==== Products Menu ====--------"
             << "\nTo Add Product ........PRESS 1,"
             << "\nTo View Inventory......PRESS 2,"
             << "\nTo Delete Product .....PRESS 3,"
             << "\nTo Search Product .....PRESS 4,"
             << "\nTo Update Product .....PRESS 5,"
             << "\nExit to main menu......PRESS 0: ";
        cin >> choice;

        if (choice == 0) {
            cout << "\n-------------------------------\n"
                 << "You'r Exited from Product Menu.\n"
                 << "-------------------------------\n";
            break;
        }
        else if (choice == 1) {
            addProducts(product, file);
        }
        else if (choice == 2) {
            allProducts(product, file);
        }
        else if (choice == 3){
            deleteProducts(product, file, temp);
        }
        else if (choice == 4){
            searchProducts(product, file);
        }
        else if (choice == 5) {
            updateProducts(product, file, temp);
        }
        else
        {
            cout << "";
            cout << "\n--------------\n"
                 << "Invalid Input\n"
                 << "--------------\n";
        }
    } while (choice != 0);
    return 0;
}
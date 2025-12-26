#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "customers.h"

using namespace std;

int addCustomers(Customers &customer, fstream &file){
    // Opens counter.txt to read the last used UID
    file.open("Customers/counter.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error in opening counter.txt\n";
        return 0;
    }
    string count;
    getline(file, count);     // Read the UID as string
    customer.ID = stoi(count); // Convert UID string to int
    file.close();             // Close file

    cout << "--------==== Add Customer ====--------" << endl;
    cin.ignore();
    cout << "Enter Customer name: "; // Gets username as input
    getline(cin, customer.name);

    cout << "Enter Customer's Phone Number: "; // Gets Password as input
    getline(cin, customer.phone);

    cout << "Enter Customer Type(general(g), regular(r)): "; // Gets Password as input
    getline(cin, customer.type);

    if (customer.type == "g" || customer.type == "G" || customer.type == "general") {
        customer.type = "General";
    }
    else{
        customer.type = "Regular";
    }

    // Step 3: Append new user
    customer.ID++; // Increment UID
    file.open("Customers/customers.csv", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error in opening customers.csv for writing\n";
        return 0;
    }
    file << customer.ID << ", " << customer.name << ", " << customer.phone << ", " << customer.type << "\n";
    file.close();

    // Step 4: Update counter.txt
    file.open("Customers/counter.txt", ios::out);
    if (!file.is_open()) {
        cout << "Error opening counter.txt for writing\n";
        return 0;
    }
    file << customer.ID;
    file.close();
    return 0;
}

int updateCustomers(Customers &customer, fstream &file, fstream &temp){
    int searchID;
    cout << "Enter ID of the customer: ";
    cin >> searchID;

    file.open("Customers/customers.csv", ios::in);
    temp.open("Customers/temp.csv", ios::out);

    if (!file.is_open() || !temp.is_open()) {
        cout << "Error opening file\n";
        return 0;
    }

    string line;
    bool found = false;

    // Copy header
    getline(file, line);
    temp << line << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nameStr, phoneStr, typeStr;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, phoneStr, ',');
        getline(ss, typeStr, ',');

        int id = stoi(idStr);

        if (id == searchID){
            found = true;

            cin.ignore();
            cout << "Enter Customer Name: ";
            getline(cin, customer.name);

            cout << "Enter Customer Phone Number: ";
            getline(cin, customer.phone);

            cout << "Enter Customer Type: ";
            getline(cin, customer.type);

            if (customer.type == "g" || customer.type == "G" || customer.type == "general") {
                customer.type = "General";
            }
            else{
                customer.type = "Regular";
            }
            // Write updated row
            temp << searchID << ", "
                    << customer.name << ", "
                    << customer.phone << ", "
                    << customer.type << endl;
        }
        else {
            // Copy original row
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (found){
        remove("Customers/customers.csv");
        rename("Customers/temp.csv", "customers.csv");
        cout << "Customers updated successfully.\n";
    }
    else{
        remove("Customers/temp.csv");
        cout << "Customers ID not found.\n";
    }
    return 0;
}

int deleteCustomers(Customers &customer, fstream &file, fstream &temp){
    int searchID;
    cout << "Enter ID of the Customer: ";
    cin >> searchID;

    file.open("Customers/customers.csv", ios::in);
    temp.open("Customers/temp.csv", ios::out);

    if (!file.is_open() || !temp.is_open()) {
        cout << "Error opening file\n";
        return 0;
    }

    string line;
    bool found = false;

    // Copy header
    getline(file, line);
    temp << line << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nameStr, phoneStr, typeStr;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, phoneStr, ',');
        getline(ss, typeStr, ',');

        int id = stoi(idStr);

        if (id == searchID){
            found = true;
        }
        else {
            // Copy original row
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    if (found) {
        remove("Customers/customers.csv");
        rename("Customers/temp.csv", "customers.csv");
        cout << "Customers Deleted successfully.\n";
    }
    else
    {
        remove("Customers/temp.csv");
        cout << "Customers ID not found.\n";
    }
    return 0;
}

int searchCustomers(Customers &customer, fstream &file){
    cout << "Enter ID of the customer: ";
    cin >> customer.ID;

    file.open("Customers/customers.csv", ios::in);
        if (!file.is_open())
        {
            cout << "Error in opening customers.csv\n";
            return 0;
        }

        string line;
        bool exist = false;

        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            string idStr, nameStr, phoneStr, typeStr;

            getline(ss, idStr, ',');
            getline(ss, nameStr, ',');
            getline(ss, phoneStr, ',');
            getline(ss, typeStr, ',');

            // Remove spaces
            idStr.erase(0, idStr.find_first_not_of(" "));
            idStr.erase(idStr.find_last_not_of(" ") + 1);
            int ID = stoi(idStr);

            nameStr.erase(0, nameStr.find_first_not_of(" "));
            nameStr.erase(nameStr.find_last_not_of(" ") + 1);
            customer.name = nameStr;

            phoneStr.erase(0, phoneStr.find_first_not_of(" "));
            phoneStr.erase(phoneStr.find_last_not_of(" ") + 1);
            customer.phone = phoneStr;

            typeStr.erase(0, typeStr.find_first_not_of(" "));
            typeStr.erase(typeStr.find_last_not_of(" ") + 1);
            customer.type = typeStr;

            if (ID == customer.ID){
                exist = true;
                break;
            }
        }
    file.close();
    if (exist) {
        cout << "--------==== Customer Details ====--------" << endl;
        cout << "ID: " << customer.ID << endl;
        cout << "Name: " << customer.name << endl;
        cout << "Phone: " << customer.phone << endl;
        cout << "Type: " << customer.type << endl;
    }
    else {
        cout << "There is no customer with ID: " << customer.ID;
    }
    return 0;
}

int allCustomers(Customers &customer, fstream &file){
    cout << endl;
    cout << "--------==== Customer Details ====--------" << endl;

    file.open("Customers/customers.csv", ios::in);
        if (!file.is_open())
        {
            cout << "Error in opening customers.csv\n";
            return 0;
        }

        string line;
        bool exist = false;

        getline(file, line); // Skip header
        while (getline(file, line)){
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

            cout << endl;
            cout << "ID: " << customer.ID << endl;
            cout << "Name: " << customer.name << endl;
            cout << "Phone Number: " << customer.phone << endl;
            cout << "Type: " << customer.type << endl;
            cout << "----------------------------------" << endl;
        }
    file.close();
    return 0;
}
int customers(){
    Customers customer;
    fstream file;
    fstream temp;

    int choice;
    do {
        cout << "\n--------==== Customers Menu ====--------"
             << "\nTo Add Customer ..........PRESS 1,"
             << "\nTo Update Customer .......PRESS 2,"
             << "\nTo Delete Customer .......PRESS 3,"
             << "\nTo Search Customer .......PRESS 4,"
             << "\nTo View all Customer......PRESS 5,"
             << "\nTo Exit ..................PRESS 0: ";
        cin >> choice;

        if (choice == 0) {
            cout << "You'r Logged out.\n";
            break;
        }
        else if (choice == 1) {
            addCustomers(customer, file);
        }
        else if (choice == 2) {
            updateCustomers(customer, file, temp);
        }
        else if (choice == 3){
            deleteCustomers(customer, file, temp);
        }
        else if (choice == 4){
            searchCustomers(customer, file);
        }
        else if (choice == 5) {
            allCustomers(customer, file);
        }
        else {
            cout << "Invalid Input";
        }
    } while (choice != 0);
    return 0;
}
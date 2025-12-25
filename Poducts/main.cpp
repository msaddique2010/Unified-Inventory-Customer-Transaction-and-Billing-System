#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
struct Products
{
    int ID;
    string name;
    string description;
    int price;
    int quantity;
};

int main()
{
    Products product;
    fstream file;

    int choice;
    do {
        cout << "\nTo Add Product ........PRESS 1,"
             << "\nTo Update Product .....PRESS 2,"
             << "\nTo Delete Product .....PRESS 3,"
             << "\nTo Search Product .....PRESS 4,"
             << "\nTo View Inventory......PRESS 5,"
             << "\nTo Exit ...............PRESS 0: ";
        cin >> choice;

        if (choice == 0) {
            cout << "You'r Logged out.";
            break;
        }
        else if (choice == 1) {
            // Opens counter.txt to read the last used UID
            file.open("counter.txt", ios::in);
            if (!file.is_open()) {
                cout << "Error in opening counter.txt\n";
                return 0;
            }
            string count;
            getline(file, count);     // Read the UID as string
            product.ID = stoi(count); // Convert UID string to int
            file.close();             // Close file

            cout << "--------==== Add Product ====--------" << endl;
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
            file.open("products.csv", ios::out | ios::app);
            if (!file.is_open()) {
                cout << "Error in opening products.csv for writing\n";
                return 0;
            }
            file << product.ID << ", " << product.name << ", " << product.description << ", " << product.price << ", " << product.quantity << "\n";
            file.close();

            // Step 4: Update counter.txt
            file.open("counter.txt", ios::out);
            if (!file.is_open()) {
                cout << "Error opening counter.txt for writing\n";
                return 0;
            }
            file << product.ID;
            file.close();
        }
        else if (choice == 2) {
            int searchID;
            cout << "Enter ID of the product: ";
            cin >> searchID;

            fstream file("products.csv", ios::in);
            fstream temp("temp.csv", ios::out);

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
                string idStr, nameStr, descStr, priceStr, qtyStr;

                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, descStr, ',');
                getline(ss, priceStr, ',');
                getline(ss, qtyStr, ',');

                int id = stoi(idStr);

                if (id == searchID){
                    found = true;

                    cin.ignore();
                    cout << "Enter Product Name: ";
                    getline(cin, product.name);

                    cout << "Enter Product Description: ";
                    getline(cin, product.description);

                    cout << "Enter Product Price: ";
                    cin >> product.price;

                    cout << "Enter Product Quantity: ";
                    cin >> product.quantity;

                    // Write updated row
                    temp << searchID << ","
                         << product.name << ","
                         << product.description << ","
                         << product.price << ","
                         << product.quantity << endl;
                }
                else {
                    // Copy original row
                    temp << line << endl;
                }
            }

            file.close();
            temp.close();

            if (found)
            {
                remove("products.csv");
                rename("temp.csv", "products.csv");
                cout << "Product updated successfully.\n";
            }
            else
            {
                remove("temp.csv");
                cout << "Product ID not found.\n";
            }
        }
        else if (choice == 3)
        {
            int searchID;
            cout << "Enter ID of the product: ";
            cin >> searchID;

            fstream file("products.csv", ios::in);
            fstream temp("temp.csv", ios::out);

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
                string idStr, nameStr, descStr, priceStr, qtyStr;

                getline(ss, idStr, ',');
                getline(ss, nameStr, ',');
                getline(ss, descStr, ',');
                getline(ss, priceStr, ',');
                getline(ss, qtyStr, ',');

                int id = stoi(idStr);

                if (id == searchID){
                    found = true;

                    // Write updated row
                    temp << "";
                }
                else {
                    // Copy original row
                    temp << line << endl;
                }
            }

            file.close();
            temp.close();

            if (found) {
                remove("products.csv");
                rename("temp.csv", "products.csv");
                cout << "Product Deleted successfully.\n";
            }
            else
            {
                remove("temp.csv");
                cout << "Product ID not found.\n";
            }
        }
        else if (choice == 4)
        {
            cout << "Enter ID of the product: ";
            cin >> product.ID;

            file.open("products.csv", ios::in);
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
            if (exist)
            {
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
            file.close();
        }
        else if (choice == 5)
        {
            cout << endl;
            cout << "--------==== Product Details ====--------" << endl;

            file.open("products.csv", ios::in);
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
                cout << "Quantity: " << product.quantity << endl;
                cout << "----------------------------------" << endl;
            }
            file.close();
        }
        else
        {
            cout << "Invalid Input";
        }
    } while (choice != 0);
    return 0;
}
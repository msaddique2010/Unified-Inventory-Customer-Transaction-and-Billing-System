// Next step is to avoid duplication in Username (username must be unique)

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
bool isAuthentic = false;
// Structure holds user data
struct User{
    int UID;
    string username;
    string password;
};

int authentication(){
    fstream file; // File object for reading/writing files
    User user;    // User-defined datatype to store user input and info

    int choice;
    cout << "Press 1 to Sign up 2 to Login: "; // Take user input: 1 = Sign up, 2 = Login
    cin >> choice;

    // --------==== Sign Up ====--------
    if (choice == 1){

        // Opens counter.txt to read the last used UID
        file.open("./Authentication/counter.txt", ios::in);
        if(!file.is_open()) {
            cout << "Error in opening counter.txt\n";
            return 0;
        }
        string count;
        getline(file, count);   // Read the UID as string
        user.UID = stoi(count); // Convert UID string to int
        file.close();           // Close file

        cout << "\n--------==== Sign Up ====--------" << endl;

        cout << "Enter Username: "; // Gets username as input
        cin >> user.username;

        cout << "Enter password: "; // Gets Password as input
        cin >> user.password;

        // Step 2: Check for duplicate username
        file.open("./Authentication/data.csv", ios::in);
        if (!file.is_open()) {
            cout << "Error in opening data.csv\n";
            return 0;
        }

        string line;
        bool duplicate = false;

        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            string uidStr, usernameStr, passwordStr;

            getline(ss, uidStr, ',');
            getline(ss, usernameStr, ',');
            
            // Remove leading/trailing spaces
            usernameStr.erase(0, usernameStr.find_first_not_of(" "));
            usernameStr.erase(usernameStr.find_last_not_of(" ") + 1);

            if (usernameStr == user.username) {
                duplicate = true;
                break;
            }
        }
        file.close();

        if (duplicate) {
            cout << "Username already exists. Choose another username.\n";
        } else {
            // Step 3: Append new user
            user.UID++; // Increment UID
            file.open("./Authentication/data.csv", ios::out | ios::app);
            if (!file.is_open()) {
                cout << "Error in opening data.csv for writing\n";
                return 0;
            }
            file << user.UID << ", " << user.username << ", " << user.password << "\n";
            file.close();

            // Step 4: Update counter.txt
            file.open("./Authentication/counter.txt", ios::out);
            if (!file.is_open()) {
                cout << "Error opening counter.txt for writing\n";
                return 0;
            }
            file << user.UID;
            file.close();

            cout << "Sign up successful! Your UID is " << user.UID << endl;
            isAuthentic = true;
        }
    }

    // --------==== Sign In ====--------
    else if (choice == 2){
        cout << "\n--------==== Sign In ====--------" << endl;
        cout << "Enter your username: ";
        cin >> user.username;

        cout << "Enter your password: ";
        cin >> user.password;

        // Checking if file contain user name
        file.open("./Authentication/data.csv", ios::in);
        if (!file.is_open()) {
            cout << "Error in opening data.csv\n";
            return 0;
        }

        string line;
        bool exist = false;

        getline(file, line); // Skip header
        while (getline(file, line)) {
            stringstream ss(line);
            string uidStr, usernameStr, passwordStr;

            getline(ss, uidStr, ',');
            getline(ss, usernameStr, ',');
            getline(ss, passwordStr, ',');

            // Remove spaces
            usernameStr.erase(0, usernameStr.find_first_not_of(" "));
            usernameStr.erase(usernameStr.find_last_not_of(" ") + 1);

            passwordStr.erase(0, passwordStr.find_first_not_of(" "));
            passwordStr.erase(passwordStr.find_last_not_of(" ") + 1);

            if (usernameStr == user.username && passwordStr == user.password) {
                user.UID = stoi(uidStr);
                exist = true;
                break;
            }
        }
        file.close();
        if (exist) {
            cout << "User Exist and its UID is: " << user.UID << endl;
            isAuthentic = true;
        } else {
            cout << "Incorrect Username or Password";
        }
    }
    return 0;
}
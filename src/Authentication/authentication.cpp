#include <iostream>
#include <string>
#include <fstream>
#include <sstream> // To separate each column in .csv file

using namespace std;

// Structure holds user data like UID, usernme, password.
struct User{
    int UID;
    string username;
    string password;
};

int signUp(User &user, fstream &file){
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

    // Check for duplicate username if exist
    file.open("./Authentication/data.csv", ios::in);
    if (!file.is_open()) {
        cout << "Error in opening data.csv\n";
        return 0;
    }

    string line;
    bool duplicate = false;

    getline(file, line); // This line is used to skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string uidStr, usernameStr, passwordStr;

        // Separated words if they find ","
        getline(ss, uidStr, ',');
        getline(ss, usernameStr, ',');
        
        // Remove spaces and store it in struct
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
        return 0;
    } else {
        // Add new user at the bottom of csv file without any overrighting

        user.UID++; // Increment UID
        file.open("./Authentication/data.csv", ios::out | ios::app);
        if (!file.is_open()) {
            cout << "Error in opening data.csv for writing\n";
            return 0;
        }
        file << user.UID << ", " << user.username << ", " << user.password << "\n";
        file.close();

        // Update counter.txt according to the last id stored in csv
        file.open("./Authentication/counter.txt", ios::out);
        if (!file.is_open()) {
            cout << "Error opening counter.txt for writing\n";
            return 0;
        }
        file << user.UID;
        file.close();

        cout << "\n--------------------------------------------\n"
             << "Sign up successful! Your UID is " << user.UID << "\n"
             << "--------------------------------------------\n";
        return -1;
    }
}

int signIn(User &user, fstream &file){
    cout << "\n--------==== Sign In ====--------" << endl;
        cout << "Enter your username: ";
        cin >> user.username;

        cout << "Enter your password: ";
        cin >> user.password;

        // Checking if file contain user name entered by user
        file.open("./Authentication/data.csv", ios::in);
        if (!file.is_open()) {
            cout << "\n-----------------------------\n"
                 << "Error in opening data.csv\n"
                 << "-----------------------------\n";
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
            cout << "\n-------------------------------------\n";
            cout << "User Exist and its UID is: " << user.UID << endl;
            cout << "-------------------------------------\n";
            return -1;
        } else {
            cout << " \n--------------------------------\n";
            cout << "| Incorrect Username or Password |\n";
            cout << " --------------------------------\n";

            return 0;
        }
}

bool authentication(){
    fstream file; // File object for reading/writing files
    User user;    // User-defined datatype to store user input and info

    int choice;
    cout << "\n--------==== Login Menu ====--------\n"
         << "Sign up............Press 1\n"
         << "Login..............Press 2: ";
    cin >> choice;

    // --------==== Sign Up ====--------
    if (choice == 1){
        int sign_up = signUp(user, file);

        if (sign_up == -1){
            return true;
        }
    }

    // --------==== Sign In ====--------
    else if (choice == 2){
        int sign_in = signIn(user, file);

        if (sign_in == -1){
            return true;
        }
    }

    else {
        cout << "\n-----------------------------\n"
             << "Invalid Input\n"
             << "-----------------------------\n";
    }

    return false;
}
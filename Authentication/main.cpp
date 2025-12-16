// Next step is to avoid duplication in Username (username must be unique)

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Structure holds user data
struct User{
    int UID;
    string username;
    string password;
};

int main(){
    fstream file; // File object for reading/writing files
    User user;    // User-defined datatype to store user input and info

    int choice;
    cout << "Press 1 to Sign up 2 to Login: "; // Take user input: 1 = Sign up, 2 = Login
    cin >> choice;

    // --------==== Sign Up ====--------
    if (choice == 1){

        // Opens counter.txt to read the last used UID

        file.open("counter.txt", ios::in);
        string count;
        getline(file, count);   // Read the UID as string
        user.UID = stoi(count); // Convert UID string to int
        file.close();           // Close file

        cout << "--------==== Sign Up ====--------" << endl;

        // Opens data.csv to add new user without over-writing previous text
        file.open("data.csv", ios::out | ios::app);

        if (file.is_open()){ 
            // Check if file opened successfully
            cout << "Enter Username: "; // Gets username as input
            cin >> user.username;

            cout << "Enter password: "; // Gets Password as input
            cin >> user.password;

            user.UID++; // Increment UID for new user

            // Writes user information to CSV
            file << user.UID << ", " << user.username << ", " << user.password << "\n";

            file.close();

            // Update counter.txt with new UID
            file.open("counter.txt", ios::out);
            file << user.UID;
            file.close();
        }

        else{
            cout << "Error in opening file for writing.." << endl;
            return 0;
        }
    }

    // --------==== Sign In ====--------
    else if (choice == 2){
        cout << "--------==== Sign In ====--------";
    }
    return 0;
}
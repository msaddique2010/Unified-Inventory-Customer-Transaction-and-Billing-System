// Next step is to avoid duplication in Username (username must be unique)

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct User {
    int UID;
    string username;
    string password;
};

int main(){
    fstream file;
    User user;

    int choice;
    cout << "Press 1 to Sign up 2 to Login: ";
    cin >> choice;

    if (choice == 1){
        file.open("counter.txt", ios::in);
            string count;
            getline(file, count);
            user.UID = stoi(count);
        file.close();

        cout << "--------==== Sign Up ====--------" << endl;
        
        file.open("data.csv", ios::out | ios::app);

        if (file.is_open()) {

            cout << "Enter Username: ";
            cin >> user.username;

            cout << "Enter password: ";
            cin >> user.password;

            user.UID++; 
        
            file << user.UID << ", " << user.username << ", " << user.password << "\n";

        file.close();

        file.open("counter.txt", ios::out);
            file << user.UID;
        file.close();

        } else {
            cout << "Error in opening file for writing.." << endl;
            return 0;
        }
    }

    else if (choice == 2){
        cout << "--------==== Sign In ====--------";

    }
    return 0;
}
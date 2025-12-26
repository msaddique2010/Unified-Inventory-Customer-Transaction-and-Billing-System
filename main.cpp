#include <iostream>
#include "./Authentication/authentication.cpp"
#include "./Products/products.cpp"
#include "./Customers/customers.cpp"
#include "./Sales/sales.cpp"

using namespace std;
int main(){
    // authentication();
    // if (isAuthentic) {
    if (true){
        while(true){
            int choice;
            cout << "\n--------==== Main MENU ====--------\n" 
                 << "Products.......Press 1: \n" 
                 << "Customers......Press 2: \n"
                 << "Manage Sales...Press 3: \n"
                 << "Exit...........Press 0: ";
            cin >> choice;
            if (choice == 0){
                cout << "You're going to exit..";
                break;
            }
            else if (choice == 1) {
                products();
            }
            else if (choice == 2){
                customers();
            }
            else if (choice == 3){
                sales();
            }
            else{
                cout << "Invalid Input..";
            }
        }
    } 
    else {
        
    }
    return 0;
}
#include <iostream>
#include "./Authentication/authentication.cpp"
#include "./Products/products.cpp"
#include "./Customers/customers.cpp"
#include "./Transactions/transactions.cpp"
#include "./Billing/billing.cpp"

using namespace std;
int main(){
    // authentication();
    // if (isAuthentic) {
    if (true){
        while(true){
            int choice;
            cout << "\n--------==== Main MENU ====--------\n" 
                 << "Products..............Press 1: \n" 
                 << "Customers.............Press 2: \n"
                 << "Manage Transactions...Press 3: \n"
                 << "Billing...............Press 4: \n"
                 << "Exit..................Press 0: ";
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
                transactions();
            }
            else if (choice == 4){
                billing();
            }
            else{
                cout << "Invalid Input..";
            }
        }
    } 
    else {
        cout << "Invalid Input";
    }
    return 0;
}
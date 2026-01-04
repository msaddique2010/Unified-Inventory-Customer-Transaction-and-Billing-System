#include <iostream>

#include "./Authentication/authentication.cpp"
#include "./Products/products.cpp"
#include "./Customers/customers.cpp"
#include "./Transactions/transactions.cpp"
#include "./Billing/billing.cpp"

using namespace std;
int main(){
    bool isAuthorized = authentication();
    if (isAuthorized) {
        while(true){
            int choice;
            cout << "\n--------==== Main MENU ====--------\n" 
                 << "Products Module.............Press 1: \n" 
                 << "Customers Module............Press 2: \n"
                 << "Transactions Module.........Press 3: \n"
                 << "Billing Module..............Press 4: \n"
                 << "Terminate the Program.......Press 0: ";
            cin >> choice;
            if (choice == 0){
                cout << "\n-----------------------\n";
                cout << "You're going to exit..\n";
                cout << "-----------------------\n";

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
    return 0;
}
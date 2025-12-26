#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "../Products/products.h"

using namespace std;
struct Sales{
    int Transaction_ID;
    int Customer_ID;
    int Product_ID;
    int Quantity;
    int totalAmount;
    string dateTime;
};

int sales(){
    Products product;
    fstream file;

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    char dateTime[20];
    strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", ltm);

    while(true){
        int choice;
        cout << "See All Products.........Press 1: \n"
             << "See All Customers........Press 2: \n"
             << "Exit.....................Press 0: ";
        cin >> choice;

        if (choice == 0){
            cout << "Exiting..";
            break;
        }
        else if(choice == 1){
            allProducts(product, file);
        }
        else {
            cout << "Invalid Input";
        }
    }

    return 0;
}
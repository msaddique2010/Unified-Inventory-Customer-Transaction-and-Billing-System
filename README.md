# Mini ERP System

A simple ERP system developed in **C++** to manage products, customers, transactions, and billing for a small business.  
The project supports **user authentication**, **dynamic billing**, and **CSV-based persistent storage**. It is designed as a command-line application.

---

## Team Members

| Roll Number      | Name                  |
|-----------------|----------------------|
| 25021519-187    | Muhammad Saddique     |
| 25021519-138    | Farooq Farhaaj        |
| 25021519-136    | Maaz Arif             |
| 25021519-215    | Aliyan Nadeem         |



---

## Technologies Used
- C++ (Standard Library: fstream, string, vector, ctime)
- CSV file handling for data storage
- VS Code / GCC Compiler

---

## Project Features
- **User Authentication:** Sign up and sign in system with CSV-based user data.
- **Customer Management:** Add, view, and manage customer records.
- **Product Management:** Add, view, and manage product records.
- **Transactions:** Record transactions with automatic validation of product stock and customer ID.
- **Billing System:** Generate bills automatically, with support for discounts based on customer type.
- **Persistent Storage:** All data is stored in CSV files for simplicity and easy inspection.
---

1. Clone the repository:
   ```bash
   git clone https://github.com/msaddique2010/Unified-Inventory-Customer-Transaction-and-Billing-System

2. Navigate to the src directory:
   ```bash
   cd Project-Name/src

3. Compile the project using g++::
   ```bash
   g++ main.cpp -o main.exe
   
4. Run the program:
   ```bash
   .\main.exe

---
## Contribution Summary

| Roll Number      | Name                  | Contribution                           |
|-----------------|----------------------|-------------------------------------------|
| 25021519-187    | Muhammad Saddique     | Core logic, Programmed System        |
| 25021519-138    | Farooq Farhaaj        | Attested the System |
| 25021519-136    | Maaz Arif             | Designed Interface      |
| 25021519-215    | Aliyan Nadeem         | Comments, documentation      |

---
## Notes
- All data is stored in CSV files
- Unique IDs are managed using counter.txt files
- Program is terminal-based
  
---
## Limitations
- No graphical user interface (GUI)
- No database integration
- Single-user system
---

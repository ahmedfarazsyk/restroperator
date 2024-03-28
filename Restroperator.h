#include <iostream>
#include <string>
using namespace std;

void showActions();
void showMenu();
string insertOrder();
string deleteOrder();
void viewOrders();
string orderDeliver();
string payBill();
string amountEarned();
void pushHistory(int PTR);
void viewHistory();
void clearHistory();

void saveHistoryToFile(const string& filename);
void loadHistoryFromFile(const string& filename);
#include "Restroperator.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <ctime>

using namespace std;
int N = 18;
string foodItems[] = {"Chicken Caesar Salad", "Margherita Pizza", "Cheeseburger with Fries", "Spaghetti Bolognese", "Vegetable Stir-Fry", 
"Grilled Salmon with Veggies", "Mushroom Risotto", "Chicken Alfredo Pasta", "Beef Tacos", "Shrimp Caesar Salad" ,
"Tiramisu", "Chocolate Lava Cake", "Creamy Brulee", "Fruit Tart", "Cheesecake", "Mojito", "Berry Sangria", "Espresso Martini"};

int prices[] = {15, 18, 15, 18, 15, 20, 18, 18, 12, 20, 13, 15, 11, 14, 12, 13, 12, 15};

int histID[30];
string histCustomer[30];
string histOrder[30];
int histAmount[30];
string histTime[30];
int TOP = -1;


int uID[15]; 
int orderNo = 0;
string customer[15];
string order[15];
int amount[15];
int deletedAmount = 0;
int table[15];
bool delivered[15];
bool ITEMDELIVERED;
bool paid[15];
bool PRICEPAID = false;
int LINK[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1};
int AVAIL = 0, START = -1;





void showActions(){
    cout<<"Enter 1 to Show Menu\nEnter 2 to Insert Order\nEnter 3 to Delete Order\nEnter 4 to View Orders\nEnter 5 to Deliver Order\nEnter 6 to Pay Bill\nEnter 7 to View Total Amount Earned\nEnter 8 to View History\nEnter e to exit: "<<endl;
}

void showMenu(){
    cout<<"   "<<left<<setw(30)<<"Menu: "<<setw(10)<<"Prices: "<<endl;
    for(int i = 0; i < N; i++){
        cout<<setw(3)<<i+1<<left<<setw(30)<<foodItems[i]<<"$ "<<prices[i]<<endl;
    }
}

string insertOrder(){
    if (AVAIL == -1){
        string result = "The Restaurant is already full! ";
        return result;
    }
    time_t unique_id = time(0);

    int itemNo, tableNo;
    string name;
    PRICEPAID = false;
    ITEMDELIVERED = false;
    cout<<endl<<"Enter the name of custormer: "; cin>>name;
    string ITEM; int ITEMPRICE = 0;

    char input;
    while (input != 'N' && input != 'n'){
        
        cout<<endl<<"Enter the orderd item no: "; cin>>itemNo;
        itemNo--;
        ITEM += foodItems[itemNo]+", "; ITEMPRICE += prices[itemNo];
        cout<<"Order another item? (y/n): "; cin>>input;
    }
    


    int NEW = AVAIL;
    AVAIL = LINK[AVAIL];

    uID[NEW] = unique_id; customer[NEW] = name; order[NEW] =  ITEM; amount[NEW] = ITEMPRICE; 

    int count = 0;
    do{
        cout<<endl<<"Enter empty table no. and in range (1-15): "; cin >> tableNo;
        count = 0;

        if (tableNo > 0 && tableNo <= 15){
            for (int i = 0; i < 15; i++){
                if (tableNo == table[i])
                    count++;
            }
        }
            
    }while (tableNo <= 0 || tableNo > 15 || count != 0);

    table[NEW] = tableNo;        
    delivered[NEW] = ITEMDELIVERED; paid[NEW] = PRICEPAID;

    if (START == -1){
        LINK[NEW] = START;
        START = NEW;
    }
    else{
        int PTR = START;
        while (LINK[PTR] != -1)
            PTR = LINK[PTR];
        LINK[NEW] = -1;
        LINK[PTR] = NEW;
    }
    return "Order inserted successfully!";
}

string deleteOrder(){
    if (START == -1){
        string result = "There is no order available to be deleted!";
        return result;
    }
    
    int LOC;
    cout<<"Enter the order no. you want to delete: "; cin>>LOC;
    LOC--;

    

    int PTR = START;
    int prev = -1; // To keep track of the previous node in the linked list

    // Finding the node to delete
    while (PTR != -1 && LOC > 0) {
        prev = PTR;
        PTR = LINK[PTR];
        LOC--;
    }

    if (PTR == -1) {
        return "Order number not found!";
    }
    // Delete the node
    if (prev == -1) {
        START = LINK[PTR];
    } else {
        LINK[prev] = LINK[PTR];
    }

    if (paid[PTR] == true){ 
        deletedAmount += amount[PTR];
    }

    // Resetting the deleted node's link
    LINK[PTR] = AVAIL;
    AVAIL = PTR;

    return "Order deleted successfully!";
}


void viewOrders(){
    int totalOrders = 0, deliveredOrders = 0, paidOrders = 0;
    cout << left << setw(5) << "No." << setw(15) << "Id" << setw(20) << "Name" << setw(30) << "Orders" << setw(12) << "Amount" << setw(10) << "Table" << setw(15) << "Delivered" << setw(10) << "Paid" << endl;
    int PTR = START;
    while (PTR != -1){
        totalOrders++;
        if (paid[PTR])
            paidOrders++;
        if (delivered[PTR])
            deliveredOrders++;
        
        cout << left << setw(5) << totalOrders << setw(15) << uID[PTR] << setw(20) << customer[PTR] << ""; // Clearing the field for orders
        
        // Display each ordered item on a separate line
        string items = order[PTR];
        size_t pos = 0; int format = 0;

        while ((pos = items.find(", ")) != string::npos) {
            cout << left <<setw(30)<< items.substr(0, pos); // Display each item
            format++;
            if (format == 1){
                cout << left << "$ " << setw(10)  << amount[PTR] << setw(10) << table[PTR];
                cout << setw(15) << (delivered[PTR] ? "Yes" : "No") << setw(10) << (paid[PTR] ? "Yes" : "No");
            }
            items.erase(0, pos + 2);
            cout <<endl<< setw(40)<< left << ""; // Empty space for alignment
        }

        cout << left << setw(20) << items <<endl;
        
        PTR = LINK[PTR];
    }
    cout << endl << "Total Orders: " << totalOrders << ", Delivered Orders: " << deliveredOrders << ", Paid Orders: " << paidOrders << endl;
    cout<<amountEarned();
}


string orderDeliver(){
    cout<<"Enter the order no. which have been delivered: "; cin>>orderNo;
    orderNo--;
    int PTR = START;
    while (PTR != -1){
        if (PTR == orderNo){
            delivered[PTR] = true;
        }
        PTR = LINK[PTR];
    }
    return "Order delivered for order no: " + to_string(++orderNo);
}

string payBill(){
    cout<<"Enter the order no. who have paid the bill: "; cin>>orderNo;
    orderNo--;
    int PTR = START;
    while (PTR != -1){
        if (PTR == orderNo){
            if (delivered[PTR] == true){
                paid[PTR] = true;
                pushHistory(PTR);
            }      
            else
                return "Let the order be first delivered!";
        }
        PTR = LINK[PTR];
    }
    return "Bill Paid for order no: " + to_string(++orderNo);
}

string amountEarned(){
    int totalAmount = 0;
    int PTR = START;
    while (PTR != -1){
        if (paid[PTR] == true)
            totalAmount += amount[PTR];
    PTR = LINK[PTR];
    }
    totalAmount += deletedAmount;
    return "Total amount earned: $" + to_string(totalAmount);

}

void pushHistory(int PTR){
    TOP++;
    histID[TOP] = uID[PTR];
    histCustomer[TOP] = customer[PTR];
    histOrder[TOP] = order[PTR];
    histAmount[TOP] = amount[PTR];

    time_t time_sec = time(0);
    tm *gottime = localtime(&time_sec);

    int day, month, year, hour, min, sec;

    day = gottime->tm_mday; month = gottime->tm_mon; year = gottime->tm_year;
    hour = gottime->tm_hour; min = gottime->tm_min; sec = gottime->tm_sec;

    string time = to_string(day) + "/" + to_string(month + 1) + "/" + to_string(year + 1900) + " " + to_string(hour) + ":" + to_string(min) + ":" + to_string(sec) ;
    

    histTime[TOP] = time;
}


void viewHistory(){
    cout << left << setw(5) << "No." << setw(15) << "ID" << setw(20) << "Name" << setw(30) << "Orders" << setw(12) << "Amount" << setw(15) << "Time";

    for (int i = TOP; i >= 0; i--){
        cout << endl << left << setw(5) << i+1 << setw(15) << histID[i] << setw(20) << histCustomer[i];

        string items = histOrder[i];
        size_t pos = 0; int format = 0;

        while ((pos = items.find(", ")) != string::npos) {
            cout << left <<setw(30)<< items.substr(0, pos); // Display each item
            format++;
            if (format == 1){
                cout << left << "$ " <<setw(10) << histAmount[i] << setw(15) << histTime[i];
            }
            items.erase(0, pos + 2);
            cout <<endl<< setw(40)<< left << ""; // Empty space for alignment
        }
        cout << left << setw(20) << items;
    }

    clearHistory();
}

void clearHistory(){
    char clr;
    cout << endl << endl << "Do you want to clear History (y/n): "; cin>>clr;
    if (clr == 'y' || clr == 'Y'){
        TOP = -1;
    }
}

void saveHistoryToFile(const string& filename){
    ofstream ostream(filename);
    if (!ostream.is_open()){
        cout<<"File can't be opened.";
        return;
    }
    ostream << TOP << endl;

    for (int i = 0; i <= TOP; i++){
        int histIdentity = histID[i];
        string histCust = histCustomer[i];
        string histOrd = histOrder[i];
        int histAm = histAmount[i];
        string histTm = histTime[i];
        replace(histCust.begin(), histCust.end(), ' ', '_');
        replace(histOrd.begin(), histOrd.end(), ' ', '_');
        replace(histTm.begin(), histTm.end(), ' ', '_');

        ostream << histIdentity << " " << histCust << " " << histOrd <<" "<< histAm << " " << histTm <<endl;

    }
    ostream.close();
}

void loadHistoryFromFile(const string& filename){
    ifstream istream(filename);
    if (!istream.is_open()){
        cout<<"File can't be opened.";
        return;
    }
    istream >> TOP;
    if (TOP < 0){
        cout<<"History: There is no record available.";
        return;
    }

    for (int i = 0; i <= TOP; i++){
        int histIdentity;
        string histCust;
        string histOrd;
        int histAm = 0;
        string histTm;

        istream >> histIdentity >> histCust >> histOrd >> histAm >> histTm;

        replace(histCust.begin(), histCust.end(), '_', ' ');
        replace(histOrd.begin(), histOrd.end(), '_', ' ');
        replace(histTm.begin(), histTm.end(), '_', ' ');


        histID[i] = histIdentity;
        histCustomer[i] = histCust;
        histOrder[i] = histOrd;
        histAmount[i] = histAm;
        histTime[i] = histTm;

        // Check for any errors during file reading
        if (istream.fail()) {
            cout << "Error: Failed to read history entry " << (i + 1) << " from file " << filename << endl;
            return;
        }
    }
}

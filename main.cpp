#include "Restroperator.h"
#include "Restroperator.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){

    char act;
    cout<<"_____________________________________WELCOME TO RESTROPERATOR______________________________________________"<<endl;
    loadHistoryFromFile("new_history.txt");
    cout<<endl;
    do {
        cout<<"___________________________________________________________________________________________________________"<<endl;
        showActions();
        
        cin>>act;
        if (act == 'e'|| act == 'E' ){
            saveHistoryToFile("new_history.txt");
            break;
        }
        switch (act){
            case '1':
                cout<<"__________________________________________MENU OF FOOD ITEMS_______________________________________________"<<endl;
                showMenu();
                cout<<endl;
                break;
            case '2':
                cout<<"___________________________________________INSERT ANY ORDER_______________________________________________"<<endl;
                showMenu();
                cout<<endl<<endl<<insertOrder()<<endl;
                viewOrders();
                cout<<endl;
                break;
            case '3':
                cout<<"___________________________________________DELETE ANY ORDER_______________________________________________"<<endl;
                cout<<deleteOrder()<<endl;
                viewOrders();
                cout<<endl;
                break;

            case '4':
                cout<<"________________________________________________ORDERS____________________________________________________"<<endl;
                viewOrders();
                cout<<endl;
                break;
            case '5':
                cout<<"_____________________________________________DELIVER ORDER________________________________________________"<<endl;
                cout<<orderDeliver()<<endl;
                viewOrders();
                cout<<endl;
                break;
            case '6':
                cout<<"_______________________________________________PAY BILL___________________________________________________"<<endl;
                cout<<payBill()<<endl;
                viewOrders();
                cout<<endl;
                break;
            case '7':
                cout<<"__________________________________________TOTAL AMOUNT EARNED______________________________________________"<<endl;
                cout<<amountEarned()<<endl;
                break;
            case '8':
                cout<<"________________________________________________HISTORY____________________________________________________"<<endl;
                viewHistory();
                cout<<endl;
                break;
            default:
                cout<<"Enter valid number!";
        }


    }while(true);
}
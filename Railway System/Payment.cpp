//
// Created by majok on 12/16/2024.
//
#include <iostream>
#include <list>
using namespace std;
#ifndef PAYMENT_H
#define PAYMENT_H
class Payment {
    double amount=0.0;
    string method;
    string status;
    string date;
public:
    static int payment_id;
    Payment() {
        payment_id++;
    }
    void paymentMethod() { // function to determine the payment method
        int choice;
        cout << "Choose a payment method from the following: " << endl<<"1)Credit/Debit Card\t"
        <<"2)Digital wallet\n";
        do {
                cin >> choice;
                if(choice < 1 || choice > 2) {
                cout << "Please enter a valid choice" << endl;
                }
        }while(choice < 1 || choice > 2);
        if (choice == 1) {
            method = "Credit/Debit Card";
        } else {
            method = "Digital wallet";
        }
    };
    void processPayment() { //check if the payment method is valid or no
    string number;
        if ( method == "Credit/Debit Card") {
            cout << "Please enter the Credit/Debit Card number: ";
            do {
                cin >> number;
                if((int)number.size() !=16)
                    cout << "\nPlease enter a valid Credit/Debit Card: " << endl;
            } while((int)number.size() !=16);
        }
        else {
            cout << "\nPlease the enter Digital wallet number: ";
            do {
                cin >> number;
                if((int)number.size() !=11)
                    cout << "\nPlease enter a valid digital wallet: " << endl;
            } while((int)number.size() !=11);
        }
        cout<<"\nPlease enter the amount: ";
        cin>>amount;
        int fare; //سيتم استبدالها ب fare في كلاس تيكت
        if(amount==fare) {
            status = "Successful";
        }else
            status = "Unsuccessful";
    };
    void verifyPayment() {
        if(status=="Successful") {
        cout << "\nThe payment is successful.\n";

        }else
         cout << "\nThe payment is unsuccessful.\n";
    };
    void generateReceipt(Payment payment) {
    list<Payment> Recepits;
    Recepits.push_back(payment);
    cout<<"-----------------------Recepit#"<<payment_id<<"-----------------------\n"
        <<"Payment id: "<<payment_id<<"\n"
        <<"Amount: "<<amount<<"\n"
        <<"Method: "<<method<<"\n"
        <<"Status: "<<status<<"\n"
        <<"Date: "<<date<<"\n";
    };
};
int Payment :: payment_id=0;
#endif //PAYMENT_H
int main() {
    return 0;
}
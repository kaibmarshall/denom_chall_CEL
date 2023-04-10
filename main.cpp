#include <iostream>
#include <iomanip> //For setprecision, which is used for output legibility
#include <string.h>
using namespace std;

//US Denominations: 0.01 , 0.05 , 0.10 , 0.25 , 1.00 , 5.00 , 10.00 , 20.00 , 50.00 , 100.00
//To reduce potential errors, calculations will be done in cents so as to use integers whenever possible
//Therefore, the denominations will be represented as: 1 , 5 , 10 ... 2000, 5000, 10000.
const int NUM_OF_US_DENOMS = 10;
const int US_DENOMS[] = {10000,5000,2000,1000,500,100,25,10,5,1};

// ***NOTE**** - The below algorithm for counting the denominations assumes that they are listed in DESCENDING order
int* getNumOfDenoms(int amount) {

    static int demomCounter[NUM_OF_US_DENOMS];
    memset(demomCounter, 0, sizeof(demomCounter)); //sets all values of teh counter array to 0

    for (int i = 0; i<NUM_OF_US_DENOMS; i++){
        while (amount >= US_DENOMS[i]) {
            amount -= US_DENOMS[i];
            demomCounter[i] += 1;
        }
    }

    return demomCounter;
}

void run(){
    //First, get user input to count the denominations
    double amount;
    cout << "Enter the amount to get change for: ";

    //Check user input is a number and get new input if invalid
    while (true){
        if (cin >> amount) { //Check if input is a number
            if (amount < 0) { //Check if input is negative
                cout << "Input is negative. Please enter a positive value." << endl;
                cin.clear();
                while (cin.get() != '\n');
                continue;
            }
            break; //Input is a number and not negative, so it is valid
        }
        else { //Input is not a number
            cout << "Invalid input. Please input a numerical value." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
    }

    //Convert user input to cents for calculation purposes
    int intAmount = amount*100;

    //Count the number of each denomination using algorithm
    int* denomCounter = getNumOfDenoms(intAmount);

    //Output result to user
    cout <<"The entered amount is $" << setprecision(2) << fixed << amount << endl << "Getting the least amount of each US denomination to make change..." << endl;
    for (int i = 0; i<NUM_OF_US_DENOMS; i++) {
        cout <<"$"<< setprecision(2) << fixed << US_DENOMS[i]/100.0 << "\t - " << denomCounter[i] << endl;
    }
}


int main() {

    string response;
    while (!(response == "E" || response == "e")) {
        run();
        cout << "Type \"E\" or \"e\" to exit program, or anything else to try another number> ";
        cin >> response;
    }

    return 0;
}
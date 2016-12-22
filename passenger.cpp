///////////////////////////////////////////////////////////////////////////////
// File Name:      passenger.cpp
//
// Author:         Shu Chen
// CS email:       schen265@wisc.edu
//
// Author:         Austin Schaumberg
// CS email:       schaumberg2@wisc.edu
//
// Description:    The passenger.cpp file for our final program.
//
////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <cctype>
#include <unordered_map>

#include "passenger.h"
#include "flight.h"

using namespace std;

static int passengerID_val = 1;
int passenger::totalNum_passengers = 0;

passenger::passenger(string firstName,
                     string lastName,
                     string dateOfBirth,
                     string phoneNum)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->dateOfBirth = dateOfBirth;
    this->phoneNum = phoneNum;
    this->passengerID = passengerID_val++;
    totalNum_passengers++;
}

int passenger::getId(){
    return passengerID;
}

string passenger::getLastName(){
    return lastName;
}

string passenger::getFirstName(){
    return firstName;
}

string passenger::getDateOfBirth(){
    return dateOfBirth;
}

string passenger::getPhoneNumber(){
    return phoneNum;
}

vector<flight> passenger::getFlights(){
    return flights;
}

vector<string> passenger::getSeats(){
    return seats;
}


void passenger::addFlight(string seat, flight flightX){
    flights.push_back(flightX);
    seats.push_back(seat);
}

int passenger::cancelFlight(){
    int x;
    // flight number to be returned for easy removal of passenger value.
    int flight_num = 0;

    cout << "Enter the respective corresponding digit(s) of your listed flight, you wish to cancel:"<< endl;
    cout << endl;

    if(flights.empty()){
        cout << "You have no flights reserved." << endl;
        std::cout << "Returning to the Main Menu" << std::endl;
        std::cout << std::endl;

        return flight_num;
    }

    scanf("%d", &x);
    if(x < 1 || x > flights.size()){
        cout << "Please select a valid flight you wish to cancel."<< endl;
        cout << "You have "<< flights.size()<<", which you may cancel at any time." << endl;
    }else{
        // y is the element location of desired removal
        int y = x-1;

        flight_num = flights.at(y).getId();
        flights.erase(flights.begin() + y);
        seats.erase(seats.begin() + y);
        cout << "Flight " << x << " has been canceled." << endl;
    }
    cout << "Returning to the Main Menu" << endl;
    cout << endl;

    return flight_num;

}
/*
int passenger::cancelFlight() {
    string stringX;
    // flight number to be returned for easy removal of passenger value.
    int flight_num = 0;
    cout << "Enter the respective corresponding digit(s) of your listed flight, you wish to cancel:"<< endl;;
    cout << "If you wish to leave this menu, enter 'q' or 'Q' and hit enter." << endl;

    while (getline(cin, stringX) && stringX.length() > 0) {

        // If User enters q or Q breeaks out of method.
        if ((stringX == "q") || (stringX == "Q")) {
            return 0;
        } else {
            int x = stoi(stringX);
            if (x < 1 || x > flights.size()) {
                cout << "Please select a valid flight you wish to cancel." << endl;
                cout << "You have " << flights.size() << ", which you may cancel at any time." << endl;
            } else {
                // y is the element location of desired removal
                int y = x - 1;

                flight_num = flights.at(y).getId();
                flights.erase(flights.begin() + y);
                seats.erase(seats.begin() + y);
                cout << "Flight " << x << " has been canceled." << endl;
            }
        }
        cout << "Returning to the Main Menu" << endl;

        return flight_num;

    }
}*/

    void passenger::printItinerary() {
        string stringX;
        string fNameX = this->getFirstName();
        string lNameX = this->getLastName();
        string dateOfBirthX = this->getDateOfBirth();
        string phoneNumX = this->getPhoneNumber();
        int idX = this->getId();

        cout << "Passenger Name: " << fNameX << " " << lastName << endl;
        cout << "Passenger ID: " << idX << endl;
        if (flights.empty()) {
            cout << "You have no flights reserved." << endl;
            std::cout << "Returning to the Main Menu" << std::endl;
            std::cout << std::endl;
            return;
        } else {
            for (int i = 0; i < flights.size(); i++) {
                int j = i + 1;
                std::cout << std::endl;
                cout << "Flight " << j << ":" << endl;
                cout << "     Date of Flight: " << flights.at(i).getDateOfFlight() << endl;
                cout << "     Seat: " << flights.at(i).findPassenger(passengerID) << endl;
                cout << "     Boarding Time: " << flights.at(i).getBoardingTime() << endl;
                cout << "     Departure Time: " << flights.at(i).getDepartureTime() << endl;
                cout << "     Boarding Time: " << flights.at(i).getArrivalTime() << endl;
                std::cout << std::endl;
            }
        }
    }


//Itinerary passenger::getItinerary(){
//    return itinerary;
//}

//void setItineraryObj(Itinerary insertHere){
//   this->itinerary = insertHere;
//}





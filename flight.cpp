////////////////////////////////////////////////////////////////////////////////
// File Name:      flight.cpp
//
// Author:         Shu Chen
// CS email:       schen265@wisc.edu
//
// Author:         Austin Schaumberg
// CS email:       schaumberg2@wisc.edu
//
//
// Description:    The flight.cpp file for our final program.
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

#include "flight.h"
#include "passenger.h"



using namespace std;


static int flightID_val = 1000;
static int totalNumberOfFlights = 0;

flight::flight(){
}
flight::flight(string region,
               string origin,
               string destination,
               string boardingTime,
               string departureTime,
               string arrivalTime,
               int duration,
               int distance)
{
    this->flightID = flightID_val++;
    this->region = region;
    this->origin = origin;
    this->destination = destination;
    this->dateOfFlight = "" "";
    this->boardingTime = boardingTime;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
    this->duration = duration;
    this->distance = distance;
    this->totalSeatsAvailable = 100;
    this->numFirstClassSeats  = 20;
    this->numBusClassSeats    = 20;
    this->numEconomySeats     = 60;
    totalNumberOfFlights++;
}

int flight::getId(){
    return flightID;
}

string flight::getRegion(){
    return region;
}

string flight::getOriginCity(){
    return origin;
}

string flight::getDestinationCity(){
    return destination;
}

string flight::getDateOfFlight(){
    return dateOfFlight;
}

void flight::setDateOfFlight(string date){

    // store the flight date value
    this->dateOfFlight = date;
}

string flight::getBoardingTime(){
    return boardingTime;
}

string flight::getDepartureTime(){
    return departureTime;
}

string flight::getArrivalTime(){
    return arrivalTime;
}

int flight::getDuration(){
    return duration;
}

int flight::getDistance(){
    return distance;
}

int flight::getTotalSeatsAvailable(){
    return totalSeatsAvailable;
}

int flight::getFirstClSeatsAvailable(){
    return numFirstClassSeats;
}

int flight::getBusinessCLSeatsAvailable(){
    return numBusClassSeats;
}

int flight::getEconomySeatsAvailable(){
    return numBusClassSeats;
}

void flight::bookOpenSeat(int row, char seat, int passengerID)
{
    int i;
    if (seat != 'A' && seat != 'B' && seat != 'C' && seat != 'D'){
        cout << "Please, select a vaild seat: A, B, C or D"<< endl;
    }

    if(row < 1 || row > 25){
        cout << "Please, select a vaild row: 1 - 25"  << endl;
        cout << "Rows 1 - 5 are First Class seats"    << endl;
        cout << "Rows 6 - 10 are Buisness Class seats"<< endl;
        cout << "Rows 11 - 25 are Economy Class seats"<< endl;
    }
    // Overload chars fed by user to allow for easy access to plane seating.
    if (seat == 'A'){
        i = 0;
    }
    else if (seat == 'B'){
        i =1;
    }
    else if (seat == 'C'){
i= 2;
    }
    else if (seat == 'D'){
i = 3;
    }


    // downsize row value by 1 to allow for easy array access.
    row = row - 1;

    if(isSeatTaken(row,i)){
        cout << "Please, select another seat. This seat has already been reserved" << endl;
    }
    else{
        seatsAvailable[row][i] = passengerID;
    }
}

void flight::printSeatingChart()
{
    // variables for seating chart print out
    string aisle     = "   ";
    string seatOpen  = "|___|";
    string seatTaken = "|_X_|";

    // start of hardc-coded seating chart
    cout << "\n|_X_| = Seat Taken\n"    << endl;
    cout << "|___| = Seat Available"    << endl;
    cout << "\n          (FRONT)\n"     << endl;
    cout << "  | A || B |   | C || D |" << endl;
    cout << "  |___||___|___|___||___|" << endl;

    // loop parses through the flight's seatsAvailable array
    // identifies if seat is taken or available for user to see.
    for (int i = 0; i < 25; i++)
    {
        /* code */
        int displayRow = i +1;

        // prints seating class lables (Economy class @ very end)
        displayRow == 6  ? cout << "  [   First Class 1-5   ]" << endl : cout <<"";
        displayRow == 11 ? cout << "  [ Business Class 6-10 ]" << endl : cout <<"";

        // conditional for print formating
        // single vs double diget row values
        if(displayRow < 10){
            cout << displayRow << " ";
        }
        else{
            cout << displayRow;
        }


        for (int j = 0; j < 4; j++)
        {
            // prints the aisle buffer with no label
            if(displayRow < 15 || displayRow > 19){
                j == 2 ? cout << aisle : cout <<"";
            }
                ////////////////////////////////////////////////////
                // Sorry, I know this is messy, but not sure of   //
                // how to make it cleaner.                        //
                //                                                //
                // prints the aisle label vertically in the prompt//
                ////////////////////////////////////////////////////
            else if(displayRow == 15){

                j == 2 ? cout << " A ": cout <<"";;
            }
            else if(displayRow == 16){ j == 2 ? cout << " I ": cout <<"";}
            else if(displayRow == 17){ j == 2 ? cout << " S ": cout <<"";}
            else if(displayRow == 18){ j == 2 ? cout << " L ": cout <<"";}
            else if(displayRow == 19){ j == 2 ? cout << " E ": cout <<"";}
            ////////////////////////////////////////////////////

            // conditional prints if seat is taken
            if(isSeatTaken(i,j)){
                cout << seatTaken;
            }
            else{
                cout << seatOpen;
            }
        }
        // start next row of seating chart
        std::cout <<'\n';
        // if last row output, print seating class label
        displayRow == 25 ? cout <<"  [ Economy Class 11-25 ]"<< endl : cout <<"";;
    }
    //
    cout << "\n          (REAR)\n" << endl;
}

bool flight::isSeatTaken(int row, int seat){
    if(seatsAvailable[row][seat] != 0){
        return true;
    }
    else{
        return false;
    }
}


void flight::fillFlights(ifstream &inFile, vector<flight> &scheduledFlightData)
{
    // Variable used to intake and split up flight info
    string line;

    // Retrieve the current line of the file
    while (getline(inFile, line))
    {
        // Vector used to take comma delimited line and
        // split into the relevant variables for new flight
        vector<string> flightInfo;

        // Split the current line into components
        string str;
        stringstream stream(line);
        while (getline(stream, str, ','))
        {
            flightInfo.push_back(str);
        }
        // End of split.

        // Split and set flight information
        string region      = flightInfo[0];
        string origin      = flightInfo[1];
        string destination = flightInfo[2];
        // Each line of the input file has 3 flights scheduled
        // for each city in a  1 - 1 relation ship (6 flights total)
        string boardingTimeF1 = flightInfo[3];
        string departureTimeF1= flightInfo[4];
        string arrivalTimeF1  = flightInfo[5];

        string boardingTimeF2 = flightInfo[6];
        string departureTimeF2= flightInfo[7];
        string arrivalTimeF2 = flightInfo[8];

        string boardingTimeF3 = flightInfo[9];
        string departureTimeF3= flightInfo[10];
        string arrivalTimeF3  = flightInfo[11];
        int distance        = atoi(flightInfo[12].c_str());
        int duration        = atoi(flightInfo[13].c_str());


        flight *newFlight1 = new flight(
                region,
                origin,
                destination,
                boardingTimeF1,
                departureTimeF1,
                arrivalTimeF1,
                duration,
                distance);

        flight *newFlight2 = new flight(
                region,
                origin,
                destination,
                boardingTimeF2,
                departureTimeF2,
                arrivalTimeF2,
                duration,
                distance);

        flight *newFlight3 = new flight(
                region,
                origin,
                destination,
                boardingTimeF3,
                departureTimeF3,
                arrivalTimeF3,
                duration,
                distance);

        // Push new scheduled flights into the Flight vector
        scheduledFlightData.push_back(*newFlight1);
        scheduledFlightData.push_back(*newFlight2);
        scheduledFlightData.push_back(*newFlight3);
    }
}

string flight::findPassenger(int passengerID){
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 4; ++j) {
            if(seatsAvailable[i][j] == passengerID){

                char c = j;
                string seatAssign = to_string(i) + c;
                return seatAssign;

            }
        }
    }
}


void flight::removePassenger(int passengerID){
    string seatToDelete = findPassenger(passengerID);
    char c;
    // seat letter (column)
    if(seatToDelete.length() == 2){
        c = seatToDelete[2];
    }else{
        c = seatToDelete[1];
    }
    // seat number (row)
    int i = atoi(seatToDelete.substr(0,1).c_str());

    // overloads values of the seat column
    unsigned char A = 0;
    unsigned char B = 1;
    unsigned char C = 2;
    unsigned char D = 3;

    int j = (int)c;


    // Effectively clears passenger value from seat
    seatsAvailable[i][j] = 0;

}







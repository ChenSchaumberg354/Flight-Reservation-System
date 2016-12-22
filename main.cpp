////////////////////////////////////////////////////////////////////////////////
// File Name:      main.cpp
//
// Author:         Shu Chen
// CS email:       schen265@wisc.edu
//
// Author:         Austin Schaumberg
// CS email:       schaumberg2@wisc.edu
//
//
// Description:    The main.cpp file for our final program.
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
#include <string.h>

#include "flight.h"
#include "passenger.h"



//////////////////// START Random Methods Used for Passenger Creation ///////////////////////////////////


flight findFlight(int xFlightID, vector<flight> xFlights){

    flight foundFlight;

    for (vector<flight>::const_iterator i = xFlights.begin(); i != xFlights.end(); ++i) {
        flight currFlight = *i;
        if(currFlight.getId() == xFlightID){
            return currFlight;
        }
    }

    return foundFlight;

}

passenger findPassenger(int xpassID, vector<passenger> xPassengers){

    passenger p("","","","");
    for (vector<passenger>::const_iterator i = xPassengers.begin(); i != xPassengers.end(); ++i) {
        passenger currPassenger = *i;
        if(currPassenger.getId() == xpassID){
            return currPassenger;
        }
    }

    return p;

}


bool formatVerificatoin(string strUserInput, string strTemplate){

    if (strTemplate.length() != strUserInput.length())
        return false;

    // Step through the user input to see if it matches
    for (unsigned int nIndex=0; nIndex < strTemplate.length(); nIndex++)
    {
        switch (strTemplate[nIndex])
        {
            case '#': // match a digit
                if (!isdigit(strUserInput[nIndex]))
                    return false;
                break;
            case '_': // match a whitespace
                if (!isspace(strUserInput[nIndex]))
                    return false;
                break;
            case '@': // match a letter
                if (!isalpha(strUserInput[nIndex]))
                    return false;
                break;
            case '?': // match anything
                break;
            default: // match the exact character
                if (strUserInput[nIndex] != strTemplate[nIndex])
                    return false;
        }
    }

    return true;
}

/**
* @brief Uses a bunch of prompts to collect data from the user
 *
 * and returns a newly crated passenger object.
*/
passenger createPassenger(){
    string fName = "";
    string lName = "";
    string dateOfBirthString ="";
    string phoneNum = "";


    // How to get a string/sentence with spaces
    cout << "Please enter your first name:\n>";
    getline(cin, fName);

    cout << "Please enter your last name:\n>";
    getline(cin, lName);



    //// START inifinte loop until Date of Birth entered correctly ///
    while(1) {
        int dd, mm, yy;

        printf("Please enter your date of birth (DD/MM/YYYY format): ");
        scanf("%d/%d/%d", &dd, &mm, &yy);

        //checks the year
        if (yy >= 1900 && yy <= 9999) {
            //checks the month
            if (mm >= 1 && mm <= 12) {
                //check the proper days
                if ((dd >= 1 && dd <= 31) &&
                    (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
                    printf("Date is valid.\n");
                else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
                    printf("Date is valid.\n");
                else if ((dd >= 1 && dd <= 28) && (mm == 2))
                    printf("Date is valid.\n");
                else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
                    printf("Date is valid.\n");
                else
                    printf("Day is invalid.\n");
            } else
                printf("Month is not valid.\n");
        } else
            printf("Year is not valid.\n");

        std::ostringstream s1, s2, s3;
        s1 << dd;
        s2 << mm;
        s3 << yy;
        dateOfBirthString = s1.str() + "/" + s2.str() + "/" + s3.str();

        if(formatVerificatoin(dateOfBirthString, "##/##/####"))
            break;
    }
    //// END inifinte loop until Date of Birth entered correctly ///




    //// START inifinte loop until phone entered correctly ///
    while(1) {
        cout << "Enter a phone number (###) ###-####: ";
        getline(cin, phoneNum); // get the entire line, including spaces
        if (formatVerificatoin(phoneNum, "(###) ###-####"))
            break;
    }
    //// END inifinte loop until phone entered correctly ///
    passenger newPassenger = passenger(fName, lName, dateOfBirthString, phoneNum);

    return newPassenger;

}




void fillPassengers(ifstream &inFile, vector<passenger> &oldPassengerData)
{
    // Variable used to intake and split up flight info
    string line;

    // Retrieve the current line of the file
    while (getline(inFile, line))
    {
        // Vector used to take comma delimited line and
        // split into the relevant variables for new passenger
        vector<string> passengerInfo;

        // Split the current line into components
        string str;
        stringstream stream(line);
        while (getline(stream, str, ','))
        {
            passengerInfo.push_back(str);
        }
        // End of split.

        // Split and set passenger information
        string fName      = passengerInfo[0];
        string lName      = passengerInfo[1];
        string dateOfBirth = passengerInfo[2];
        string phoneNum = passengerInfo[3];



        passenger *passengerX = new passenger(fName, lName, dateOfBirth, phoneNum);

        // Push new scheduled passengers into the passenger vector
        oldPassengerData.push_back(*passengerX);
    }
}


void writePassengersToFile(vector<passenger> &oldPassengerData, ofstream &passengerFile)
{
    for (vector<passenger>::const_iterator i = oldPassengerData.begin(); i != oldPassengerData.end(); ++i) {
        passenger pX = *i;

        vector<string> pXinformation;

        string fName      = pX.getFirstName()+",";
        string lName      = pX.getLastName()+",";
        string dateOfBirth = pX.getDateOfBirth()+",";
        string phoneNum = pX.getPhoneNumber();

        pXinformation.push_back(fName);
        pXinformation.push_back(lName);
        pXinformation.push_back(dateOfBirth);
        pXinformation.push_back(phoneNum);
        for (vector<string>::const_iterator j = pXinformation.begin(); j != pXinformation.end(); ++j) {
            passengerFile << *j << '\n';
        }
    }


}

void writePassengersFlightsToFile(vector<passenger> &oldPassengerData, ofstream &passengerFlightsFile)
{
    int count = 0;
    for (vector<passenger>::const_iterator i = oldPassengerData.begin(); i != oldPassengerData.end(); ++i) {
        // declare passenger
        passenger pX = *i;
        //////////////////////////////
        vector<flight> pxFlights = pX.getFlights();
        vector<string> pxSeats = pX.getSeats();
        vector<string> pXinformation;
        //////////////////////////////


        string passengersFlightIDX = "";
        string passengersSeatAssignmentX = "";

        string passengerIDX      = pX.getId()+",";
        passengersFlightIDX = to_string(pxFlights.at(count).getId())+",";
        passengersSeatAssignmentX = pxSeats.at(count);


        pXinformation.push_back(passengerIDX);
        pXinformation.push_back(passengersFlightIDX);
        pXinformation.push_back(passengersSeatAssignmentX);

        for (vector<string>::const_iterator j = pXinformation.begin(); j != pXinformation.end(); ++j) {
            passengerFlightsFile << *j << '\n';
        }
        count++;
    }


}

void fillPassengersFlights(ifstream &inFile, vector<passenger> &passengerVector, vector<flight> &flightVector)
{
    // Variable used to intake and split up info
    string line;

    // Retrieve the current line of the file
    while (getline(inFile, line))
    {
        // Vector used to take comma delimited line and
        // split into the relevant variables for passengers old booked flights
        vector<string> passengerInfo;

        // Split the current line into components
        string str;
        stringstream stream(line);
        while (getline(stream, str, ','))
        {
            passengerInfo.push_back(str);
        }
        // End of split.

        // Split and set passenger information to book relevant flight with seat.
        string passengerIDX = passengerInfo[0];
        string flightIDX      = passengerInfo[1];
        string seatAssigned = passengerInfo[2];

        int passengerID = stoi(passengerIDX);
        int flightID = stoi(flightIDX);

        passenger currPass = findPassenger(passengerID, passengerVector);
        flight currFlight = findFlight(flightID, flightVector);

        //////////
        string seatAssignedX = seatAssigned;
        string a;
        string b;
        int i;
        char c;

        // seat letter (column)
        if(seatAssignedX.length() <= 2){
            a = seatAssignedX[0];
            stringstream concat;
            concat<<a;
            string d = concat.str();
            i = stoi(d);
            c = seatAssignedX[1];
        }
        else if(seatAssignedX.length() < 2){
            a = seatAssignedX[0];
            b = seatAssignedX[1];
            c = seatAssignedX[2];
            stringstream concat;
            concat<<a<<b;
            string d = concat.str();
            i = stoi(d);
        }

        /////////

        currFlight.bookOpenSeat(i, c, passengerID);
        currPass.addFlight(seatAssigned, currFlight);




    }
}


//////////////////// END of Random Methods Used for Passenger Creation ///////////////////////////////////

void printSplitLine(){
    for(int i = 0; i < 35; i++){
        std::cout << "*";
    }
    std::cout <<'\n';
}

int getUserChoice(){
    int choice;

    bool wrong_choice = true;
    while(wrong_choice){
        printSplitLine();
        std::cout << "*Welcome to shu-stin Airlines!" << std::endl;
        std::cout << "*Please select from one of the following options:[Enter choice number]" << std::endl;
        printSplitLine();
        std::cout << "1.Book a flight reservation" << std::endl;
        std::cout << "2.Cancel flight reservation" << std::endl;
        std::cout << "3.View your itinerary" << std::endl;
        std::cout << "4.Exit" << std::endl;
        std::cin >> choice;
        if(!std::cin.fail() && choice >=1 && choice <= 5){
            wrong_choice = false;
        }else{
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            printSplitLine();
            std::cout << "Choose between 1 and 5 inclusive" << std::endl;
            printSplitLine();
        }

    }
    return choice;
}

int getSecondChoice(){
    int choice;
    bool wrong_choice = true;
    while(wrong_choice){
        std::cout << "1.One Way" << std::endl;
        std::cout << "2.Round Trip" << std::endl;
        std::cin >> choice;
        if(!std::cin.fail() && choice >= 1 && choice <= 2){
            wrong_choice = false;
        }else{
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            printSplitLine();
            std:: cout << "Select 1 or 2 " << std::endl;
            printSplitLine();
        }
    }
    return choice;
}

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(), s.end(), [](char c){ return !std::isdigit(c);}) == s.end();
}

std::string getDate(){
    //TODO: Create method that only takes valid
    int dd,mm,yy;

    printf("Enter date of flight (DD/MM/YYYY format): ");
    scanf("%d/%d/%d",&dd,&mm,&yy);

    //checks the year
    if(yy>=2016 && yy<=9999)
    {
        //checks the month
        if(mm>=1 && mm<=12)
        {
            //check the proper days
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                printf("Date is valid.\n");
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                printf("Date is valid.\n");
            else if((dd>=1 && dd<=28) && (mm==2))
                printf("Date is valid.\n");
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                printf("Date is valid.\n");
            else
                printf("Day is invalid.\n");
        }
        else
            printf("Month is not valid.\n");
    }
    else
        printf("Year is not valid.\n");

    std::ostringstream s1, s2, s3;
    s1<<dd;s2<<mm;s3<<yy;
    string dateString = s1.str()+"/"+s2.str()+"/"+s3.str();
//    string dateString = dd+"/"+mm+"/"+yy;

    // store the flight date value
   return dateString;
}

void printDepartureCities(){
    printSplitLine();
    std::cout << "*   Flying From    * " << std::endl;
    printSplitLine();
    std::cout << "Please select From one of the following options: " << std::endl;
    printSplitLine();
    std::cout << "United States of America " << std::endl;
    printSplitLine();
    std::cout << "1. Chicago" << std::endl;
    std::cout << "2. Los Angeles" << std::endl;
    std::cout << "3.Houston" << std::endl;
    std::cout << "4.New York City" << std::endl;
    std::cout << "5. Philadelphia" << std::endl;
    printSplitLine();
    std::cout << "People's Republic of China" << std::endl;
    printSplitLine();
    std::cout << "6. Beijing " << std::endl;
    std::cout << "7. Guangzhou" << std::endl;
    std::cout << "8. Shanghai " << std::endl;
    std::cout << "9. Shenzhen" << std::endl;
    std::cout << "10.Tianjin" << std::endl;
}
void printDestinationCities(){
    printSplitLine();
    std::cout << "*   Flying To    * " << std::endl;
    printSplitLine();
    std::cout << "Please select From one of the following options: " << std::endl;
    printSplitLine();
    std::cout << "United States of America " << std::endl;
    printSplitLine();
    std::cout << "1. Chicago" << std::endl;
    std::cout << "2. Los Angeles" << std::endl;
    std::cout << "3.Houston" << std::endl;
    std::cout << "4.New York City" << std::endl;
    std::cout << "5. Philadelphia" << std::endl;
    printSplitLine();
    std::cout << "People's Republic of China" << std::endl;
    printSplitLine();
    std::cout << "6. Beijing " << std::endl;
    std::cout << "7. Guangzhou" << std::endl;
    std::cout << "8. Shanghai " << std::endl;
    std::cout << "9. Shenzhen" << std::endl;
    std::cout << "10.Tianjin" << std::endl;
}

std::string getCity(int choice){
    std::cout << "in getCity" << std::endl;
    std::string city;
    if(choice == 1){

        city = "Chicago";
    }
    if(choice == 2){
        city = "Los Angeles";
    }
    if (choice == 3){
        city = "Houston";
    }
    if(choice == 4){
        city = "New York City";
    }
    if(choice == 5){
        city = "Philadelphia";
    }
    if(choice == 6){
        city = "Beijing";
    }
    if(choice == 7){
        city = "Guangzhou";
    }
    if(choice == 8){
        city = "Shanghai";
    }
    if(choice == 9){
        city = "Shenzhen";
    }
    if(choice == 10){
        city = "Tianjin";
    }
    return city;
}
//int passengerID = 0;
int main(int argc, char *argv[]) {

    //////////////// FILE READ/INPUT START //////////////////////
    //////////////// FILE READ/INPUT START //////////////////////
    // Check if the program is given 3 command line arguments
    // including the program name.
    if (argc != 4) {
        std::cerr << "USAGE: ./a.out <FlightDataFile> <PassengerDataFile> <PassengerFlightDataFile>"
                  << std::endl;
        return -1;
    }

    // Open the input file containing the flight data.
    std::ifstream FlightDataFile(argv[1]);
    if (!FlightDataFile.is_open()) {
        std::cerr << "Input file " << argv[1] << " cannot be opened."
                  << std::endl;
        return -1;
    }

    // Open the input file containing the passenger data.
    std::ifstream PassengerDataFile(argv[2]);
    if (!PassengerDataFile.is_open()) {
        std::cerr << "Input file " << argv[2] << " cannot be opened."
                  << std::endl;
        return -1;
    }


    // Open the input file containing the passenger data.
    std::ifstream PassengerFlightDataFile(argv[3]);
    if (!PassengerFlightDataFile.is_open()) {
        std::cerr << "Input file " << argv[3] << " cannot be opened."
                  << std::endl;
        return -1;
    }

    flight F;
    //A vector to store all flights.
    std::vector<flight> flightVector;

    //A vector of passengers
    std::vector<passenger> allPassengersVector;

    // Read a collections of flights from the flightData file
    // and store it in a vector.
    F.fillFlights(FlightDataFile, flightVector);

    fillPassengers(PassengerDataFile, allPassengersVector);

    fillPassengersFlights(PassengerFlightDataFile, allPassengersVector, flightVector);
    //////////////// FILE READ/INPUT END //////////////////////




    bool finish = true;
    int triggerXY = 1;
    while(finish){

        int user_choice = getUserChoice();

        if (user_choice == 1) {
                std::string lastName;
                std::string firstName;
                std::string phoneNum;
                std::string dateOfBirth;
                std::vector<passenger> allPassengersVector;

                //Ask user enter their information
                std::cout << "please enter your personal information" << std::endl;
                std::cout << "Enter your last Name" << std::endl;
                std::cin.ignore(10000,'\n');
                std::getline(std::cin, lastName);
                std::cout << "Enter your first Name" << std::endl;
                std::getline(std::cin, firstName);
                std::cout << "Enter your phone number" << std::endl;
                std::getline(std::cin, phoneNum);
                std::cout << "Enter your birth day in dd/mm/yy format" << std::endl;
                dateOfBirth = getDate();
                passenger p1(firstName, lastName,dateOfBirth, phoneNum);
                std::cout << p1.getId() << std::endl;
                allPassengersVector.push_back(p1);


                printSplitLine();
                std::cout << "*please select from one of the following options" << std::endl;
                printSplitLine();

                int secondChoice = getSecondChoice();

                //User select one way
                if(secondChoice == 1){
                    flight F1;
                    printSplitLine();
                    std::cout << "*  Departure Date  * " << std::endl;
                    std::string date = getDate();
                    F1.setDateOfFlight(date);

                    //get cities
                    printDepartureCities();
                    std::cout << "enter the departure city number" << std::endl;
                    int dep;
                    std::cin >> dep;
                    bool wrong_input = true;
                    while(wrong_input){
                        if(!std::cin.fail() && dep >= 1 && dep <= 10){
                            wrong_input = false;
                        }else{
                            std::cout << "Enter number between 1 and 10" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> dep;
                        }
                    }
                    //Destination
                    printDestinationCities();
                    std::cout << "Enter destination city number" << std::endl;
                    int des;
                    std::cin >> des;
                    wrong_input = true;
                    while(wrong_input){
                        if(!std::cin.fail() && des >= 1 && des <= 10){
                            wrong_input = false;
                        }else{
                            std::cout << "Enter number between 1 and 10" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> des;
                        }
                    }
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::string originCity = getCity(dep);
                    std::string destCity = getCity(des);

                    //find all the available flights for these citie
                    std::vector<flight> availableFlights;
                    for(auto it = flightVector.begin(); it != flightVector.end(); it++){
                        if((*it).getOriginCity() == originCity && (*it).getDestinationCity() == destCity){
                            availableFlights.push_back(*it);
                        }
                    }
                    std::cout << "Select a paticular flight" << std::endl;
                    std::cout << "  Departure Time" << "     " << "Arrival Time" << std::endl;
                    int num = 1;
                    for(auto it = availableFlights.begin(); it != availableFlights.end(); it++){
                        std::cout << num << ". "<< (*it).getDepartureTime() << "           " << (*it).getArrivalTime() << std::endl;
                        num++;
                    }


                    //get user choice flight number
                    int flightNum;
                    std::cin >> flightNum;
                    bool wrongInput = true;
                    while(wrongInput){
                        if(!std::cin.fail() && flightNum >= 1 && flightNum <= 3){
                            wrongInput = false;
                        }else{
                            std::cout << "Please enter a number between 1 and 3" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> flightNum;
                        }
                    }
                    //select seat
                    std::cout << "Select a Seat " << std::endl;
                    printSplitLine();
                    std::cout << " Please select a seat in the format: Seat Number + Letter" << std::endl;
                    std::cout << "Example: 2A, 25B, 15C" << std::endl;
                    availableFlights[flightNum - 1].printSeatingChart();
                    std::string seat;
                    std::cin >> seat;
                    bool wrongseat = true;
                    while(wrongseat){
                        if(seat.length() == 2 || seat.length() == 3){
                            wrongseat = false;
                        }else{
                            std::cout << "Enter available seat" << std::endl;
                            std::cin >> seat;
                        }
                    }
                    int row;
                    std::string col;
                    if(seat.length() == 2){
                        row = std::stoi(seat.substr(0,1));
                        col = seat.substr(1,1);
                    }
                    if(seat.length() == 3){
                        row = std::stoi(seat.substr(0,2));
                        col = seat.substr(2,2);
                    }
                    //TODO , FILL PASSENGER ID
                    availableFlights[flightNum - 1].bookOpenSeat(row,col[0],p1.getId());


                }




                //User select round way
                if(secondChoice == 2){
                    /////////////////////////////////////////////////////////////////////////FIRST TRIP//////////////////////////////////////////////////////////////////////////////////////////////////////////
                    std::cout << "Ente info for first trip" << std::endl;
                    flight F1;
                    printSplitLine();
                    ////////departure-First Flight/////////////////////////////////(Departure)/////////////////////////////////////////////////////////////////////////
                    std::cout << "*  Departure Date  * " << std::endl;
                    printSplitLine();
                    std::string departure_date = getDate();
                    printSplitLine();
                    F1.setDateOfFlight(departure_date);
                    printDepartureCities();
                    std::cout << "Enter departure city number" << std::endl;
                    int dep;
                    std::cin >> dep;
                    bool wrong_input = true;
                    while(wrong_input){
                        if(!std::cin.fail() && dep >= 1 && dep <= 10){
                            wrong_input = false;
                        }else{
                            std::cout << "Enter number between 1 and 10" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> dep;
                        }
                    }

                    ////////////////////////////////////////////////////////////(Destination)///////////////////////////////////////////////////////////////////////////
                    //destination-First Flight
                    printDestinationCities();
                    std::cout << "Enter destination city number" << std::endl;
                    int des;
                    std::cin >> des;
                    wrong_input = false;
                    while(wrong_input){
                        if(!std::cin.fail() && des >= 1 && des <= 10){
                            wrong_input = false;
                        }else{
                            std::cout <<"Enter number between 1 and 10" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> des;
                        }
                    }

                    // select flight for your first trip///////////////////////////////////////////(Flight)//////////////////////////////////////////
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::string originCity = getCity(dep);
                    std::string destCity = getCity(des);

                    //find all the available flights for these citie
                    std::vector<flight> availableFlights;
                    for(auto it = flightVector.begin(); it != flightVector.end(); it++){
                        if((*it).getOriginCity() == originCity && (*it).getDestinationCity() == destCity){
                            availableFlights.push_back(*it);
                        }
                    }
                    std::cout << "Select a paticular flight" << std::endl;
                    std::cout << "  Departure Time" << "     " << "Arrival Time" << std::endl;
                    int num = 1;
                    for(auto it = availableFlights.begin(); it != availableFlights.end(); it++){
                        std::cout << num << ". "<< (*it).getDepartureTime() << "           " << (*it).getArrivalTime() << std::endl;
                        num++;
                    }


                    //get user choice flight number
                    int flightNum;
                    std::cin >> flightNum;
                    bool wrongInput = true;
                    while(wrongInput){
                        if(!std::cin.fail() && flightNum >= 1 && flightNum <= 3){
                            wrongInput = false;
                        }else{
                            std::cout << "Please enter a number between 1 and 3" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> flightNum;
                        }
                    }

                    //select seat
                    std::cout << "Select a Seat " << std::endl;
                    printSplitLine();
                    std::cout << " Please select a seat in the format: Seat Number + Letter" << std::endl;
                    std::cout << "Example: 2A, 25B, 15C" << std::endl;
                    availableFlights[flightNum - 1].printSeatingChart();
                    std::string seat;
                    std::cin >> seat;
                    bool wrongseat = true;
                    while(wrongseat){
                        if(seat.length() == 2 || seat.length() == 3){
                            wrongseat = false;
                        }else{
                            std::cout << "Enter available seat" << std::endl;
                            std::cin >> seat;
                        }
                    }
                    int row;
                    std::string col;
                    if(seat.length() == 2){
                        row = std::stoi(seat.substr(0,1));
                        col = seat.substr(1,1);
                    }
                    if(seat.length() == 3){
                        row = std::stoi(seat.substr(0,2));
                        col = seat.substr(2,2);
                    }

                    availableFlights[flightNum - 1].bookOpenSeat(row,col[0],p1.getId());

//////////////////////////////////////////////////////////////////////////////////////SECOND TRIP//////////////////////////////////////////////////////////////////////////////////////////
                    std::cout << "Enter info for second trip" << std::endl;
                    flight F2;
                    std::cout << "* Return Date " << std::endl;
                    //printSplitLine();
                    std::string return_date = getDate();
                    //std::cout << "here" << std::endl;
                    F2.setDateOfFlight(return_date);


                    //check user input
                    //bool wrong_choice = true;
                    //while(wrong_choice){
                    //std::string choice;
                    //getline(std::cin, choice);
                    //int num = std::stoi(choice.c_str());
                    //if(num >=1 && num <= 10){
                    //wrong_choice = false;
                    //}else{
                    //std::cout << "Please select from the above" << std::endl;
                    //}
                    //}

                    std::vector<flight> availableFlights2;
                    for(auto it = flightVector.begin(); it != flightVector.end(); it++){
                        if((*it).getOriginCity() == destCity && (*it).getDestinationCity() == originCity){
                            availableFlights2.push_back(*it);
                        }
                    }
                    std::cout << "Select a paticular flight" << std::endl;
                    std::cout << "  Departure Time" << "     " << "Arrival Time" << std::endl;
                    num = 1;
                    for(auto it = availableFlights2.begin(); it != availableFlights2.end(); it++){
                        std::cout << num << ". "<< (*it).getDepartureTime() << "           " << (*it).getArrivalTime() << std::endl;
                        num++;
                    }

                    //get user choice flight number
                    //int flightNum;
                    std::cin >> flightNum;
                    wrongInput = true;
                    while(wrongInput){
                        if(!std::cin.fail() && flightNum >= 1 && flightNum <= 3){
                            wrongInput = false;
                        }else{
                            std::cout << "Please enter a number between 1 and 3" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cin >> flightNum;
                        }
                    }

                    //select seat
                    std::cout << "Select a Seat " << std::endl;
                    printSplitLine();
                    std::cout << " Please select a seat in the format: Seat Number + Letter" << std::endl;
                    std::cout << "Example: 2A, 25B, 15C" << std::endl;
                    availableFlights2[flightNum - 1].printSeatingChart();
                    std::cin >> seat;
                    wrongseat = true;
                    while(wrongseat){
                        if(seat.length() == 2 || seat.length() == 3){
                            wrongseat = false;
                        }else{
                            std::cout << "Enter available seat" << std::endl;
                            std::cin >> seat;
                        }
                    }
                    //int row;
                    //std::string col;
                    if(seat.length() == 2){
                        row = std::stoi(seat.substr(0,1));
                        col = seat.substr(1,1);
                    }
                    if(seat.length() == 3){
                        row = std::stoi(seat.substr(0,2));
                        col = seat.substr(2,2);
                    }

                    availableFlights2[flightNum - 1].bookOpenSeat(row,col[0],p1.getId());
                }
                //break;
                //}
                std::cout << "Your Itinerary/Passenger ID is: "<< p1.getId()<<  std::endl;
                std::cout << "Your seat has been sucessfully reserved your seat."<< std::endl;
                std::cout << std::endl;

            }
                //break;

        if (user_choice == 2) {

            std::cout << std::endl;
            printSplitLine();
            std::cout << "Please enter your Intinerary identification number" << std::endl;
            std::cout << "Returning to the Main Menu" << std::endl;
            printSplitLine();
            bool trigger = false;
            int Itinerary;
            while (!(cin >> Itinerary)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.  Try again: ";
            }
            printSplitLine();
            //TODO distinguish one way and round way and print the prompt
            int j = Itinerary;
            // placeholder for passenger ID
            int pID;
            int flight2cancel;
            // add all passengers to the vector "allPassengersVector"
            // finds the passenger's ID and prints their relevant itinerary information
            for (std::vector<passenger>::iterator it = allPassengersVector.begin();
                 it != allPassengersVector.end(); ++it) {
                //p1 set to relevant ID entered
                passenger p1 = *it;
                if (p1.getId() == j) {
                    // retrieve passenger ID
                    pID = p1.getId();
                    // Print itinerary
                    p1.printItinerary();
                    flight2cancel = p1.cancelFlight();
                    trigger = true;
                }

            }
            // variable will be used to retireve flight number and remove passenger from flight.
            flight flightPlaceHolder;

            // passenger ID was not found exit method.
            if (trigger == false) {
                std::cout << "No passengers with that ID number exist in our system." << std::endl;
                std::cout << "Returning to the Main Menu" << std::endl;
                std::cout << std::endl;
            } else {

                //should remove passenger seat assignment from flight, not sure why IDE is throwing an error
                for (std::vector<flight>::iterator it = flightVector.begin(); it != flightVector.end(); ++it) {

                    flightPlaceHolder = *it;
                    if (flightPlaceHolder.getId() == flight2cancel) {
                        flightPlaceHolder.removePassenger(pID);
                    }

                }
            }

            }



        if (user_choice == 3) {
            std::cout << std::endl;
            printSplitLine();
            std::cout << "Please enter your Intinerary identification number" << std::endl;
            printSplitLine();
            bool trigger = false;
            int Itinerary;
            while (!(cin >> Itinerary)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.  Try again: ";
            }
            printSplitLine();
            //TODO distinguish one way and round way and print the prompt
            int j = Itinerary;
            // placeholder for passenger ID
            int pID;
            int flight2cancel;
            // add all passengers to the vector "allPassengersVector"
            // finds the passenger's ID and prints their relevant itinerary information
            for (std::vector<passenger>::iterator it = allPassengersVector.begin();
                 it != allPassengersVector.end(); ++it) {
                //p1 set to relevant ID entered
                passenger p1 = *it;
                if (p1.getId() == j) {
                    // retrieve passenger ID
                    pID = p1.getId();
                    // Print itinerary
                    p1.printItinerary();
                    flight2cancel = p1.cancelFlight();
                    trigger = true;
                }

            }
            // variable will be used to retireve flight number and remove passenger from flight.
            flight flightPlaceHolder;

            // passenger ID was not found exit method.
            if (trigger == false) {
                std::cout << "No passengers with that ID number exist in our system." << std::endl;
                std::cout << "Returning to the Main Menu" << std::endl;
                std::cout << std::endl;
            } else {

                //should remove passenger seat assignment from flight, not sure why IDE is throwing an error
                for (std::vector<flight>::iterator it = flightVector.begin(); it != flightVector.end(); ++it) {

                    flightPlaceHolder = *it;
                    if (flightPlaceHolder.getId() == flight2cancel) {
                        flightPlaceHolder.removePassenger(pID);
                    }

                }
            }






            }





///////////ADD THIS TO END OF MAIN FOR PASSENGER FILE OUTPUT////////

        /*// Open an output file for storing the passenger data.

        string fileNew = "newPassengerDataFile.txt";
        std::ofstream PassengerDataFileOut(fileNew);
        if (!PassengerDataFileOut.is_open()) {
            std::cerr << "Input file " << fileNew << " cannot be opened.";
            return -1;
        }

        writePassengersToFile(allPassengersVector, PassengerDataFileOut);
        ///////////ADD THIS TO END OF MAIN FOR PASSENGER FILE OUTPUT////////


        // Normal program termination.
        // Open an output file for storing the passenger data.

        string fileNew1 = "newPassengerFlightDataFile.txt";
        std::ofstream PassengerFlightDataFileOut(fileNew1);
        if (!PassengerFlightDataFileOut.is_open()) {
            std::cerr << "Input file " << fileNew1 << " cannot be opened.";
            return -1;
        }


        //writePassengersFlightsToFile(allPassengersVector, PassengerFlightDataFileOut);
*/



        if (user_choice == 4) {

            break;
        }


        // Normal program termination.


    }
    return 0;
}

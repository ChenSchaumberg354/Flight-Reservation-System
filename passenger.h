/////////////////////////////////////////////////////////////////////////////////
// File Name:      passenger.h
//
// Author:         Shu Chen
// CS email:       schen265@wisc.edu
//
// Author:         Austin Schaumberg
// CS email:       schaumberg2@wisc.edu
//
// Description:    The header file for the Passenger class.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef FLIGHTRESSYSTEM_PASSENGER_H
#define FLIGHTRESSYSTEM_PASSENGER_H


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

#include "flight.h"

using namespace std;

/**
 * @brief An abstract base class for a Passenger.
 */
class passenger{
private:
    // passenger's unique id.
    int passengerID;
    string firstName;
    string lastName;
    string dateOfBirth;
    string phoneNum;
    static int totalNum_passengers;
    vector<flight> flights;
    vector<string> seats;
public:
    /**
     * @brief A parameterised constructor for a Passenger.
     *
     * @param firstName Passenger's first name.
     * @param lastName Passenger's last name.
     * @param dateOfBirth Passenger's date of birth.
     * @param phoneNum Passenger's phone number.
     */
    passenger(string firstName,
              string lastName,
              string dateOfBirth,
              string phoneNum);
    /**
     * @brief Getter for Passenger's id.
     *
     * @return The id of the Passenger.
     */
    int getId();

    /**
     * @brief Getter for Passenger's last name.
     *
     * @return The last name of the Passenger.
     */
    string getLastName();


    /**
     * @brief Getter for Passenger's first name.
     *
     * @return The first name of the Passenger.
     */
    string getFirstName();


    /**
     * @brief Getter for Passenger's date of birth.
     *
     * @return The date of birth of the Passenger.
     */
    string getDateOfBirth();

    /**
     * @brief Getter for Passenger's phone number.
     *
     * @return The phone number of the Passenger.
     */
    string getPhoneNumber();

    /**
     * @brief
     */
    void addFlight(string seat, flight flightX);


    /**
     * @brief
     */
    int cancelFlight();

    /**
     * @brief
     */
    void printItinerary();

    vector<flight> getFlights();

    vector<string> getSeats();

};


#endif //FLIGHTRESSYSTEM_PASSENGER_H

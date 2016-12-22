///////////////////////////////////////////////////////////////////////////////
// File Name:      flight.h
//
// Author:         Shu Chen
// CS email:       schen265@wisc.edu
//
// Author:         Austin Schaumberg
// CS email:       schaumberg2@wisc.edu
//
// Description:    The header file for the Flight class.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef FLIGHTRESSYSTEM_FLIGHT_H
#define FLIGHTRESSYSTEM_FLIGHT_H



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




using namespace std;

/**
 * @brief An abstract base class for a Flight.
 */
class flight {
private:
    // Flight's unique id.
    int flightID;
    string region;
    string origin;
    string destination;
    string dateOfFlight;
    string boardingTime;
    string departureTime;
    string arrivalTime;
    int duration;
    int distance;
    int totalSeatsAvailable;
    int numFirstClassSeats;
    int numBusClassSeats;
    int numEconomySeats;
    int seatsAvailable[25][4];

public:
    /**
     * @brief A parameterised constructor for a Flight.
     *
     * @param firstName Flight's first name.
     * @param lastName Flight's last name.
     * @param dateOfBirth Flight's date of birth.
     * @param phoneNum Flight's phone number.
     */
    flight();
    flight(string region,
           string origin,
           string destination,
           string boardingTime,
           string departureTime,
           string arrivalTime,
           int duration,
           int distance);


    /**
     * @brief Getter for Flight's id.
     *
     * @return The id of the Flight.
     */
    int getId();

    /**
     * @brief Getter for Flight's region. Either China or US.
     *
     * @return The region of the Flight.
     */
    string getRegion();

    /**
     * @brief Getter for Flight's origin city name.
     *
     * @return The origin city of the Flight.
     */
    string getOriginCity();

    /**
     * @brief Getter for Flight's destination city name.
     *
     * @return The destination city of the Flight.
     */
    string getDestinationCity();

    /**
     * @brief Getter for Flight's date to take off.
     *
     * @return The date of the Flight's take off.
     */
    string getDateOfFlight();

    /**
     * @brief Setter for Flight's date to take off.
     *
     *  sets the date of the Flight's take off.
     */
    void setDateOfFlight(string date);

    /**
     * @brief Getter for Flight's boarding time.
     *
     * @return The boarding time of the Flight.
     */
    string getBoardingTime();

    /**
     * @brief Getter for Flight's departure time.
     *
     * @return The departure time of the Flight.
     */
    string getDepartureTime();

    /**
     * @brief Getter for Flight's arrival time.
     *
     * @return The arrival time of the Flight.
     */
    string getArrivalTime();

    /**
    * @brief Getter for Flight's duration.
    *
    * @return The Flight's duration in minutes.
    */
    int getDuration();

    /**
    * @brief Getter for Flight's distance.
    *
    * @return The Flight's distance in kilometers.
    */
    int getDistance();

    /**
     * @brief Getter for Flight's available seats.
     *
     * @return The Flight's total seats available on the plane.
     */
    int getTotalSeatsAvailable();

    /**
     * @brief Getter for Flight's available first class seats.
     *
     * @return The Flight's first class seats available on the plane.
     */
    int getFirstClSeatsAvailable();

    /**
    * @brief Getter for Flight's available business class seats.
    *
    * @return The Flight's business class seats available on the plane.
    */
    int getBusinessCLSeatsAvailable();

    /**
    * @brief Getter for Flight's available economy class seats.
    *
    * @return The Flight's economy class seats available on the plane.
    */
    int getEconomySeatsAvailable();

    /**
    * @brief Setter for a passenger reserving a seat. Puts
    * the passenger's unique ID in the occupied seat.
    */
    void bookOpenSeat(int row, char seat, int passengerID);

    /**
   * @brief Printer method for Flight's seating chart.
   *
   * @return A seating chart of available seats on the flight.
   */
    void printSeatingChart();

    /**
    * @brief Boolean method, takes a desired seat.
    *
    * @return True/False depening on seat's availability.
    */
    bool isSeatTaken(int row, int seatNum);

    /**
    * @brief  method, takes a file of flight data, and parses
    *         it into a vector for use in the main method.
    */
    void fillFlights(ifstream &inFile, vector<flight> &scheduledFlightData);

    /**
    * @brief finds a passenger's seat on a flight given thier ID number.
    */
    string findPassenger(int passengerID);

    /**
    * @brief removes a passenger from a flight given their ID number.
    */
    void removePassenger(int passengerID);

};



#endif //FLIGHTRESSYSTEM_FLIGHT_H

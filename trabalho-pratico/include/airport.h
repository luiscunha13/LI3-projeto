#ifndef AIRPORT_H
#define AIRPORT_H

#include "../include/flight.h"

    typedef struct yearpass YEARPASS;

    typedef struct airport AIRPORT;

    //criar structs

    YEARPASS *newYear();

    AIRPORT *newAirport();

    //apagar structs

    void delete_YearPass(YEARPASS *y);

    void delete_Airport(AIRPORT *a);

    //sets

    void setAirportId(AIRPORT *a, const char *token);

    void setNrFlights(AIRPORT *a, int n);

    void setNrDelays(AIRPORT *a, int n);

    void setFlightsIds(AIRPORT *a);

    void setDelaysList(AIRPORT *a);

    void setYearsList(AIRPORT *a);

    void setType(AIRPORT *a, int n);

    void setYearPassId(YEARPASS *y, int token);

    void setYearPassengers(YEARPASS *y, int n);

    void accNrFlights(AIRPORT *a);

    void accNrDelays(AIRPORT *a);

    void addFlightToList(AIRPORT *a, FLIGHT *f);

    void addDelayToList(AIRPORT *a, int n);

    void addYearToList(AIRPORT *a, YEARPASS *y);

    //gets

    const char *getAirportId(AIRPORT *a);

    int getNumberFlights(AIRPORT *a);

    int getNumberDelays(AIRPORT *a);

    int getType(AIRPORT *a);

    GSList *getFlightsIds(AIRPORT *a);

    GSList *getDelaysList(AIRPORT *a);

    GSList *getYearsList(AIRPORT *a);

    int getYearPassId(YEARPASS *y);

    int getYearPassengers(YEARPASS *y);

    void addYearPassengers(YEARPASS *y, int n);

#endif
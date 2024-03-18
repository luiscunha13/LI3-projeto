#include"../include/flight.h"
#include"../include/airport.h"

#ifndef FLIGHTS_H
#define FLIGHTS_H

    typedef struct data_flights DATA_FLIGHTS;

    DATA_FLIGHTS *read_flightsfile(const char* file_path, DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys);

    void delete_data_flights(DATA_FLIGHTS *df);

    void add_passengers(DATA_FLIGHTS *df, char *flight_id, int pass);

    //gets

    GHashTable *getFlightsTable(DATA_FLIGHTS *df);

    GHashTable *getAirportsTable(DATA_FLIGHTS *df);

#endif
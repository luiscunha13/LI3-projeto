#include"../include/flights.h"
#include"../include/reservations.h"
#include"../include/users.h"
#include"../include/passengers.h"
#include"../include/dayinfo.h"

#ifndef CATALOG_H
#define CATALOG_H

    typedef struct catalog CATALOG;

    void delete_Catalog(CATALOG *c);

    CATALOG *create_catalog();

    //sets

    void setDataFlights(CATALOG *c, char *input, DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys);

    void setDataUsers(CATALOG *c, char *input, YEARS *ys);

    void setDataReservations(CATALOG *c, char *input, DATA_USERS *du, YEARS *ys);

    void setDataPassengers(CATALOG *c, char *input, DATA_USERS *du);

    void setYears(CATALOG *c);

    //gets

    DATA_FLIGHTS *getDataFlights(CATALOG *c);

    DATA_USERS *getDataUsers(CATALOG *c);

    DATA_RESERVATIONS *getDataReservations(CATALOG *c);

    DATA_PASSENGERS *getDataPassengers(CATALOG *c);

    YEARS *getYears(CATALOG *c);

#endif
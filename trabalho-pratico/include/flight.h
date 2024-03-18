#include"../include/users.h"
#include"../include/passengers.h"
#include"../include/dayinfo.h"
#include"../include/date.h"


#ifndef FLIGHT_H
#define FLIGHT_H

    typedef struct flight FLIGHT;

    void delete_Flight(FLIGHT *f);

    FLIGHT *create_Flight(char *line, DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys);

    //sets

    void setPassegers(FLIGHT *f, int n);

    int setDelay(FLIGHT *f);

    //gets

    int getFlightId(FLIGHT *f);

    const char *getAirline(FLIGHT *f);

    const char *getPlaneModel(FLIGHT *f);

    const char *getOrigin(FLIGHT *f);

    const char *getDestination(FLIGHT *f);

    DATE *getSDDate(FLIGHT *f);

    DATE *getSADate(FLIGHT *f);

    DATE *getRDDate(FLIGHT *f);

    DATE *getRADate(FLIGHT *f);

    const char *getSDDateString(FLIGHT *f);

    int getPassengers(FLIGHT *f);

    
#endif
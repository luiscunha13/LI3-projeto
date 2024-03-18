#include"../include/func.h"
#include"../include/dayinfo.h"
#include"../include/date.h"

#ifndef USER_H
#define USER_H

    typedef struct user USER;

    void delete_User(USER *u);

    USER *create_User(char *line, YEARS *ys);

    //sets

    void addFlight(USER *u, int token);

    void addReservation(USER *u, int token);

    void accUserNrFlights(USER *u);

    void accNrReservations(USER *u);

    void addTotalSpent(USER *u, double n);

    int setIdade(USER *u);

    void setNumberofflights(USER *u,int x);

    void setFlightsList(USER *u, char *flight);

    //gets

    const char *getUserId(USER *u);

    int getAccStatus(USER *u);

    const char *getName(USER *u);

    const char getSex(USER *u);
    
    const char *getCode(USER *u);

    const char *getPassport(USER *u);

    int getNumberofreservations(USER *u);

    int getNumberofflights(USER *u);

    double getTotalspent(USER *u);

    GSList *getReservationsList(USER *u);

    GSList *getFlightsList(USER *u);
    

#endif
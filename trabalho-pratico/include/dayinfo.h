#include"../include/func.h"
#include"../include/date.h"

#ifndef DAYINFO_H
#define DAYINFO_H

    typedef struct dayinfo DAYINFO;

    typedef struct monthinfo MONTHINFO;

    typedef struct yearinfo YEARINFO;
    
    typedef struct years YEARS;

    void delete_Years(YEARS *ys);

    void initializeDay(DAYINFO *d);

    void initializeMonth(MONTHINFO *d);

    void initializeYear(YEARINFO *d);

    YEARS *initializeYears();

    void findDay(YEARS *ys, DATE *d, int i, int n, GSList *pass);

    void accNrUsers(YEARINFO *y, MONTHINFO *m, DAYINFO *d);

    void accNrFligh(YEARINFO *y, MONTHINFO *m, DAYINFO *d);

    void accNrReserv(YEARINFO *y, MONTHINFO *m, DAYINFO *d);

    void addNrPassengers(YEARINFO *y, MONTHINFO *m, DAYINFO *d, int n);

    void addPassengers(YEARS *ys, DATE *date, GSList *passengers);

    YEARINFO *getYearInfo(YEARS *ys, int year);

    MONTHINFO *getMonthInfo(YEARS *ys, int year, int month);

    DAYINFO *getDayInfo(YEARS *ys, int year, int month, int day);

    //gets day

    int getNrUsersDay(DAYINFO *d);

    int getNrFlightsDay(DAYINFO *d);

    int getNrPassengersDay(DAYINFO *d);

    int getNrUniquePassengersDay(DAYINFO *d);

    int getNrReservationsDay(DAYINFO *d);

    int getinitializedDay(DAYINFO *d);

    //gets month

    int getNrUsersMonth(MONTHINFO *m);

    int getNrFlightsMonth(MONTHINFO *m);
    
    int getNrPassengersMonth(MONTHINFO *m);

    int getNrUniquePassengersMonth(MONTHINFO *m);

    int getNrReservationsMonth(MONTHINFO *m);
    
    int getinitializedMonth(MONTHINFO *m);
    
    //gets year

    int getNrUsersYear(YEARINFO *y);

    int getNrFlightsYear(YEARINFO *y);

    int getNrPassengersYear(YEARINFO *y);

    int getNrUniquePassengersYear(YEARINFO *y);

    int getNrReservationsYear(YEARINFO *y);

    int getinitializedYear(YEARINFO *y);


#endif
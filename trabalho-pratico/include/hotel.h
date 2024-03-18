#include<glib.h>

#include"../include/reservation.h"

#ifndef HOTEL_H
#define HOTEL_H

    typedef struct hotel HOTEL;

    HOTEL *newHotel();

    void delete_Hotel(HOTEL *h);

    //sets

    void setHotelId(HOTEL *h, int n);

    void setNumberReservations(HOTEL *h, int n);

    void accNumberReservations(HOTEL *h);

    void setReservationsIds(HOTEL *h);

    //gets

    int getHotelId(HOTEL *h);

    int getNumberReservations(HOTEL *h);

    GSList *getReservationsIds(HOTEL *h);

    void addReservationsList(HOTEL *h, RESERVATION *r);


#endif
#include"../include/users.h"
#include"../include/func.h"
#include"../include/dayinfo.h"
#include"../include/date.h"

#ifndef RESERVATION_H
#define RESERVATION_H

    typedef struct reservation RESERVATION;

    void delete_Reservation(RESERVATION *r);

    RESERVATION *create_Reservation(char *line, DATA_USERS *du, YEARS *ys);

    //sets

    double setPrice(RESERVATION *r);

    int setNights(RESERVATION *r);

    //gets

    int getReservationId(RESERVATION *r);

    const char *getResUserId(RESERVATION *r);

    int getResHotelId(RESERVATION *r);

    const char *getResHotelName(RESERVATION *r);

    int getStars(RESERVATION *r);

    DATE *getBDate(RESERVATION *r);

    DATE *getEDate(RESERVATION *r);

    int getIncludesBreakfast(RESERVATION *r);

    const char *getBreakfast(RESERVATION *r);

    int getRating(RESERVATION *r);

    int getPricepn(RESERVATION *r);

    int getTax(RESERVATION *r);


#endif
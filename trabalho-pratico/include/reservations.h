#include"../include/users.h"
#include"../include/reservation.h"
#include"../include/hotel.h"

#ifndef RESERVATIONS_H
#define RESERVATIONS_H

    typedef struct data_reservations DATA_RESERVATIONS;

    DATA_RESERVATIONS *read_reservationsfile (const char* file_path, DATA_USERS *du, YEARS *ys);

    void delete_data_reservations(DATA_RESERVATIONS *dr);

    //gets

    GHashTable *getReservationsTable(DATA_RESERVATIONS *dr);

    GHashTable *getHotelsTable(DATA_RESERVATIONS *dr);
    

#endif
#include"../include/users.h"
#include"../include/func.h"

#ifndef SEAT_H
#define SEAT_H

    typedef struct seats SEATS;

    void delete_seats(SEATS *s);

    SEATS *create_seats(char *line, DATA_USERS *du);

    //sets

    void set_valido(SEATS *s, int val);

    void increaseNrSeats(SEATS *s);

    void addPassList(SEATS *s, char *token);

    //gets

    int get_flid(SEATS *s);

    GSList *get_passList(SEATS *s);

    int get_nrpass(SEATS *s);

    int get_valido(SEATS *s);

    

#endif
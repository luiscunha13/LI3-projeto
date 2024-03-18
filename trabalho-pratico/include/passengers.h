#include"../include/users.h"
#include"../include/seat.h"

#ifndef PASSENGERS_H
#define PASSENGERS_H

    typedef struct data_passengers DATA_PASSENGERS;

    DATA_PASSENGERS *read_passengersfile(const char * file_path, DATA_USERS *du);

    void delete_data_passengers(DATA_PASSENGERS *dp);

    void erase_passengers(DATA_PASSENGERS *dp);

    void add_flightinfo(DATA_PASSENGERS *dp,DATA_USERS *du, int fid);

    GHashTable *getPassengersTable(DATA_PASSENGERS *dp);

    int exist_in_pass_table(DATA_PASSENGERS *dp, char* fl_id);


#endif
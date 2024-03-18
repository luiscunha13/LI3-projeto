#include"../include/user.h"

#ifndef USERS_H
#define USERS_H

    
    typedef struct data_users DATA_USERS;

    DATA_USERS *read_usersfile (const char* file_path, YEARS *ys);

    void delete_data_users(DATA_USERS *du);

    void add_reservation(DATA_USERS *du, const char *user_id, double price, int resid);

    void add_flight(DATA_USERS *du, const char *user_id, int fid);

    int exist_in_hashtable(DATA_USERS *du, char* us_id);

    GHashTable *getUsersTable(DATA_USERS *du);

    GSList *getUserIdsList(DATA_USERS *du);

    int accStat(DATA_USERS *du, const char *usid);

#endif
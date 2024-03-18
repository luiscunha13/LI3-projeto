#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/catalog.h"

//estrutura principal do programa - guarda dados relativos ao input inicial dos ficheiros csv
struct catalog {
    DATA_FLIGHTS *df;
    DATA_RESERVATIONS *dr;
    DATA_USERS *du;
    DATA_PASSENGERS *dp;
    YEARS *ys;
};

// delete da struct
void delete_Catalog(CATALOG *c) {
    delete_data_users(c->du);
    delete_data_reservations(c->dr);
    delete_data_flights(c->df);
    delete_data_passengers(c->dp);
    delete_Years(c->ys);
    free(c);
};

//criação da struct
CATALOG *create_catalog(){
    CATALOG *c =  malloc(sizeof(struct catalog));
    return c;
}

//sets relativos ao CATALOG
void setDataFlights(CATALOG *c, char *input, DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys){
    c->df = read_flightsfile(input, dp, du, ys);  
}

void setDataUsers(CATALOG *c, char *input, YEARS *ys){
    c->du = read_usersfile(input,ys);
}

void setDataReservations(CATALOG *c, char *input, DATA_USERS *du, YEARS *ys){
    c->dr = read_reservationsfile(input, du, ys);
}

void setDataPassengers(CATALOG *c, char *input, DATA_USERS *du){
    c->dp = read_passengersfile(input, du);
}

void setYears(CATALOG *c){
    c->ys = initializeYears();
}

//gets relativos ao CATALOG
DATA_FLIGHTS *getDataFlights(CATALOG *c){
    return(c->df);
}

DATA_USERS *getDataUsers(CATALOG *c){
    return(c->du);
}

DATA_RESERVATIONS *getDataReservations(CATALOG *c){
    return(c->dr);
}

DATA_PASSENGERS *getDataPassengers(CATALOG *c){
    return(c->dp);
}

YEARS *getYears(CATALOG *c){
    return(c->ys);
}
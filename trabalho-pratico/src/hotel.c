#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/hotel.h"

//estrutura que guarda as reservas e o número de reservas de um hotel
struct hotel{
    int hot_id;
    int nr_reservations;
    GSList *res;
};

//criação da struct
HOTEL *newHotel(){
    HOTEL *h = malloc(sizeof (struct hotel));
    return h;
}

//delet da struct
void delete_Hotel(HOTEL *h){
    if(h==NULL) return;
    g_slist_free(h->res);
    free(h);
}

void setHotelId(HOTEL *h, int num){
    h->hot_id = num;
}

//sets de dados na struct
void setNumberReservations(HOTEL *h, int n){
    h->nr_reservations = n;
}

void accNumberReservations(HOTEL *h){
    h->nr_reservations += 1;
}

void setReservationsIds(HOTEL *h){
    h->res = NULL;
}


// gets de dados da struct 
int getHotelId(HOTEL *h){
    return h->hot_id;
}

int getNumberReservations(HOTEL *h){
    return(h->nr_reservations);
}

void addReservationsList(HOTEL *h, RESERVATION *r){
    h->res = g_slist_prepend(h->res, r);
}

GSList *getReservationsIds(HOTEL *h){
    return(h->res);
}


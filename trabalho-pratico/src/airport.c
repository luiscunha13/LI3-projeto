#include<string.h>
#include<glib.h>
#include<ctype.h>

#include "../include/airport.h"

//estrutura que guarda o número de passageiros de um determinado ano
struct yearpass{
    int year_id;
    int nr_passengers;
};


//estrutura relativa aos dados de um determinado aeroporto
struct airport{
    const char *airport_id;
    int nr_flights;
    int nr_passengers;
    int nr_delays;
    GSList *flights;
    GSList *years;
    GSList *delays;
    int type;  // 1-origem, 2-destino
};

//criação de structs
YEARPASS *newYear(){
    YEARPASS *y = malloc(sizeof (struct yearpass));
    return y;
}


AIRPORT *newAirport(){
    AIRPORT *a = malloc(sizeof (struct airport));
    return a;
}

//delete de structs
void delete_YearPass(YEARPASS *y){
    if(y==NULL) return;
    free(y);
}


void delete_Airport(AIRPORT *a){
    if(a==NULL) return;
    g_slist_free(a->flights);
    g_slist_free(a->delays);
    GSList *atual = a->years;
    for(;atual!=NULL;atual=atual->next){
        YEARPASS *y = (YEARPASS*)atual->data;
        delete_YearPass(y);
    }
    g_slist_free(a->years);
    free(a);
}

//sets e gets relativos a aeroporto
void setAirportId(AIRPORT *a, const char *token){
    a->airport_id = token;
}

void setNrFlights(AIRPORT *a, int n){
    a->nr_flights = n;
}

void accNrFlights(AIRPORT *a){
    a->nr_flights += 1;
}

void setNrDelays(AIRPORT *a, int n){
    a->nr_delays = n;
}

void accNrDelays(AIRPORT *a){
    a->nr_delays += 1;
}

void setType(AIRPORT *a, int n){
    a->type = n;
}

void setFlightsIds(AIRPORT *a){
    a->flights = NULL;
}

void setDelaysList(AIRPORT *a){
    a->delays = NULL;
}

void setYearsList(AIRPORT *a){
    a->years = NULL;
}

void addFlightToList(AIRPORT *a, FLIGHT *f){
    a->flights = g_slist_prepend(a->flights, f);
}

void addDelayToList(AIRPORT *a, int n){
    a->delays = g_slist_prepend(a->delays, GINT_TO_POINTER(n));
}

void addYearToList(AIRPORT *a, YEARPASS *y){
    a->years = g_slist_prepend(a->years, y);
}

const char *getAirportId(AIRPORT *a){
    return a->airport_id;
}

int getNumberFlights(AIRPORT *a){
    return(a->nr_flights);
}

int getNumberDelays(AIRPORT *a){
    return(a->nr_delays);
}

int getType(AIRPORT *a){
    return(a->type);
}

GSList *getFlightsIds(AIRPORT *a){
    return(a->flights);
}

GSList *getDelaysList(AIRPORT *a){
    return(a->delays);
}

GSList *getYearsList(AIRPORT *a){
    return(a->years);
}

void setYearPassId(YEARPASS *y, int token){
    y->year_id = token;
}

void setYearPassengers(YEARPASS *y, int n){
    y->nr_passengers = n;
}

void addYearPassengers(YEARPASS *y, int n){
    y->nr_passengers += n;
}

int getYearPassId(YEARPASS *y){
    return(y->year_id);
}

int getYearPassengers(YEARPASS *y){
    return(y->nr_passengers);
}

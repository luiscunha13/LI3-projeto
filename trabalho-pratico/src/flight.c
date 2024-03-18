#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include<ctype.h>

#include "../include/flight.h"

//estrutura do tipo de dados voo
struct flight{
    int id; 
    char *airline; 
    char *plane_model; 
    char *origin; 
    char *destination;
    DATE *schedule_departure_date; 
    DATE *schedule_arrival_date; 
    DATE *real_departure_date; 
    DATE *real_arrival_date; 
    int passengers; 
    int delay; 
};

//função que apaga um voo
void delete_Flight(FLIGHT *f){
    if(f==NULL) return;
    //free(f->id);
    free(f->airline);
    free(f->plane_model);
    free(f->origin);
    free(f->destination);
    free(f->schedule_departure_date);
    free(f->schedule_arrival_date);
    free(f->real_departure_date);
    free(f->real_arrival_date);
    free(f);
}

//função de validação do tipo de dados voo e de alocação na struct
FLIGHT *create_Flight(char *line, DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys){

    char *copy =strdup(line);
    FLIGHT *f = malloc(sizeof(struct flight));
    char *token;
    int i=0;
    int v=1;

    while ((token = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (token[0] == '\0') v=0;
                f->id = convertFIDtoint(token);
                break;
            case 1:
                if (token[0] == '\0') v=0;
                f->airline = strdup(token);
                break;
            case 2:
                if (token[0] == '\0') v=0;
                f->plane_model = strdup(token);
                break;
            case 3:
                if (token[0] == '\0' ||is_number(token) == 0){
                  v=0;  
                  f->passengers = 0;
                } 
                else {
                    SEATS *s = g_hash_table_lookup(getPassengersTable(dp), GINT_TO_POINTER(f->id)); 
                    if(s != NULL){
                        if(get_nrpass(s) > atoi(token)) v=0;
                        f->passengers = get_nrpass(s);
                    }
                    else f->passengers = 0;      
                }
                break;
            case 4:
                if (strlen(token)!=3) v=0;
                f->origin = convertToUpperCase(strdup(token));
                break;
            case 5:
                if (strlen(token)!=3) v=0;
                f->destination = convertToUpperCase(strdup(token));
                break;
            case 6:
                f->schedule_departure_date = newDate();
                if (verify_Date(token,f->schedule_departure_date)==NULL) v=0;
                break;
            case 7:
                f->schedule_arrival_date = newDate();
                if (verify_Date(token,f->schedule_arrival_date)==NULL) v=0;
                break;
            case 8:
                f->real_departure_date = newDate();
                if (verify_Date(token,f->real_departure_date)==NULL) v=0;
                break;
            case 9:
                f->real_arrival_date = newDate();
                if (verify_Date(token,f->real_arrival_date)==NULL) v=0;
                break;
            case 10:
                if (token[0] == '\0') v=0;
                break;
            case 11:
                if (token[0] == '\0') v=0;
                break;
            case 12:
                break;
        }
    }    

     if(v==1){
        if(compare_dates(f->schedule_departure_date,f->schedule_arrival_date)==-1) v=0;
        if(compare_dates(f->real_departure_date,f->real_arrival_date)==-1) v=0;
    }

    if(v==0){
        copy_To_ErrorsFile("Resultados/flights_errors.csv",copy);
        if(exist_in_pass_table(dp,GINT_TO_POINTER(f->id))){
            SEATS *s = g_hash_table_lookup(getPassengersTable(dp), GINT_TO_POINTER(f->id));
            set_valido(s,0);
        }
        free(copy);
        delete_Flight(f);
        return NULL;
    }

    SEATS *s = g_hash_table_lookup(getPassengersTable(dp), GINT_TO_POINTER(f->id));
    findDay(ys,f->schedule_departure_date,2,f->passengers, get_passList(s));

    add_flightinfo(dp,du,f->id);

    free(copy);
    return f;
}

//gets e sets relativos a um voo
void setPassegers(FLIGHT *f, int n){
    f->passengers = n;
}

int setDelay(FLIGHT *f){
    return(difference_dates(f->schedule_departure_date,f->real_departure_date));
}

int getFlightId(FLIGHT *f){
    return(f->id);
}

const char *getAirline(FLIGHT *f){
    return(f->airline);
}

const char *getPlaneModel(FLIGHT *f){
    return(f->plane_model);
}

const char *getOrigin(FLIGHT *f){
    return(f->origin);
}

const char *getDestination(FLIGHT *f){
    return(f->destination);
}

DATE *getSDDate(FLIGHT *f){
    return(f->schedule_departure_date);
}

DATE *getRDDate(FLIGHT *f){
    return(f->real_departure_date);
}

DATE *getRADate(FLIGHT *f){
    return(f->real_arrival_date);
}

DATE *getSADate(FLIGHT *f){
    return(f->schedule_arrival_date);
}

const char *getSDDateString(FLIGHT *f){
    return(datetostring(f->schedule_departure_date,1));
}

int getPassengers(FLIGHT *f){
    return(f->passengers);
}

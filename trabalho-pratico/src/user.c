#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/user.h"


#define DATA_SISTEMA "2023/10/01"

//estrutura do tipo de dados "user"
struct user{
    char *id; 
    char *name;
    DATE *birth_date;
    char sex; 
    char *passport; 
    char *country_code; 
    DATE *account_creation;
    int account_status; 
    int number_of_flights; 
    int number_of_reservations;
    double total_spent; 
    GSList *reservationsList;
    GSList *flightsList;
};

//função que apaga uma struct user
void delete_User(USER *u){
    if(u==NULL) return;
    free(u->id);
    free(u->name);
    free(u->birth_date);
    free(u->passport);
    free(u->country_code);
    free(u->account_creation);
    if(u->reservationsList != NULL) g_slist_free(u->reservationsList);
    if(u->flightsList != NULL) g_slist_free(u->flightsList);
    free(u);
}

//função de validação do tipo de dados "user"
USER *create_User(char *line, YEARS *ys){

    char *copy=strdup(line);
    USER *u = malloc(sizeof(struct user));
    char *token;
    int i=0;
    int v=1;
    
    while((token = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (token[0] == '\0') v=0;
                u->id = strdup(token);
                break;
            case 1:
                if (token[0] == '\0') v=0;
                u->name = strdup(token);
                break;
            case 2:
                if (verify_Email(token)==0) v=0; 
                break;
            case 3:
                if (token[0] == '\0') v=0;
                break;
            case 4:
                u->birth_date = newDate();
                if (verify_Date(token,u->birth_date)==NULL) v=0;
                break;
            case 5:
                if (*token=='m'||*token=='f'||*token=='M'||*token=='F') u->sex=*token;
                else{
                  v=0;  
                  u->sex=*token; 
                } 
                break;
            case 6:
                if (token[0] == '\0') v = 0;
                u->passport = strdup(token);
                break;
            case 7:
                if (strlen(token)==2) u->country_code = strdup(token);
                else{
                   v=0; 
                   u->country_code = strdup(token);
                } 
                break;
            case 8:
                if (token[0] == '\0') v=0;
                break;
            case 9:
                u->account_creation=newDate();
                if (verify_Date(token,u->account_creation)==NULL) v=0;
                break;
            case 10:
                if (token[0] == '\0') v=0;
                break;
            case 11:
                if (verify_Status(token)==0){
                   v=0; 
                   u->account_status = 2;
                } 
                if (verify_Status(token)==1) u->account_status = 0;
                if (verify_Status(token)==2) u->account_status = 1;
                break;
        }    
    }

    u->reservationsList = NULL;
    u->flightsList = NULL;

    if (v==0){
        copy_To_ErrorsFile("Resultados/users_errors.csv",copy);
        free(copy);
        delete_User(u);
        return NULL;
    }

    findDay(ys, u->account_creation,1,0,NULL);
    
    u->number_of_flights=0;
    u->number_of_reservations=0;
    u->total_spent=0.000;  

    free(copy);
    return u;
}

//funções de gets e sets relativas a um user
void addFlight(USER *u, int token){
    u->flightsList = g_slist_prepend(u->flightsList,GINT_TO_POINTER(token));
}

void addReservation(USER *u, int token){
    u->reservationsList = g_slist_prepend(u->reservationsList,GINT_TO_POINTER(token));
}

void accUserNrFlights(USER *u){
    u->number_of_flights +=1;
}

void accNrReservations(USER *u){
    u->number_of_reservations +=1;
}

void addTotalSpent(USER *u, double n){
    u->total_spent += n;
}

const char *getUserId(USER *u){
    return(u->id);
}

int getAccStatus(USER *u){
    return(u->account_status);
}

const char *getName(USER *u){
    return(u->name);
}

const char getSex(USER *u){
    return(u->sex);
}

const char *getCode(USER *u){
    return(u->country_code);
}

const char *getPassport(USER *u){
    return(u->passport);
}

int setIdade(USER *u){ 
    int idade = 2023 - getyear(u->birth_date) ;
    if(getmonth(u->birth_date) > 10 || (getmonth(u->birth_date) == 10 && getday(u->birth_date) >1)) idade--;

    return idade;
}

int getNumberofreservations(USER *u){
    return(u->number_of_reservations);
}

int getNumberofflights(USER *u){
    return(u->number_of_flights);
}

double getTotalspent(USER *u){
    return(u->total_spent);
}

GSList *getReservationsList(USER *u){
    return(u->reservationsList);
}

GSList *getFlightsList(USER *u){
    return(u->flightsList);
}

const char *getAccDate(USER *u){
    return(datetostring(u->account_creation,1));
}

void setNumberofflights(USER *u,int x){
    u->number_of_flights += x;
}

void setFlightsList(USER *u, char *flight){
    u->flightsList = g_slist_prepend(u->flightsList,flight);
}


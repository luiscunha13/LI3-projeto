#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include<ctype.h>

#include"../include/reservation.h"

//estrutura do tipo de dados reserva
struct reservation{
    int id; 
    char *user_id; 
    int hotel_id; 
    char *hotel_name;
    int hotel_stars; 
    int city_tax; 
    DATE *begin_date;
    DATE *end_date; 
    int price_per_night;
    int includes_breakfast;
    int rating; 
};

//função de delete de uma reserva
void delete_Reservation(RESERVATION *r){
    if(r==NULL) return;
    //free(r->id);
    free(r->user_id);
    //free(r->hotel_id);
    free(r->hotel_name);
    free(r->begin_date);
    free(r->end_date);
    free(r);
}

//função de validação do tipo de dados reserva
RESERVATION *create_Reservation(char *line, DATA_USERS *du, YEARS *ys){

    char *copy = strdup(line);
    RESERVATION *r = malloc(sizeof(struct reservation));
    char *token;
    int i=0;
    int v=1;

    while((token = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (token[0] == '\0') v=0;
                r->id=convertRIDtoint(token);
                break;
            case 1:
                if (token[0] == '\0') v=0;
                r->user_id=strdup(token);
                if(exist_in_hashtable(du,r->user_id) == 0) v=0;
                break;
            case 2:
                if (token[0] == '\0') v=0;
                r->hotel_id=convertHIDtoint(token);
                break;
            case 3:
                if (token[0] == '\0') v=0;
                r->hotel_name=strdup(token);
                break;
            case 4:
                if (token[0] != '\0'){
                    for(int y=0;y<strlen(token);y++){
                        if(!isdigit(token[y])) v=0;
                    }
                    if (atoi(token)<1||atoi(token)>5) v=0;
                    r->hotel_stars=atoi(token);
                }
                else v=0;
                break;
            case 5:
                if (token[0] != '\0'){
                    for(int y=0;y<strlen(token);y++){
                        if(!isdigit(token[y])) v=0;
                    }
                    if (atoi(token)<0) v=0;
                    r->city_tax=atoi(token);
                }
                else v=0;
                break;
            case 6:
                if (token[0] == '\0') v=0;
                break;
            case 7:
                r->begin_date = newDate();
                if (verify_Date(token,r->begin_date)==NULL) v=0;
                break;
            case 8:
                r->end_date=newDate();
                if (verify_Date(token,r->end_date)==NULL) v=0;
                break;
            case 9:
                if (token[0] != '\0'){
                    for(int y=0;y<strlen(token);y++){
                        if(!isdigit(token[y])) v=0;
                    }
                    if(atoi(token)<=0) v=0;
                    r->price_per_night=atoi(token);
                }
                else v=0;
                break;
            case 10:
                r->includes_breakfast = verify_Breakfast(token);
                if(r->includes_breakfast==2) v=0;
                break;
            case 11:
                break;
            case 12:
                if (token[0] != '\0'){
                    for(int y=0;y<strlen(token);y++){
                        if(!isdigit(token[y])) v=0;
                    }
                    if (atoi(token)<1||atoi(token)>5) v=0;
                    r->rating=atoi(token);
                }
                else{
                    r->rating=-1;
                }
                break;
            case 13:
                break;
        }
    }

    if(v==1){
        if(compare_dates(r->begin_date,r->end_date)==-1) v=0;
    }

    if(v==0){
        copy_To_ErrorsFile("Resultados/reservations_errors.csv",copy);
        free(copy);
        delete_Reservation(r);
        return NULL;
    }

    findDay(ys, r->begin_date,3,0,NULL);

    add_reservation(du, getResUserId(r), setPrice(r), getReservationId(r));

    free(copy);
    return r;
}

//gets e sets relativas a uma reserva
int setNights(RESERVATION *r){
    return(getday(r->end_date) - getday(r->begin_date));
}

double setPrice(RESERVATION *r){
    return(((r->price_per_night)*(setNights(r))) + (((r->price_per_night)*(setNights(r))*(r->city_tax)*0.01)));
}

int getReservationId(RESERVATION *r){
    return(r->id);
}

const char *getResUserId(RESERVATION *r){
    return(r->user_id);
}

int getResHotelId(RESERVATION *r){
    return(r->hotel_id);
}

const char *getResHotelName(RESERVATION *r){
    return(r->hotel_name);
}

int getStars(RESERVATION *r){
    return(r->hotel_stars);
}

DATE *getBDate(RESERVATION *r){
    return(r->begin_date);
}

DATE *getEDate(RESERVATION *r){
    return(r->end_date);
}

int getIncludesBreakfast(RESERVATION *r){
    return r->includes_breakfast;
}

const char *getBreakfast(RESERVATION *r){
    if((r->includes_breakfast)==1) return("True");
    else return("False");
}

int getRating(RESERVATION *r){
    if(r == NULL) return -1;
    else return(r->rating);
}

int getPricepn(RESERVATION *r){
    return(r->price_per_night);
}

int getTax(RESERVATION *r){
    return(r->city_tax);
}

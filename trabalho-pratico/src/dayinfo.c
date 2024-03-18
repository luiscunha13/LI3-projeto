#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/dayinfo.h"

//estrutura que guarda informações gerais relativas a um dia
struct dayinfo {
    int nr_users;
    int nr_flights;
    int nr_passengers;
    int nr_uniquepassengers;
    int nr_reservations;
    GHashTable *daypass_table;
    int initialized;
};

//estrutura que guarda informações gerais relativas a um mês
struct monthinfo{
    int nr_users;
    int nr_flights;
    int nr_passengers;
    int nr_uniquepassengers;
    int nr_reservations;
    GHashTable *monthpass_table;
    int initialized;
    struct dayinfo day_list[31];
};

//estrutura que guarda informações gerais relativas a um ano
struct yearinfo{
    int nr_users;
    int nr_flights;
    int nr_passengers;
    int nr_uniquepassengers;
    int nr_reservations;
    int initialized;
    GHashTable *yearpass_table;
    struct monthinfo month_list[12];
};

//estrutura onde ficam guardadas até 24 anos de informações gerais relativas ao programa
struct years{
    struct yearinfo year_list[24];
};

//delete da estrutura inteira
void delete_Years(YEARS *ys){
    for(int i=0;i<24;i++){
        YEARINFO *y = &ys->year_list[i];
        
        if(y->yearpass_table != NULL)g_hash_table_destroy(y->yearpass_table);
        for(int j=0;j<12;j++){
            MONTHINFO *m = &ys->year_list[i].month_list[j];
            
            if(m->monthpass_table != NULL)g_hash_table_destroy(m->monthpass_table);
            for(int k=0;k<31;k++){
                DAYINFO *d = &ys->year_list[i].month_list[j].day_list[k];

                if(d->daypass_table != NULL)g_hash_table_destroy(d->daypass_table);  
            }  
        }   
    }
    free(ys);
}

//initcialização das diferentes structs
void initializeDay(DAYINFO *d){
    
    d->nr_users=0;
    d->nr_flights=0;
    d->nr_passengers=0;
    d->nr_uniquepassengers=0;
    d->nr_reservations=0;
    d->daypass_table = g_hash_table_new(g_str_hash, g_str_equal);
    d->initialized=0;

}


void initializeMonth(MONTHINFO *d){
    
    d->nr_users=0;
    d->nr_flights=0;
    d->nr_passengers=0;
    d->nr_uniquepassengers=0;
    d->nr_reservations=0;
    d->monthpass_table = g_hash_table_new(g_str_hash, g_str_equal);
    d->initialized=0;

}


void initializeYear(YEARINFO *d){
    
    d->nr_users=0;
    d->nr_flights=0;
    d->nr_passengers=0;
    d->nr_uniquepassengers=0;
    d->nr_reservations=0;
    d->yearpass_table = g_hash_table_new(g_str_hash, g_str_equal);
    d->initialized=0;

}


YEARS *initializeYears(){
    YEARS *ys = malloc(sizeof(struct years));

    for (int i = 0; i < 24; ++i) {
        initializeYear(&ys->year_list[i]);
        for (int j = 0; j < 12; ++j) {
            initializeMonth(&ys->year_list[i].month_list[j]);
            for (int k = 0; k < 31; ++k) {
                initializeDay(&ys->year_list[i].month_list[j].day_list[k]);
            }
        }
    }

    return ys;
}

//encontra o dia onde se deve atualizar a informação
void findDay(YEARS *ys, DATE *date, int i, int n, GSList *pass){
    YEARINFO *y = &ys->year_list[getyear(date)-2000];
    MONTHINFO *m = &ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1];
    DAYINFO *d = &ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1].day_list[getday(date)-1];
    if(y->initialized == 0) y->initialized = 1;
    if(m->initialized == 0) m->initialized = 1;
    if(d->initialized == 0) d->initialized = 1;
    if(i==1){
        accNrUsers(y,m,d);
    }
    if(i==2){
        accNrFligh(y,m,d);
        addNrPassengers(y,m,d,n);
        addPassengers(ys,date,pass);
    }
    if(i==3){
        accNrReserv(y,m,d);
    }
}

//funções de atualização de dados
void accNrUsers(YEARINFO *y, MONTHINFO *m, DAYINFO *d){
    y->nr_users+=1;
    m->nr_users+=1;
    d->nr_users+=1;
}


void accNrFligh(YEARINFO *y, MONTHINFO *m, DAYINFO *d){
    y->nr_flights+=1;
    m->nr_flights+=1;
    d->nr_flights+=1;
}


void accNrReserv(YEARINFO *y, MONTHINFO *m, DAYINFO *d){
    y->nr_reservations+=1;
    m->nr_reservations+=1;
    d->nr_reservations+=1;
}


void addNrPassengers(YEARINFO *y, MONTHINFO *m, DAYINFO *d, int n){
    y->nr_passengers+=n;
    m->nr_passengers+=n;
    d->nr_passengers+=n;
}


void addPassengers(YEARS *ys, DATE *date, GSList *passengers){
    GHashTable *yt = ys->year_list[getyear(date)-2000].yearpass_table;
    GHashTable *mt = ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1].monthpass_table;
    GHashTable *dt = ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1].day_list[getday(date)-1].daypass_table;

    GSList *atual = passengers;
 
    for(;atual!=NULL;atual=atual->next){
        
        char *pass = (char*)atual->data;
        char *id1 = g_hash_table_lookup(yt,pass);
        if(id1==NULL){
            g_hash_table_insert(yt, pass, pass);
            YEARINFO *y = &ys->year_list[getyear(date)-2000];
            y->nr_uniquepassengers+=1;
        }
        char *id2 = g_hash_table_lookup(mt,pass);
        if(id2==NULL){
            g_hash_table_insert(mt, pass, pass);
            MONTHINFO *m = &ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1];
            m->nr_uniquepassengers+=1;
        }
        char *id3 = g_hash_table_lookup(dt,pass);
        if(id3==NULL){
            g_hash_table_insert(dt, pass, pass);
            DAYINFO *d = &ys->year_list[getyear(date)-2000].month_list[getmonth(date)-1].day_list[getday(date)-1];
            d->nr_uniquepassengers+=1;
        }
    }
}

// gets de structs
YEARINFO *getYearInfo(YEARS *ys, int year){   
    YEARINFO *y = &ys->year_list[year-2000];

    return y;
}


MONTHINFO *getMonthInfo(YEARS *ys, int year, int month){   
    MONTHINFO *m = &ys->year_list[year-2000].month_list[month-1];

    return m;
}


DAYINFO *getDayInfo(YEARS *ys, int year, int month, int day){   
    DAYINFO *d = &ys->year_list[year-2000].month_list[month-1].day_list[day-1];

    return d;
}

//gets relativos às informações divididas por dia/mês/ano
int getNrUsersDay(DAYINFO *d){
    return(d->nr_users);
}

int getNrFlightsDay(DAYINFO *d){
    return(d->nr_flights);
}

int getNrPassengersDay(DAYINFO *d){
    return(d->nr_passengers);
}

int getNrUniquePassengersDay(DAYINFO *d){
    return(d->nr_uniquepassengers);
}

int getNrReservationsDay(DAYINFO *d){
    return(d->nr_reservations);
}

int getinitializedDay(DAYINFO *d){
    return(d->initialized);
}

int getNrUsersMonth(MONTHINFO *m){
    return(m->nr_users);
}

int getNrFlightsMonth(MONTHINFO *m){
    return(m->nr_flights);
}

int getNrPassengersMonth(MONTHINFO *m){
    return(m->nr_passengers);
}

int getNrUniquePassengersMonth(MONTHINFO *m){
    return(m->nr_uniquepassengers);
}

int getNrReservationsMonth(MONTHINFO *m){
    return(m->nr_reservations);
}

int getinitializedMonth(MONTHINFO *m){
    return(m->initialized);
}

int getNrUsersYear(YEARINFO *y){
    return(y->nr_users);
}

int getNrFlightsYear(YEARINFO *y){
    return(y->nr_flights);
}

int getNrPassengersYear(YEARINFO *y){
    return(y->nr_passengers);
}

int getNrUniquePassengersYear(YEARINFO *y){
    return(y->nr_uniquepassengers);
}

int getNrReservationsYear(YEARINFO *y){
    return(y->nr_reservations);
}

int getinitializedYear(YEARINFO *y){
    return(y->initialized);
}

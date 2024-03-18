#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/queries.h"


void query10(char *out_path, int year, int month, int type, CATALOG *c, int f){
    FILE *result;
    result = fopen(out_path, "w");
    YEARS *ys = getYears(c);
    int aux=0;

    if(type==2){  //year e month

        char **answer = malloc(31 * sizeof(char*));
        
        for(int i=0;i<31;i++){
            
            DAYINFO *d = getDayInfo(ys,year,month,i+1);
            if(getinitializedDay(d) == 1){

                if(asprintf(&answer[aux], "%d;%d;%d;%d;%d;%d", i+1,getNrUsersDay(d),
                getNrFlightsDay(d),getNrPassengersDay(d),getNrUniquePassengersDay(d),
                getNrReservationsDay(d))==0) return;
                
                aux++;
                
            }
        }

        if(aux==0){
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        if(f==0) printline(out_path, answer, 1,10,1,aux);
        else if(f==1) printline(out_path, answer, 2,10,1,aux);
        else printline(out_path, answer, 3,10,1,aux);

    }

    else if(type==1){ //meses do ano

        char **answer = malloc(12 * sizeof(char*));
        
        for(int i=0;i<12;i++){

            MONTHINFO *m = getMonthInfo(ys,year,i+1);
            if(getinitializedMonth(m) == 1){

                if(asprintf(&answer[aux], "%d;%d;%d;%d;%d;%d", i+1,getNrUsersMonth(m),
                getNrFlightsMonth(m),getNrPassengersMonth(m),getNrUniquePassengersMonth(m),
                getNrReservationsMonth(m))==0) return;
                
                aux++;

            }  
        }

        if(aux==0){
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        if(f==0) printline(out_path, answer, 1,10,2,aux);
        else if(f==1) printline(out_path, answer, 2,10,2,aux);
        else printline(out_path, answer, 3,10,2,aux);
    }

    else{ //anos

        char **answer = malloc(24 * sizeof(char*));

        for(int i=0;i<24;i++){

            YEARINFO *y = getYearInfo(ys,2000+i);
            if(getinitializedYear(y) == 1){
               

                if(asprintf(&answer[aux], "%d;%d;%d;%d;%d;%d", i+2000,getNrUsersYear(y),
                getNrFlightsYear(y),getNrPassengersYear(y),getNrUniquePassengersYear(y),
                getNrReservationsYear(y))==0) return;
                
                aux++;
                
                
            }  
        }

        if(aux==0){
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        if(f==0) printline(out_path, answer, 1,10,3,aux);
        else if(f==1) printline(out_path, answer, 2,10,3,aux);
        else printline(out_path, answer, 3,10,3,aux);

    }

    fclose(result);
}

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<glib.h>

#include"../include/queries.h"

//verifica se o id é de uma reserva
int isreservation(char *id){
    char book[] = "Book";
    int res=1;

    for(int i=0;i<4;i++){
        if(id[i] != book[i]){
            res=0;
            break;
        }
    }

    return res;
}

void query1(char *out_path, char *id, CATALOG *c, int f){

    char *answer;

    if (isalpha(id[0]))
    {
        if (isreservation(id) == 0)
        {
            USER *x = g_hash_table_lookup(getUsersTable(getDataUsers(c)), id);
            if (x == NULL){
                if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
                else printline(out_path, NULL, 1,-1,-1,-1);
                return;
            }
            else if(getAccStatus(x) == 1){
                if(asprintf(&answer,"%s;%c;%d;%s;%s;%d;%d;%.3f", getName(x),getSex(x),
                setIdade(x),getCode(x),getPassport(x),getNumberofflights(x),
                getNumberofreservations(x),getTotalspent(x))==0) return;

                if(f==0) printline(out_path, &answer, 1,1,1,1);
                else if(f==1)printline(out_path, &answer, 2,1,1,1);
                else printline(out_path, &answer, 3,1,1,1);
                
                
            }
            else{
                if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
                else printline(out_path, NULL, 1,-1,-1,-1);
                return;
            }
            
        }

        else
        {
            RESERVATION *r = g_hash_table_lookup(getReservationsTable(getDataReservations(c)), GINT_TO_POINTER(convertRIDtoint(id)));
            if (r == NULL){
                if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
                else printline(out_path, NULL, 1,-1,-1,-1);
                return;
            }
            DATE *di = getBDate(r);
            DATE *df = getEDate(r);
            char *string = convertHIDtostring(getResHotelId(r));

            if(asprintf(&answer,"%s;%s;%d;%04d/%02d/%02d;%04d/%02d/%02d;%s;%d;%.3f", 
            string, getResHotelName(r), getStars(r), getyear(di), getmonth(di),
            getday(di), getyear(df), getmonth(df), getday(df), getBreakfast(r), setNights(r), setPrice(r))==0) return;

            free(string);

            if(f==0) printline(out_path, &answer, 1,1,2,1);
            else if(f==1) printline(out_path, &answer, 2,1,2,1);
            else printline(out_path, &answer, 3,1,2,1);
            

        }
    }

    else
    {
        FLIGHT *x = g_hash_table_lookup(getFlightsTable(getDataFlights(c)), GINT_TO_POINTER(convertFIDtoint(id)));
        if (x == NULL){
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }
        DATE *dd = getSDDate(x);
        DATE *da = getSADate(x);

        if(asprintf(&answer, "%s;%s;%s;%s;%04d/%02d/%02d %02d:%02d:%02d;%04d/%02d/%02d %02d:%02d:%02d;%d;%d", 
        getAirline(x),getPlaneModel(x),getOrigin(x),getDestination(x),getyear(dd),
        getmonth(dd),getday(dd),gethour(dd),getminute(dd),getsecond(dd),
        getyear(da),getmonth(da),getday(da),gethour(da),getminute(da),getsecond(da),
        getPassengers(x),setDelay(x))==0) return;
        

        if(f==0) printline(out_path, &answer, 1,1,3,1);
        else if(f==1) printline(out_path, &answer, 2,1,3,1);
        else printline(out_path, &answer, 3,1,3,1);
        
        
    }

    
}
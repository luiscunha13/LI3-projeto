#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>

#include"../include/queries.h"


void query8(char *out_path, char *hotel_id, char *begin_date, char *end_date, CATALOG *c,int f){

    int revenue=0;
    int nights=0;
    int hid = convertHIDtoint(hotel_id);

    DATE *bdate = newDate();
    DATE *edate = newDate();
    if(verify_Date(begin_date, bdate)==NULL) return;
    if(verify_Date(end_date, edate)==NULL) return;
    
    HOTEL *h = g_hash_table_lookup(getHotelsTable(getDataReservations(c)),GINT_TO_POINTER(hid));

   if(h!=NULL){
        GSList *lista = getReservationsIds(h);
        GSList *atual;

        for(atual=lista;atual != NULL; atual=atual->next){
            RESERVATION *r = (RESERVATION*)atual->data;
            if(compare_dates(edate,getEDate(r))==1 && compare_dates(edate,getBDate(r))!=1){   
                if(compare_dates(bdate,getBDate(r))!=-1){
                    nights = (getday(edate) - getday(getBDate(r))) + 1;
                }
                else nights = (getday(edate) - getday(bdate)) + 1;

                revenue += (getPricepn(r)*nights);  
            }
            else if((compare_dates(edate,getEDate(r))!=1) && (compare_dates(bdate,getEDate(r))!=-1)){    
                if(compare_dates(bdate,getBDate(r))!=-1){
                    nights = (getday(getEDate(r)) - getday(getBDate(r)));
                }
                else nights = (getday(getEDate(r)) - getday(bdate));

                revenue += (getPricepn(r)*nights);
            }
        }    
   }
   else{
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
   }

    char *answer;
    if(asprintf(&answer, "%d", revenue)==0) return;

    if(f==0) printline(out_path, &answer, 1,8,1,1);
    else if(f==1) printline(out_path, &answer, 2,8,1,1);
    else printline(out_path, &answer, 3,8,1,1);

    free(bdate);
    free(edate);

}
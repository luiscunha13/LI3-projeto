#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>

#include"../include/queries.h"

void query3(char *out_path, char *hotel_id, CATALOG *c, int f){

    int acum=0;
    double media;
    int hid = convertHIDtoint(hotel_id);

    HOTEL *h = g_hash_table_lookup(getHotelsTable(getDataReservations(c)),GINT_TO_POINTER(hid));

    if(h!=NULL){
        GSList *lista = getReservationsIds(h);
        GSList *atual;

        for(atual=lista;atual != NULL; atual=atual->next){
            RESERVATION *r = (RESERVATION*)atual->data;
            if(r!=NULL){
                acum += getRating(r);
            }
        }
    }
    else{
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }

    if(acum!=0) media=((double)acum/getNumberReservations(h));
    else media=(double)acum;
    
    char *answer;
    if(asprintf(&answer,"%.3f\n", media)==0) return;


    if(f==0) printline(out_path, &answer, 1,3,1,1);
    else if(f==1)printline(out_path, &answer, 2,3,1,1);
    else printline(out_path, &answer, 3,3,1,1);

}


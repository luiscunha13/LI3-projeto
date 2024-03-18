#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/queries.h"

//função usada na ordenação da lista de respostas
int compare4(gconstpointer a, gconstpointer b){
    RESERVATION *reservation1 =(RESERVATION *) a;
    RESERVATION *reservation2 =(RESERVATION *) b;

    DATE *date1 = getBDate(reservation1);
    DATE *date2 = getBDate(reservation2);

    if(compare_dates(date1,date2)==1){
        return 1;
    }
    if(compare_dates(date1,date2)==-1){
        return -1;
    }
    else{
        if(getReservationId(reservation1)<getReservationId(reservation2)){
            return -1;
        }
        else return 1;
    }
}

void query4(char *out_path, char *hotel_id, CATALOG *c, int f){
    
    GSList *resposta = NULL;
    int acc=0;
    int hid = convertHIDtoint(hotel_id);

    HOTEL *h = g_hash_table_lookup(getHotelsTable(getDataReservations(c)),GINT_TO_POINTER(hid));

    if(h!=NULL){
        GSList *lista = getReservationsIds(h);
        GSList *atual;

        for(atual=lista;atual != NULL; atual=atual->next){
            RESERVATION *r = (RESERVATION*)atual->data;
            if(r!=NULL){
                resposta = g_slist_prepend(resposta,r);
                acc++;
            }
        }

    }
    else{
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }

    GSList *atual;
    resposta = g_slist_sort(resposta, compare4);
    char **answer = malloc(acc * sizeof(char*));

    

    int a=0;
    for(atual=resposta; atual != NULL; atual=atual->next){
        RESERVATION *reservation = (RESERVATION *)atual->data;
        DATE *d1 = getBDate(reservation);
        DATE *d2 = getEDate(reservation);

        char *string =  convertRIDtostring(getReservationId(reservation));

        if(asprintf(&answer[a],"%s;%04d/%02d/%02d;%04d/%02d/%02d;%s;%d;%.3f", 
        string, getyear(d1), getmonth(d1), getday(d1), getyear(d2), getmonth(d2),
        getday(d2), getResUserId(reservation), getRating(reservation), setPrice(reservation))==0) return;

        free(string);

        a++;
    }

    if(f==0) printline(out_path,answer,1,4,1,a);
    else if(f==1)printline(out_path,answer,2,4,1,a);
    else printline(out_path,answer,3,4,1,a);
    
    g_slist_free(resposta);

}

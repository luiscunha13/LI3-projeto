 #define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>

#include"../include/queries.h"

//struct que guarda a informação de um voo ou uma reserva e a sua data
typedef struct info{
    int id;
    DATE *date;
    int type;  // 0->flight  1->reservation
}INFO;

//adiciona uma struct à lista
GSList *add_toList3(GSList *resposta, int id, DATE *date, int type){
	
	INFO *i = g_new(INFO, 1);

	i->id = id;
	i->date = date;
	i->type = type;
    resposta = g_slist_prepend(resposta,i);

	return resposta;
}
//função usada para a ordenação da lista
gint compare2(gconstpointer a, gconstpointer b){
	INFO *inf1 =(INFO *) a;
	INFO *inf2 =(INFO *) b;
	//DATE *date1 = inf1->date;
	//DATE *date2 = inf2->date;
    
    if(compare_dates(inf1->date,inf2->date)==1){
        return 1;
    }
    if(compare_dates(inf1->date,inf2->date)==-1){
        return -1;
    }
    else{
        if(inf1->id<inf2->id){
             return -1;
        }
        else return 1;
    }
    
}

void query2(char *out_path, char *id, char *arg, int type, CATALOG *c, int f){

    USER *u = g_hash_table_lookup(getUsersTable(getDataUsers(c)),id);
    int acc=0;
    

    if(type == 0){
        GSList *resposta = NULL;
        GSList* atual;

        if(u != NULL && getAccStatus(u)==1){
            for(atual=getFlightsList(u);atual !=NULL;atual=atual->next){
                char *fl =(char*)atual->data;
                FLIGHT *f = g_hash_table_lookup(getFlightsTable(getDataFlights(c)),fl);
                if(f!=NULL){
                    resposta = add_toList3(resposta, getFlightId(f), getSDDate(f),0);
                    acc++;
                }  
            }
            for(atual=getReservationsList(u);atual !=NULL;atual=atual->next){
                char *rv =(char*)atual->data;
                RESERVATION *r = g_hash_table_lookup(getReservationsTable(getDataReservations(c)),rv);
                if(r!=NULL){
                    resposta = add_toList3(resposta,getReservationId(r), getBDate(r),1);
                    acc++;
                } 
            }
        }
        else{
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        resposta = g_slist_sort(resposta, compare2);
        char **answer = malloc(acc * sizeof(char*));
        
        int a=0;
        for(atual=resposta; atual != NULL; atual=atual->next){
            INFO *i = (INFO *)atual->data;
            DATE *d1 = i->date; 

            if(i->type==0){

                char *string1 = convertFIDtostring(i->id);

                if(asprintf(&answer[a],"%s;%04d/%02d/%02d;flight", string1,
                getyear(d1),getmonth(d1),getday(d1))==0) return;

                free(string1);
            }
            else{

                char *string2 = convertRIDtostring(i->id);

                if(asprintf(&answer[a],"%s;%04d/%02d/%02d;reservation", string2,
                getyear(d1),getmonth(d1),getday(d1))==0) return;

                free(string2);
            }
            
            a++; 
        }

        if(f==0) printline(out_path, answer, 1,2,1,a);
        else if(f==1) printline(out_path, answer, 2,2,1,a);
        else printline(out_path, answer, 3,2,1,a);
        

        if(resposta != NULL) g_slist_free_full(resposta,free);
    
    }

    else if(arg[0] == 'f'){
        GSList *resposta = NULL;
        GSList* atual;

        if(u != NULL && getAccStatus(u)==1){
            for(atual=getFlightsList(u);atual !=NULL;atual=atual->next){
                char *fl =(char*)atual->data;
                FLIGHT *f = g_hash_table_lookup(getFlightsTable(getDataFlights(c)),fl);
                if(f!=NULL){
                    resposta = add_toList3(resposta,getFlightId(f), getSDDate(f),0);
                    acc++;
                }
            }
            
        }
        else{
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        resposta = g_slist_sort(resposta, compare2);
        char **answer = malloc(acc * sizeof(char*));

        int a=0;
        for(atual=resposta; atual != NULL; atual=atual->next){
            INFO *i = (INFO *)atual->data;
            DATE *d1 = i->date; 

            char *string3 = convertFIDtostring(i->id);

            if(asprintf(&answer[a],"%s;%04d/%02d/%02d", string3,
            getyear(d1),getmonth(d1),getday(d1))==0) return;

            free(string3);

            a++;
        }

        if(f==0) printline(out_path, answer, 1,2,1,a);
        else if(f==1)printline(out_path, answer, 2,2,1,a);
        else printline(out_path, answer, 3,2,1,a);

        if(resposta != NULL) g_slist_free_full(resposta,free);
    }

    else{
        GSList *resposta = NULL;
        GSList* atual;

        if(u != NULL && getAccStatus(u)==1){
            for(atual=getReservationsList(u);atual !=NULL;atual=atual->next){
                char *rv =(char*)atual->data;
                RESERVATION *r = g_hash_table_lookup(getReservationsTable(getDataReservations(c)),rv);
                if(r!=NULL){
                    resposta = add_toList3(resposta,getReservationId(r), getBDate(r),1);
                    acc++;
                }
            }
        }
        else{
            if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
            else printline(out_path, NULL, 1,-1,-1,-1);
            return;
        }

        resposta = g_slist_sort(resposta, compare2);
        char **answer = malloc(acc * sizeof(char*));

        int a=0;
        for(atual=resposta; atual != NULL; atual=atual->next){
            INFO *i = (INFO *)atual->data;
            DATE *d1 = i->date;
            
            char *string4 = convertRIDtostring(i->id);

            if(asprintf(&answer[a],"%s;%04d/%02d/%02d", string4,
            getyear(d1),getmonth(d1),getday(d1))==0) return;

            free(string4);

            a++;
        }

        if(f==0) printline(out_path, answer, 1,2,1,a);
        else if(f==1) printline(out_path, answer, 2,2,1,a);
        else printline(out_path, answer, 3,2,1,a);

        if(resposta != NULL) g_slist_free_full(resposta,free);

    }
    
}
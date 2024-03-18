#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<glib.h>
#include<ctype.h>

#include"../include/queries.h"

//struct que contem um aeroporto e os seu numero de passageiros
typedef struct{
	const char *airport;
	int passengers;
}PAIR;


//função adiciona uma struct à lista
GSList *add_toList(GSList *resposta, const char *airp, int nrpass){

	PAIR *p1 = g_new(PAIR, 1);
	p1->airport = airp;
	p1->passengers = nrpass;
	resposta = g_slist_prepend(resposta,p1);

	return resposta;
}

//função usada na ordenação da lista de respostas
gint compare_passengers(gconstpointer a, gconstpointer b){
	PAIR *pair1 =(PAIR *) a;
	PAIR *pair2 =(PAIR *) b;
	int pass1 = pair1->passengers;
	int pass2 = pair2->passengers;

	if(pass1>pass2){
		return -1;
	}
	if(pass1<pass2){
		return 1;
	}
	else{
		if(strcmp(pair1->airport,pair2->airport)<0){
			return -1;
		}
		else return 1;
	}

}

void query6(char *out_path,char* year, int N, CATALOG *c, int f){
	int acc=0, yearn= atoi(year);

	GHashTableIter iter;
    gpointer key, value;
	GSList *resposta = NULL;

    g_hash_table_iter_init(&iter, getAirportsTable(getDataFlights(c)));

    while (g_hash_table_iter_next(&iter, &key, &value)){
        AIRPORT *a = (AIRPORT*)value;
		GSList *atual = getYearsList(a);

		for(;atual!=NULL;atual=atual->next){
			YEARPASS *y =(YEARPASS*)atual->data;
			if(getYearPassId(y)==yearn){
				resposta = add_toList(resposta,getAirportId(a),getYearPassengers(y));
				acc++;
				break;
			}
		}
	}

	resposta = g_slist_sort(resposta, compare_passengers);
	int aux=0;
	if(acc >= N) aux = N;
	else aux = acc;

	char **answer = malloc(aux * sizeof(char*));

	if(resposta==NULL){
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }
	

	GSList *atual;

	int i=0;
	for(atual=resposta;atual!=NULL;atual=atual->next){
		if(i<N){
			PAIR *pair = (PAIR *)atual->data;
			const char *ori=pair->airport;
			char oriUp[3];
			for(int g=0;g<strlen(ori);g++){
				oriUp[g]=toupper(ori[g]);
			}

			if(asprintf(&answer[i], "%s;%d",oriUp,pair->passengers) == 0) return;

			i++;

		}
		else break;
	}

	if(f==0) printline(out_path, answer, 1,6,1,i);
	else if(f==1) printline(out_path, answer, 2,6,1,i);
	else printline(out_path, answer, 3,6,1,i);


	if(resposta != NULL) g_slist_free_full(resposta,free);

}


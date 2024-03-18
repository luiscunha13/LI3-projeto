#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<glib.h>

#include"../include/queries.h"

//função que guarda os atrasos dos voos de um aeroporto
typedef struct{
	const char *origin;
    int length_list;
	GSList *delays;
}PAIR;

//função adiciona uma struct à lista
GSList *add_toList2(GSList *resposta, const char *airp, GSList *del, int nrdelays){

	PAIR *p = g_new(PAIR, 1);
	p->origin = airp;
	p->length_list = nrdelays;
    p->delays = g_slist_copy(del);
    resposta = g_slist_prepend(resposta,p);

	return resposta;
}

//função usada na ordenação dos atrasos por ordem crescente
gint compare_delays(gconstpointer a, gconstpointer b){
    int delay1 = GPOINTER_TO_INT(a);
	int delay2 = GPOINTER_TO_INT(b);

    if(delay1<=delay2){
		return -1;
	}
	if(delay1>delay2){
		return 1;
	}
	else return 0;
}

//calcula a mediana de atrasos de um aeroporto
int get_median(PAIR *p){
    int len = p->length_list;
    if(len % 2 == 1){
        int pos=len/2;
        GSList *atual;
        int x=0;
        for (atual = p->delays; atual != NULL; atual = g_slist_next(atual)){
            if (x == pos){
                int value = GPOINTER_TO_INT(atual->data);
                return value;
            }
            x++;
        }
    }
    else{
        int pos=len/2-1;
        GSList *atual;
        int x=0;
        for (atual = p->delays; atual != NULL; atual = g_slist_next(atual)) {
            if (x == pos){
                int value1 = GPOINTER_TO_INT(atual->data);
                int value2 = GPOINTER_TO_INT(atual->next->data);
                return ((value1+value2)/2);
            }
            x++;
        }
    }
    return 0;

}

//função usada na ordenação das medianas
gint compare_medians(gconstpointer a, gconstpointer b){
    PAIR *pair1 =(PAIR *) a;
	PAIR *pair2 =(PAIR *) b;
    int median1 = get_median(pair1);
    int median2 = get_median(pair2);

    if(median1>median2){
		return -1;
	}
	if(median1<median2){
		return 1;
	}
	else{
        if(strcasecmp(pair1->origin,pair2->origin)<0){
			return -1;
		}
		else return 1;
    }
}



void query7(char *out_path, int N, CATALOG *c, int f){
	int acc=0;

	GHashTableIter iter;
    gpointer key, value;
	GSList *resposta = NULL;

    g_hash_table_iter_init(&iter, getAirportsTable(getDataFlights(c)));

    while (g_hash_table_iter_next(&iter, &key, &value)){
        AIRPORT *a = (AIRPORT*)value;
		if(getType(a) == 1){
			resposta = add_toList2(resposta, getAirportId(a), getDelaysList(a), getNumberDelays(a));
			acc++;
		}
	}

    GSList *atual;

    for (atual = resposta; atual != NULL; atual = g_slist_next(atual)){
        PAIR *pair = (PAIR *)atual->data;
        pair->delays = g_slist_sort(pair->delays, compare_delays);
    }

	int aux=0;
	if(acc>=N) aux = N;
	else aux = acc;

	char **answer = malloc(aux * sizeof(char*));

	resposta = g_slist_sort(resposta, compare_medians);

	if(resposta==NULL){
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
    }
	
	int i=0;
	for(atual=resposta;atual!=NULL;atual=atual->next){
		if(i<N){
			PAIR *pair = (PAIR *)atual->data;
			const char *ori=pair->origin;
			char oriUp[3];
			for(int j=0;j<3;j++){
				oriUp[j]=toupper(ori[j]);
			}
			
			if(asprintf(&answer[i], "%s;%d", oriUp,get_median(pair))==0) return;

			i++;

		}
		else break;
	}

	if(f==0) printline(out_path, answer, 1,7,1,i);
	else if(f==1)printline(out_path, answer, 2,7,1,i);
	else printline(out_path, answer, 3,7,1,i);
	

	if(resposta != NULL){
		for(atual=resposta;atual!=NULL;atual=atual->next){
			PAIR *pair = (PAIR *)atual->data;
			g_slist_free(pair->delays);
		}
		
		g_slist_free_full(resposta,free);
	}

}


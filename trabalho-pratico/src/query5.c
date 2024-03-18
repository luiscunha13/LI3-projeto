#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<glib.h>
#include<ctype.h>

#include"../include/queries.h"

//função usada na ordenação da lista de respostas
gint compare5(gconstpointer a, gconstpointer b){
	FLIGHT *flight1 =(FLIGHT *) a;
	FLIGHT *flight2 =(FLIGHT *) b;
	DATE *date1 = getSDDate(flight1);
	DATE *date2 = getSDDate(flight2);

	if(compare_dates(date1,date2)==1){
		return 1;
	}
	if(compare_dates(date1,date2)==-1){
		return -1;
	}
	else{
		if(getFlightId(flight1)<getFlightId(flight2)){
			return -1;
		}
		else return 1;
	}	
}

void query5(char *out_path, char *origin, char *days_bdate, char *hours_bdate, char *days_edate, char *hours_edate, CATALOG *c, int f){

    GSList *resposta = NULL; 
	GSList *atual;
	int acc=0;

    days_bdate=days_bdate+1;     
    hours_bdate[strlen(hours_bdate)-1] = '\0';  
    days_edate=days_edate+1;       
    hours_edate[strlen(hours_edate)-1] = '\0';   

	char *date1 = (char*)malloc(strlen(days_bdate) + strlen(hours_bdate) + 2);
	char *date2 = (char*)malloc(strlen(days_edate) + strlen(hours_edate) + 2);

	strcpy(date1, days_bdate);
	strcat(date1," ");
	strcat(date1, hours_bdate);

	strcpy(date2, days_edate);
	strcat(date2," ");
	strcat(date2, hours_edate);

	DATE *d1 = newDate();
	DATE *d2 = newDate();

	if(verify_Date(date1,d1)==NULL) return;
	if(verify_Date(date2,d2)==NULL) return;
	
	AIRPORT *a = g_hash_table_lookup(getAirportsTable(getDataFlights(c)),origin);

	if(a!=NULL){
		GSList *lista = getFlightsIds(a);
		
		for(atual=lista;atual !=NULL;atual=atual->next){
			FLIGHT *f = (FLIGHT*)atual->data;
			if(f!=NULL){
				if((compare_dates(getSDDate(f),d1) != 1) && (compare_dates(getSDDate(f),d2) != -1)){
					
					resposta = g_slist_prepend(resposta,f);
					acc++;
				}
			} 
		}
	}   
	else{
        if(f==2)printline(out_path, NULL, 2,-1,-1,-1);
        else printline(out_path, NULL, 1,-1,-1,-1);
        return;
	}    

	resposta = g_slist_sort(resposta, compare5);
	char **answer = malloc(acc * sizeof(char*));

	int b=0;
	for(atual=resposta; atual != NULL; atual=atual->next){
		FLIGHT *flight = (FLIGHT *)atual->data;

		const char *dest=getDestination(flight);
		char destUp[3];
		for(int i=0;i<strlen(dest);i++){
			destUp[i]=toupper(dest[i]);
		}

		DATE *dd = getSDDate(flight);
		char *string = convertFIDtostring(getFlightId(flight));

		if(asprintf(&answer[b],"%s;%04d/%02d/%02d %02d:%02d:%02d;%s;%s;%s", 
		string, getyear(dd), getmonth(dd), getday(dd), gethour(dd),getminute(dd),
		getsecond(dd), destUp, getAirline(flight), getPlaneModel(flight))==0) return;

		free(string);

		b++;
	}

	if(f==0) printline(out_path, answer, 1,5,1,b);
	else if(f==1) printline(out_path, answer, 2,5,1,b);
	else printline(out_path, answer, 3,5,1,b);



	free(d1);
	free(d2);
	free(date1);
	free(date2);
	if(resposta != NULL) g_slist_free(resposta);

}








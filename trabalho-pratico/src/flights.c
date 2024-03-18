#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include<ctype.h>

#include "../include/flights.h"

//estrutura que guarda duas hashtables relativas ao tipo de dados voo -> divididas por id de voo e aeroporto de origem
struct data_flights{
    GHashTable *flights_table;
    GHashTable *airports_table;
};

//função que insere um voo na hashtable por id
void insert_flight(DATA_FLIGHTS *df, FLIGHT *f){
    g_hash_table_insert(df->flights_table, GINT_TO_POINTER(getFlightId(f)), f);
}

//função que insere um voo na hashtable por aeroporto de origem
void insert_airport(DATA_FLIGHTS *df, FLIGHT *f){
    AIRPORT *a = g_hash_table_lookup(df->airports_table,getOrigin(f));
    if(a == NULL){
        AIRPORT *a1 = newAirport();
        YEARPASS *y = newYear();
        setAirportId(a1, getOrigin(f));
        setNrFlights(a1,1);
        setFlightsIds(a1);
        setType(a1,1);
        setDelaysList(a1);
        addFlightToList(a1,f);
        addDelayToList(a1,setDelay(f));
        setNrDelays(a1,1);
        setYearPassId(y, getyear(getSDDate(f)));
        setYearsList(a1);
        setYearPassengers(y,getPassengers(f));
        addYearToList(a1,y);
        g_hash_table_insert(df->airports_table, (gpointer)getAirportId(a1), a1);
    }
    else{
        accNrFlights(a);
        addFlightToList(a,f);
        addDelayToList(a,setDelay(f));
        accNrDelays(a);
        if(getType(a) == 0) setType(a,1);
        GSList *atual = getYearsList(a);
        int i=0;
        for(;atual!=NULL;atual= atual->next){
            YEARPASS *y =(YEARPASS*)atual->data;
            int aux = getyear(getSDDate(f));
            if(getYearPassId(y)==aux){
                addYearPassengers(y,getPassengers(f));
                i=1;
                break;
            }
        }
        if(i==0){
            YEARPASS *y3 = newYear();
            setYearPassId(y3, getyear(getSDDate(f)));
            setYearPassengers(y3,getPassengers(f));
            addYearToList(a,y3);
        }
    }
    AIRPORT *a2 = g_hash_table_lookup(df->airports_table,getDestination(f));
    if(a2 == NULL){
        AIRPORT *a3 = newAirport();
        YEARPASS *y1 = newYear();
        setAirportId(a3, getDestination(f));
        setNrFlights(a3,0);
        setFlightsIds(a3);
        setDelaysList(a3);
        setNrDelays(a3,0);
        setType(a3,0);
        setYearPassId(y1, getyear(getSDDate(f)));
        setYearsList(a3);
        setYearPassengers(y1,getPassengers(f));
        addYearToList(a3,y1);
        g_hash_table_insert(df->airports_table, (gpointer)getAirportId(a3), a3);
    }
    else{
        GSList *atual = getYearsList(a2);
        int i=0;
        for(;atual!=NULL;atual= atual->next){
            YEARPASS *y =(YEARPASS*)atual->data;
            int aux = getyear(getSDDate(f));
            if(getYearPassId(y)==aux){
                addYearPassengers(y,getPassengers(f));
                i=1;
                break;
            }
        }
        if(i==0){
            YEARPASS *y4 = newYear();
            setYearPassId(y4, getyear(getSDDate(f)));
            setYearPassengers(y4,getPassengers(f));
            addYearToList(a2,y4);
        }
    }
}

//função relativa ao parsing do ficheiro de voos
DATA_FLIGHTS *read_flightsfile(const char* file_path,DATA_PASSENGERS *dp, DATA_USERS *du, YEARS *ys){
    
    FILE* fp = fopen(file_path, "r");
    create_csvfile("Resultados/flights_errors.csv");

    if(!fp){
        perror("Error opening flights file");
        return NULL;
    }

    DATA_FLIGHTS *df = malloc(sizeof(struct data_flights));
    df -> flights_table = g_hash_table_new(int_hash, int_equal);
    df -> airports_table = g_hash_table_new(g_str_hash, g_str_equal);

    char *line = NULL;
    size_t len = 0;
    int i=0;
    
    while(getline(&line,&len,fp)!=-1){
        if(i==0){
            i++; // serve para ignorar a primeira linha
        }
        else{
            line[strcspn(line, "\n")] = 0;
            FLIGHT *f = create_Flight(line, dp, du, ys);
            if(f != NULL){
              insert_flight(df,f);// função de inserir o voo na base de dados dos voos
              insert_airport(df,f);  
            } 
        }
    }

    free(line);
    fclose(fp);
    return df;
}

// delete da hashatble das structs dos voos
void delete_data_flights(DATA_FLIGHTS *df){

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, df->flights_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        FLIGHT *r =(FLIGHT *)value;
        delete_Flight(r);        
	} 
    g_hash_table_destroy(df->flights_table);

    g_hash_table_iter_init(&iter, df->airports_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        AIRPORT *a =(AIRPORT *)value;
        delete_Airport(a);        
	} 
    g_hash_table_destroy(df->airports_table);


    free(df);
}

void add_passengers(DATA_FLIGHTS *df, char *flight_id, int pass){
    FLIGHT *f = g_hash_table_lookup(df->flights_table,flight_id);
    setPassegers(f,pass);
}

//gets das hashtables dos voos e dos aeroportos
GHashTable *getFlightsTable(DATA_FLIGHTS *df){
    return(df->flights_table);
}
GHashTable *getAirportsTable(DATA_FLIGHTS *df){
    return(df->airports_table);
}
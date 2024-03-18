#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>
#include<ctype.h>

#include"../include/reservations.h"

//struct que contém todos os dados relativos às reservas
struct data_reservations{
    GHashTable *reservations_table;
    GHashTable *hotels_table;
};

//insere um reserva na sua hashtable
void insert_reservation(DATA_RESERVATIONS *dr, RESERVATION *r){
    g_hash_table_insert(dr->reservations_table, GINT_TO_POINTER(getReservationId(r)), r);
}

//insere um hotel na sua hashtable
void insert_hotel(DATA_RESERVATIONS *dr, RESERVATION *r){
    HOTEL *h = g_hash_table_lookup(dr->hotels_table, GINT_TO_POINTER(getResHotelId(r)));
    if(h == NULL){
        HOTEL *h1 = newHotel();
        setHotelId(h1, getResHotelId(r));
        setNumberReservations(h1,1);
        setReservationsIds(h1);
        addReservationsList(h1, r);
        g_hash_table_insert(dr->hotels_table, GINT_TO_POINTER(getHotelId(h1)), h1);
    }
    else{
        accNumberReservations(h);
        addReservationsList(h, r);
    }
    
}

//função que lêm o ficheiro de dados das reservas
DATA_RESERVATIONS *read_reservationsfile (const char* file_path, DATA_USERS *du, YEARS *ys){
    
    FILE *fp = fopen(file_path, "r");
    create_csvfile("Resultados/reservations_errors.csv");

    if(!fp){
        perror("Error opening reservations file");
        return NULL; 
    }

    DATA_RESERVATIONS *dr = malloc(sizeof(struct data_reservations));
    dr -> reservations_table = g_hash_table_new(int_hash, int_equal);
    dr -> hotels_table = g_hash_table_new(int_hash, int_equal);

    char *line = NULL;
    size_t len=0;
    int i=0;

    while(getline(&line,&len,fp)!=-1){
        if(i==0){
            i++; // ignorar a primeira linha
        }
        else{
            line[strcspn(line, "\n")] = 0;
            RESERVATION *r = create_Reservation(line, du, ys);
            if(r!=NULL){
               insert_reservation(dr,r); // função de inserir a reserva na base de dados das reservas 
               insert_hotel(dr,r);
            } 
        }
    }

    free(line);
    fclose(fp);
    return dr;
}

//função que apagam todos os dados das hashtables relativas a reservas
void delete_data_reservations(DATA_RESERVATIONS *dr){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, dr->reservations_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        RESERVATION *r =(RESERVATION *)value;
        delete_Reservation(r);        
	} 
    g_hash_table_destroy(dr->reservations_table);

    g_hash_table_iter_init(&iter, dr->hotels_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        HOTEL *h =(HOTEL *)value;
        delete_Hotel(h);        
	} 
    g_hash_table_destroy(dr->hotels_table);

    free(dr);
}

//gets das hashtables
GHashTable *getReservationsTable(DATA_RESERVATIONS *dr){
    return(dr->reservations_table);
}

GHashTable *getHotelsTable(DATA_RESERVATIONS *dr){
    return(dr->hotels_table);
}

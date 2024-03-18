#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/seat.h"

//struct realativa aos dados de um voo e os seus passageiros
struct seats{
    int flight_id;
    GSList *usersList;
    int nr_seats;
    int valido;
};

//função que apaga uma struct seats
void delete_seats(SEATS *s){
    //free(s->flight_id);
    if(s->usersList != NULL) g_slist_free_full(s->usersList,free);
    free(s);
}

//função que lêm uma linha do ficheiro dos passageiros e guarda/apaga os dados
SEATS *create_seats(char *line, DATA_USERS *du){

    char *copy = strdup(line);
    SEATS *s = malloc(sizeof(struct seats));
    char *token;
    int i=0, v=1;
    
    while ((token = strsep(&line, ";")) != NULL){
        switch(i++){
            case 0:
                if (token[0] == '\0') v = 0;
                s->flight_id = convertFIDtoint(token);
                break;
            case 1:
                if (token[0] == '\0') v = 0;
                s->usersList = NULL;
                s->valido = 1;
                if(v==1){
                    USER *x = g_hash_table_lookup(getUsersTable(du),token);
                    if(x == NULL) v=0;
                    else{
                        s->nr_seats = 1;
                        s->usersList = g_slist_prepend(s->usersList,strdup(token));
                    }
                }
            break;
        }
    }

    if(v==0){
        copy_To_ErrorsFile("Resultados/passengers_errors.csv",copy);
        free(copy);
        delete_seats(s);
        return NULL;
    }

    free(copy);
    return s;
}

//gets e sets relativos aos seats
int get_flid(SEATS *s){
    return(s->flight_id);
}

GSList *get_passList(SEATS *s){
    return(s->usersList);
}

int get_nrpass(SEATS *s){
    return(s->nr_seats);
}

int get_valido(SEATS *s){
    return(s->valido);
}

void set_valido(SEATS *s, int val){
    s->valido = val;
}

void increaseNrSeats(SEATS *s){
    s->nr_seats++;
}

void addPassList(SEATS *s, char *token){
    s->usersList = g_slist_prepend(s->usersList, token);
}
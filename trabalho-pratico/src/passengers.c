#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/passengers.h"

//estrutura de dados dos passageiros
struct data_passengers{
    GHashTable *passengers_table;
};

// inserção dos passageiros de um voo na hashtable dos passageiros
void insert_seats(DATA_PASSENGERS *dp, SEATS *s){
    g_hash_table_insert(dp->passengers_table, GINT_TO_POINTER(get_flid(s)), s);
}

//parse e validação dos passageiros a partir do ficheiro csv
DATA_PASSENGERS *read_passengersfile(const char * file_path, DATA_USERS *du){

    FILE* fp = fopen(file_path, "r");
    create_csvfile("Resultados/passengers_errors.csv");

    if(!fp){
        perror("Error opening passengers file");
        return NULL;
    }

    DATA_PASSENGERS *dp = malloc(sizeof(struct data_passengers));
    dp -> passengers_table = g_hash_table_new(int_hash, int_equal);

    char *line = NULL;
    int i=0;
    size_t len=0;
    
    while(getline(&line,&len,fp)!=-1){
        if(i==0){
            i++; // serve para ignorar a primeira linha
        }
        else{
            line[strcspn(line, "\n")] = 0;
            SEATS *s = create_seats(line, du);
            if(s != NULL){
                SEATS *x = g_hash_table_lookup(dp->passengers_table, GINT_TO_POINTER(get_flid(s)));
                if(x == NULL) insert_seats(dp,s);
                else{
                   GSList *passenger = get_passList(s);
                while (passenger != NULL) {
                    char *passenger_id = (char *)passenger->data;
                    addPassList(x,strdup(passenger_id));
                    increaseNrSeats(x);
                    passenger = passenger->next;
                }
                    delete_seats(s);
                }
            }
        }   
    }

    free(line);
    fclose(fp);

    return dp;
}

// delete da hashtable dos passageiros
void delete_data_passengers(DATA_PASSENGERS *dp){

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, dp->passengers_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        SEATS *r =(SEATS *)value;
        delete_seats(r);        
	}
    g_hash_table_destroy(dp->passengers_table);
    free(dp);
}

//função que escreve os passageiros de voos inválidos no ficheiro de erros
void erase_passengers(DATA_PASSENGERS *dp){
    FILE *result = fopen("Resultados/passengers_errors.csv", "a");
    GHashTableIter iter;
    gpointer key, value;

    g_hash_table_iter_init(&iter, dp->passengers_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        SEATS *s = (SEATS*)value;

        if(get_valido(s) == 0){
            GSList *valores = get_passList(s);
            GSList *atual=valores;

            while(atual != NULL){
                char *value =(char *)atual->data;
                char *string = convertFIDtostring(get_flid(s));
                fprintf(result,"%s;%s\n", string, value);
                free(string);
                atual = atual->next;
            }
        }
    }
    fclose(result);
}

//
void add_flightinfo(DATA_PASSENGERS *dp,DATA_USERS *du, int fid){
    
    SEATS *s = g_hash_table_lookup(getPassengersTable(dp), GINT_TO_POINTER(fid));

    GSList *valores = get_passList(s);

    GSList *atual = valores;

    while(atual != NULL){
        char *value =(char*)atual->data;
        add_flight(du, value, fid);

        atual=atual->next;
    }
}

//get da hashtable dos passageiros
GHashTable *getPassengersTable(DATA_PASSENGERS *dp){
    return(dp->passengers_table);
}

//verifica se um passageiro está na hashtable
int exist_in_pass_table(DATA_PASSENGERS *dp, char* fl_id){
    SEATS *x = g_hash_table_lookup(dp->passengers_table, fl_id);
    if(x == NULL) return 0;
    else return 1;
}


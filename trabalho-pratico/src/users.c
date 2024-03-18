#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glib.h>

#include"../include/users.h"

#define DATA_SISTEMA "2023/10/01"

//struct que contêm todos os dados relativos aos users
struct data_users{
    GHashTable *users_table;
    GSList *user_ids;
};

//função que 
void free_glist_elem(gpointer data){
    free(data);
}

//insere um user na hashtable
void insert_user(DATA_USERS *du, USER *u){
    g_hash_table_insert(du->users_table, (gpointer)getUserId(u), u);
}

//função que ordena os nomes dos users por ordem alfabetica
gint compare_names(gconstpointer a, gconstpointer b){
	USER *user1 =(USER *) a;
	USER *user2 =(USER *) b;
	const char *name1 = getName(user1);
	const char *name2 = getName(user2);

	if(strcmp(name1,name2)<0){
		return -1; 
	}
	if(strcmp(name1,name2)>0){
		return 1;
	}
	else{
		if(strcmp(getUserId(user1),getUserId(user2))<0){
			return -1;
		}
		else return 1;
	}
}

//parse dos users através do ficheiro de dados
DATA_USERS *read_usersfile (const char* file_path, YEARS *ys){
    
    FILE *fp = fopen(file_path, "r");
    create_csvfile("Resultados/users_errors.csv");

    if(!fp){
        perror("Error opening users file");
        return NULL;
    }

    DATA_USERS *du = malloc(sizeof(struct data_users));
    du->users_table = g_hash_table_new(g_str_hash, g_str_equal);
    du->user_ids = NULL;

    char *line = NULL;
    size_t len=0;
    int i=0;
    
    while(getline(&line,&len,fp)!=-1){
        if(i==0){
            i++; // ignorar a primeira linha 
        }
        else{
            line[strcspn(line, "\n")] = 0;
            USER *u = create_User(line, ys);
            if(u != NULL){
               insert_user(du, u);
               du->user_ids = g_slist_prepend(du->user_ids, u);
            } 
        }
    }
 
    du->user_ids = g_slist_sort(du->user_ids, compare_names);

    free(line);
    fclose(fp);
    return du; 
}

//função que apaga todos os dados relativos ao users
void delete_data_users(DATA_USERS *du){

    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init(&iter, du->users_table);

    while (g_hash_table_iter_next(&iter, &key, &value)){
        USER *r =(USER *)value;
        delete_User(r);        
	} 
    
    g_hash_table_destroy(du->users_table);
    g_slist_free(du->user_ids);
    free(du);
}

//função que insere os dados de uma reserva na struct de um user
void add_reservation(DATA_USERS *du, const char *user_id, double price, int resid){
    USER *u = g_hash_table_lookup(du->users_table, user_id);
    accNrReservations(u);
    addTotalSpent(u,price);
    addReservation(u,resid);
}

//função que insere os dados de um voo na struct de um user
void add_flight(DATA_USERS *du, const char *user_id, int fid){
    USER *u = g_hash_table_lookup(du->users_table, user_id);
    if(u == NULL) return;
    accUserNrFlights(u);
    addFlight(u,fid);
}

//verifica se um user id é relativo a um user presente na hashtable
int exist_in_hashtable(DATA_USERS *du, char* us_id){
    USER *x = g_hash_table_lookup(du->users_table, us_id);
    if(x == NULL) return 0;
    else return 1;
}

//retorna o accstatus de um user
int accStat(DATA_USERS *du, const char *usid){
    USER *u = g_hash_table_lookup(du->users_table, usid);
    if(getAccStatus(u) == 1) return 1;
    else return 0;
}

//gets das hashtables
GHashTable *getUsersTable(DATA_USERS *du){
    return(du->users_table);
}

GSList *getUserIdsList(DATA_USERS *du){
    return(du->user_ids);
}
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<glib.h>

#include"../include/func.h"

//funções auxiliares na validação de dados dos fcheiros csv
int verify_Email(const char *email){

    int comp = strlen(email);
    int arr_pos = -1, ponto_pos = -1;

    if (comp < 6) return 0;

    for (int i = 0; i < comp; i++) {
        if (email[i] == '@') {
            arr_pos = i;
        } else if (email[i] == '.' && arr_pos != -1) {
            ponto_pos = i;
        }
    }

    return (arr_pos > 0 && arr_pos < comp - 3 && ponto_pos > arr_pos && ponto_pos < comp - 2);
}

int verify_Status(char *status){

    if (strcasecmp(status,"active")==0) return 2;
    if (strcasecmp(status,"inactive")==0) return 1;

    return 0;
}

int verify_Breakfast(char *info){

    if((strcasecmp(info,"t") == 0)||(strcasecmp(info,"true") == 0)||(strcasecmp(info,"1") == 0)) return 1;
    if((strcasecmp(info,"f") == 0)||(strcasecmp(info,"false") == 0)||(strcasecmp(info,"0") == 0)||(strcasecmp(info,"") == 0)) return 0;

    return 2;
}

//função que cria os ficheiros csv de erros
void create_csvfile(const char *file){
    FILE *csvfile = fopen(file, "w");

    if (csvfile == NULL) {
        perror("Erro ao criar arquivo");
        return;
    }

    if(strcmp("Resultados/users_errors.csv", file) == 0){
        fprintf(csvfile, "id;name;email;phone_number;birth_date;sex;passport;country_code;address;account_creation;pay_method;account_status\n");
    }
    if(strcmp("Resultados/flights_errors.csv", file) == 0){
        fprintf(csvfile, "id;airline;plane_model;total_seats;origin;destination;schedule_departure_date;schedule_arrival_date;real_departure_date;real_arrival_date;pilot;copilot;notes\n");
    }
    if(strcmp("Resultados/reservations_errors.csv", file) == 0){
        fprintf(csvfile, "id;user_id;hotel_id;hotel_name;hotel_stars;city_tax;address;begin_date;end_date;price_per_night;includes_breakfast;room_details;rating;comment\n");
    }
    if(strcmp("Resultados/passengers_errors.csv", file) == 0){
        fprintf(csvfile, "flight_id;user_id\n");
    }

    fclose(csvfile);
}

//função que transfere a linha não validada para o ficheiro de erros
void copy_To_ErrorsFile(const char *file, const char *line){
    FILE *errors = fopen(file, "a");

    if (errors == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    fprintf(errors, "%s\n", line);

    fclose(errors);
}

//funções auxiliares relativas a strings
int is_number(char *nr){
    int s = strlen(nr);
    for(int i=0;i<s;i++){
        if(isdigit(nr[i]) == 0) return 0;
    }

    if(atoi(nr)<0) return 0;

    return 1;
}

//converte uma string em letras minusculas para maiúsculas
char *convertToUpperCase(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = toupper(str[i]);
    }

    return str;
}

int convertFIDtoint(char *str){
 
    char *aux;
    int num = strtol(str, &aux, 10);

    return num;
}

char *convertFIDtostring(int value){
    char format[11];
    snprintf(format, 11, "%%0%dd", 10);

    char* result = (char*)malloc(11);  

    snprintf(result, 11, format, value);
    return result;
}

int convertRIDtoint(char *str){
    str = str+4;

    char *endptr;
    int result = strtol(str, &endptr, 10);

    return result;
}

char *convertRIDtostring(int num){

    char format[15];
    snprintf(format, 15, "Book%%0%dd", 10);

    char *result = (char *)malloc(15); 

    snprintf(result, 15, format, num);
    return result;
}

int convertHIDtoint(char *str){
    str = str+3;

    char *endptr;
    int result = strtol(str, &endptr, 10);

    return result;
}

char *convertHIDtostring(int num){

    char *result = (char *)malloc(8); 

    snprintf(result, 8, "HTL%d", num);
    return result;
}


guint int_hash(gconstpointer key) {
    return GPOINTER_TO_UINT(key);
}

// Equality function for GHashTable with integer keys
gboolean int_equal(gconstpointer a, gconstpointer b) {
    return a == b;
}

// compara duas strings
gint compare_char(gconstpointer a, gconstpointer b){
    gchar char_a = GPOINTER_TO_INT(a);
    gchar char_b = GPOINTER_TO_INT(b);

    if (char_a < char_b) return -1;
    else  return 1;
}

//dá free a uma lista de strings
void freelist(char *lista[], int length){
    for (int i = 0; i < length; i++) {
        if(lista[i] != NULL)free(lista[i]); 
    }
    free(lista);
}

//função responsável pela paginação de respostas extensas
void paginated_outputs(char **args, int N) {

    if (args == NULL){
        printf("Sem resultados para esta procura!\n");
        return;
    }

    int end = 0, current_page = 1, last_page = N / 50;

    if(N%50 > 0) last_page++;

    printf("%d páginas\n",last_page);

    while (end == 0) {
        printf("Escolha a página que quer ver ou 0 para sair!\n");
        char choice[8];
        if(fgets(choice, sizeof(choice), stdin)==0) return;
        choice[strcspn(choice, "\n")] = 0;
        current_page = atoi(choice);
        if (current_page > 0 && current_page <= last_page) {
            printf("Página %d de %d.\n", current_page, last_page);
            for(int i= (current_page-1)*50;i<N && i<current_page*50;i++){
                printf("%s\n", args[i]);
            }

        } 
        else if (current_page == 0) end = 1;
        else{
            printf("Essa página não existe\n");
        }
    }

}

//função geral de impressão de outputs
void printline(char *out_path, char **args, int print_type, int q_nr, int q_type, int nr_lines){
 
    switch (q_nr){
        case -1:
            if(print_type==2){
                printf("Sem resultados para esta procura\n");
            }
            else{
               FILE *output;
                output = fopen(out_path, "w");
                fclose(output); 
            }
            
            break;
        case 1:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "w");
                fprintf(output, "%s\n",*args);
                fclose(output);

            }
            else if(print_type == 2){
                FILE *output;
                output = fopen(out_path, "w");
                if(q_type==1){
                    char *token, *aux=*args;
                    int k=0;

                    fprintf(output, "--- 1 ---\n");

                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "name: %s\n", token); 
                                break;
                            case 1:
                                fprintf(output, "sex: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "age: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "country_code: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "passport: %s\n", token);
                                break;
                            case 5:
                                fprintf(output, "number_of_flights: %s\n", token);
                                break;
                            case 6:
                                fprintf(output, "number_of_reservations: %s\n", token);
                                break;
                            case 7:
                                fprintf(output, "total_spent: %s\n", token);
                                break;
                        }
                    }
    
                }
                else if(q_type==2){
                    char *token, *aux=*args;
                    int k=0;

                    fprintf(output, "--- 1 ---\n");

                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "hotel_id: %s\n", token); 
                                break;
                            case 1:
                                fprintf(output, "hotel_name: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "hotel_stars: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "begin_date: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "end_date: %s\n", token);
                                break;
                            case 5:
                                fprintf(output, "includes_breakfast: %s\n", token);
                                break;
                            case 6:
                                fprintf(output, "nights: %s\n", token);
                                break;
                            case 7:
                                fprintf(output, "total_price: %s\n", token);
                                break;
                        }
                    }
                }
                else{
                    char *token, *aux=*args;
                    int k=0;

                    fprintf(output, "--- 1 ---\n");

                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "airline: %s\n", token); 
                                break;
                            case 1:
                                fprintf(output, "plane_model: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "origin: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "destination: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "schedule_departure_date: %s\n", token);
                                break;
                            case 5:
                                fprintf(output, "schedule_arrival_date: %s\n", token);
                                break;
                            case 6:
                                fprintf(output, "passengers: %s\n", token);
                                break;
                            case 7:
                                fprintf(output, "delay: %s\n", token);
                                break;
                        }
                    }
                }
                fclose(output);
                    
            }
            else{
                printf("%s\n",*args);
                printf("\n");
            }

            
            free(*args);
            break;
        
        case 2:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");
                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }
                
                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");

                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "id: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "date: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "type: %s\n", token);
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }
                
                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;
        
        case 3:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "w");

                fprintf(output, "%s", *args);

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "w");

                fprintf(output, "--- 1 ---\nrating: %s", *args);

                fclose(output);
            }
            else{
                printf("%s\n", *args);
                printf("\n");
            }

            free(*args);

            break;

        case 4:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "id: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "begin_date: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "end_date: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "user_id: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "rating: %s\n", token);
                                break;
                            case 5:
                                fprintf(output, "total_price: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;
        
        case 5:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "id: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "schedule_departure_date: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "destination: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "airline: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "plane_model: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;

        case 6:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "name: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "passengers: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;

        case 7:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "name: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "median: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;
        
        case 8:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                fprintf(output, "%s\n", *args);

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");

                fprintf(output, "--- 1 ---\nrevenue: %s\n", *args);

                fclose(output);
            }
            else{
                printf("%s\n", *args);
                printf("\n");
            }

            free(*args);

            break;
        
        case 9:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                fprintf(output, "id: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "name: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);
            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args, nr_lines);

            break;

        case 10:
            if(print_type==1){
                FILE *output;
                output = fopen(out_path, "a");

                for(int i=0;i<nr_lines;i++){
                    fprintf(output, "%s\n", args[i]);
                }

                fclose(output);
            }
            else if(print_type==2){
                
                FILE *output;
                output = fopen(out_path, "a");
                char *token, *aux;
                int k=0;

                for(int i=0;i<nr_lines;i++){
                    aux = args[i];
                    k=0;
                    fprintf(output, "--- %d ---\n", i+1);
                    while((token = strsep(&aux, ";"))!=NULL){
                        switch(k++){
                            case 0:
                                if(q_type==1) fprintf(output, "day: %s\n", token);
                                else if(q_type==2) fprintf(output, "month: %s\n", token);
                                else fprintf(output, "year: %s\n", token);
                                break;
                            case 1:
                                fprintf(output, "users: %s\n", token);
                                break;
                            case 2:
                                fprintf(output, "flights: %s\n", token);
                                break;
                            case 3:
                                fprintf(output, "passengers: %s\n", token);
                                break;
                            case 4:
                                fprintf(output, "unique_passengers: %s\n", token);
                                break;
                            case 5:
                                fprintf(output, "reservations: %s\n", token);
                                break;
                        }
                    }
                    if(i!=nr_lines-1) fprintf(output,"\n");
                }

                fclose(output);

            }
            else{
                if(nr_lines<=50){
                    for(int i=0;i<nr_lines;i++){
                        printf("%s\n", args[i]);
                    }
                    printf("\n");
                }
                else paginated_outputs(args, nr_lines);
            }

            freelist(args,nr_lines);

        default:
            break;
    }  

}


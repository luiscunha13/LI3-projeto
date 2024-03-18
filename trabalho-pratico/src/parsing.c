#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<glib.h>


#include"../include/parsing.h"

//função que cria as diferentes estruturas de dados do catálogo a partir dos ficheiros csv
CATALOG *open_folder(const char *folder_path){

    CATALOG *c = create_catalog();
    setYears(c);

    char path[50];
    snprintf(path, sizeof(path), "%s", folder_path);

    char usersPath[100];
    snprintf(usersPath, sizeof(usersPath), "%s/users.csv", path);
    setDataUsers(c, usersPath, getYears(c));

    char passengersPath[100];
    snprintf(passengersPath, sizeof(passengersPath), "%s/passengers.csv", path);
    setDataPassengers(c, passengersPath, getDataUsers(c));
    
    char flightsPath[100];
    snprintf(flightsPath, sizeof(flightsPath), "%s/flights.csv", path);
    setDataFlights(c, flightsPath, getDataPassengers(c), getDataUsers(c), getYears(c));

    erase_passengers(getDataPassengers(c));

    char reservationsPath[100];
    snprintf(reservationsPath, sizeof(reservationsPath), "%s/reservations.csv", path);
    setDataReservations(c, reservationsPath, getDataUsers(c), getYears(c));

    
    return c;
}

double getElapsedTime(clock_t start, clock_t end) {
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

//função que lê o ficheiros csv das queries e as realiza
int read_queriesfile(char *line, CATALOG *c, int i, double tempos[]){

    clock_t start, end;

    char out_path[100], param1[25], param2[25], param3[15], param4[15], param5[15];  // path do ficheiro output de 1 query

    sprintf(out_path, "./Resultados/command%d_output.txt", i);

        switch(line[0]){
            case '1':
                start = clock();
                if(line[1] == ' ') query1(out_path,&line[2],c,0);
                if(line[1] == 'F') query1(out_path,&line[3],c,1);
                end = clock();
                tempos[0] += getElapsedTime(start, end);
                start = clock();
                if(line[1] == '0'){
                    if(line[2] == 'F'){
                        if (sscanf(&line[4], "%4s %2s", param1, param2) == 2) {
                            query10(out_path, atoi(param1), atoi(param2),2,c,1);
                        } 
                        else if (sscanf(&line[4], "%4s", param1) == 1) {
                            query10(out_path, atoi(param1),-1,1,c,1);
                        } 
                        else {
                            query10(out_path, -1, -1, 0,c,1);
                        }
                    }
                    else{
                        if (sscanf(&line[3], "%4s %2s", param1, param2) == 2) {
                            query10(out_path, atoi(param1), atoi(param2),2,c,0);
                        } 
                        else if (sscanf(&line[3], "%4s", param1) == 1) {
                            query10(out_path, atoi(param1),-1,1,c,0);
                        }
                        else {
                            query10(out_path,-1,-1,0,c,0);
                        }
                    }
                }
                end = clock();
                tempos[9] += getElapsedTime(start, end);
                break;
            case '2':
                start = clock();
                if(sscanf(&line[2], "%s %15s", param1, param2)==1){
                    if(line[1] == ' ') query2(out_path, param1, param2,0,c,0);
                    if(line[1] == 'F') query2(out_path, param1, param2,0,c,1);
                }
                else{
                    if(line[1] == ' ') query2(out_path, param1, param2,1,c,0);
                    if(line[1] == 'F') query2(out_path, param1, param2,1,c,1);
                }
                end = clock();
                tempos[1] += getElapsedTime(start, end);
                break;
            case '3':
                start = clock();
                if(line[1] == ' ') query3(out_path,&line[2],c,0);
                if(line[1] == 'F') query3(out_path,&line[3],c,1);
                end = clock();
                tempos[2] += getElapsedTime(start, end);
                break;
            case '4':
                start = clock();
                if(line[1] == ' ') query4(out_path,&line[2],c,0);                                    
                if(line[1] == 'F') query4(out_path,&line[3],c,1);
                end = clock();
                tempos[3] += getElapsedTime(start, end);
                break;
            case '5':
                start = clock();
                sscanf(&line[2], "%s %s %s %s %s", param3, param1, param2, param4, param5);
                if(line[1] == ' ') query5(out_path,param3,param1,param2,param4, param5,c,0);
                if(line[1] == 'F') query5(out_path,param3,param1,param2,param4, param5,c,1);
                end = clock();
                tempos[4] += getElapsedTime(start, end);
                break;
            case '6':
                start = clock();
                sscanf(&line[2], "%s %s", param1, param3);
                if(line[1] == ' ') query6(out_path,param1,atoi(param3),c,0);
                if(line[1] == 'F') query6(out_path,param1,atoi(param3),c,1);
                end = clock();
                tempos[5] += getElapsedTime(start, end);
                break;
            case '7':
                start = clock();
                sscanf(&line[2], "%s", param3);
                if(line[1] == ' ') query7(out_path, atoi(param3),c,0);
                if(line[1] == 'F') query7(out_path, atoi(param3),c,1);
                end = clock();
                tempos[6] += getElapsedTime(start, end);
                break;
            case '8':
                start = clock();
                sscanf(&line[2], "%s %s %s", param3, param1, param2);
                if(line[1] == ' ') query8(out_path,param3,param1,param2,c,0);
                if(line[1] == 'F') query8(out_path,param3,param1,param2,c,1);
                end = clock();
                tempos[7] += getElapsedTime(start, end);
                break;
            case '9':
                start = clock();
                if(line[1] == ' ') query9(out_path,&line[2],c,0);
                if(line[1] == 'F') query9(out_path,&line[3],c,1);
                end = clock();
                tempos[8] += getElapsedTime(start, end);
                break;
            
        }

    return 0;
}

//modo batch do programa
int normal_program(const char *queries_path, CATALOG *c){
    
    FILE *queries_file = fopen(queries_path, "r");

    if(!queries_file){
        perror("Error opening information file");
        return 2;
    }

    double tempos[10] = {0};
    char *line = NULL;
    size_t len;
    int i=1;

    while (getline(&line, &len, queries_file) != -1) {
        line[strcspn(line, "\n")] = 0;
        read_queriesfile(line,c,i,tempos);
        i++;
    }

    free(line);
    fclose(queries_file);

    return 0;
}

int checkFolder(const char *path) {
    // Define the required file names
    const char *files[] = {"flights.csv", "passengers.csv", "reservations.csv", "users.csv"};

    // Check the existence of each file
    for (int i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        char filepath[256]; // Adjust the size according to your needs
        snprintf(filepath, sizeof(filepath), "%s/%s", path, files[i]);

        FILE *file = fopen(filepath, "r");

        if (file == NULL) {
            // File does not exist
            return 0; // Return false
        }

        fclose(file);
    }

    // All files exist
    return 1; // Return true
}

//modo interativo do programa
void interactive_program(){

    char input[75];

    while(1){
        printf("Escreva o caminho para a pasta dos ficheiros de dados:\n");

        if(fgets(input, sizeof(input), stdin)==0) continue;

        if (input[0] != '\n' && input[0] != '\0') {
            input[strcspn(input, "\n")] = 0;
        }

        if(checkFolder(input)==1) break;
        
        printf("Input inválido. Tente novamente\n");
    }


    printf("\n"); 
    printf("__________                   __        __           .____    .___________   \n");
    printf("\\______   \\_______  ____    |__| _____/  |_  ____   |    |   |   \\_____  \\  \n");
    printf(" |     ___/\\_  __ \\/  _ \\   |  |/ __ \\   __\\/  _ \\  |    |   |   | _(__  <  \n"); 
    printf(" |    |     |  | \\(  <_> )  |  \\  ___/|  | (  <_> ) |    |___|   |/       \\ \n");
    printf(" |____|     |__|   \\____/\\__|  |\\___  >__|  \\____/  |_______ \\___/______  / \n");
    printf("                        \\______|    \\/                      \\/          \\/  \n");
    printf("\n");

    CATALOG *c = open_folder(input);
    int aux=0;

    while(aux==0){
        printf("Escreva o número da query que quer realizar (1-10) ou q se quiser terminar o programa\n");
        char querynr[3];

        if(fgets(querynr, 3, stdin)==0){
            printf("Número de query inválido!\n");
            continue;
        }

        querynr[strcspn(querynr, "\n")] = 0;

        if(strcmp(querynr, "q")==0) break;

        printf("Escreva o modo de impressão das respostas (t -> terminal/f -> ficheiro txt):\n");
        char print_type[2];
        char file_path[75];
        char format[2];

        if(fgets(print_type, 2, stdin)==0){
            printf("Tipo de impressão inválido!\n");
            continue;
        }

        int a;
        while ((a = getchar()) != '\n' && a != EOF);

        print_type[strcspn(print_type, "\n")] = 0;
        
        if(strcmp(print_type,"f")==0){
            printf("Escreva o caminho para guardar o ficheiro:\n");

            if(fgets(file_path, 75, stdin)==0){
                printf("Nome inválido");
                continue;
            }

            file_path[strcspn(file_path, "\n")] = 0;
            while ((a = getchar()) != '\n' && a != EOF);
                
            printf("Escreva se quer a impressão no formato f(f) ou no normal(n):\n");

            if(fgets(format, 2, stdin)==0){
                printf("Formato de impressão inválido!\n");
                continue;
            }

            format[strcspn(format, "\n")] = 0;
            while ((a = getchar()) != '\n' && a != EOF);
                //../../Dataset/dataset/data  

        }

        int q = atoi(querynr);
        char arguments[100];
        char param1[25], param2[25], param3[15], param4[15], param5[15];
        switch(q){
            case 1:
                printf("Escreva o id do utilizador/voo/reserva:\n");
                if(fgets(param1, sizeof(param1), stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                param1[strcspn(param1, "\n")] = 0;
                if(strcmp(print_type,"t")==0) query1(NULL,param1,c,2);
                else{
                    if(strcmp(format,"n")==0) query1(file_path,param1,c,0);
                    else query1(file_path,param1,c,1);
                }
                break;
            case 2:
                printf("Escreva o id do utilizador e flights/reservations caso queira especificar:\n");
                if(fgets(arguments, 100, stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                if(sscanf(arguments,"%s %s", param1, param2)==1){
                    param1[strcspn(param1, "\n")] = 0;
                    if(strcmp(print_type,"t")==0) query2(NULL,param1,param2,0,c,2);
                    else{
                        if(strcmp(format,"n")==0) query2(file_path,param1,param2,0,c,0);
                        else query2(file_path,param1,param2,0,c,1);
                    }
                }
                else{
                    param2[strcspn(param2, "\n")] = 0;
                    if(strcmp(param2, "flights")!=0 && strcmp(param2,"reservations")!=0){
                        printf("Informações inválidas!\n");
                        continue;
                    }
                    if(strcmp(print_type,"t")==0) query2(NULL,param1,param2,1,c,2);
                    else{
                        if(strcmp(format,"n")==0) query2(file_path,param1,param2,1,c,0);
                        else query2(file_path,param1,param2,1,c,1);
                    }
                }
                break;
            case 3:
                printf("Escreva o id do hotel:\n");
                if(fgets(param1, sizeof(param1), stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                param1[strcspn(param1, "\n")] = 0;
                if(strcmp(print_type,"t")==0) query3(NULL,param1,c,2);
                else{
                    if(strcmp(format,"n")==0) query3(file_path,param1,c,0);
                    else query3(file_path,param1,c,1);
                }
                break;
            case 4:
                printf("Escreva o id do hotel:\n");
                if(fgets(param1, sizeof(param1), stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                param1[strcspn(param1, "\n")] = 0;

                if(strcmp(print_type,"t")==0) query4(NULL,param1,c,2);
                else{
                    if(strcmp(format,"n")==0) query4(file_path,param1,c,0);
                    else query4(file_path,param1,c,1);
                }
                break;
            case 5:
                printf("Escreva o aeroporto, a data inicial e a data final:\n");
                if(fgets(arguments, 100, stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(sscanf(arguments,"%s %s %s %s %s", param3, param1, param2, param4, param5)!=5){
                    
                }

                if(verify_Date_Interative(param1,0)==0 || verify_Date_Interative(param2,1)==0 || 
                verify_Date_Interative(param4,0)==0 || verify_Date_Interative(param5,1)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(strcmp(print_type,"t")==0) query5(NULL,param3,param1,param2,param4,param5,c,2);
                else{
                    if(strcmp(format,"n")==0) query5(file_path,param3,param1,param2,param4,param5,c,0);
                    else query5(file_path,param3,param1,param2,param4,param5,c,1);
                }
                break;
            case 6:
                printf("Escreva o ano e o número de aeroportos:\n");
                if(fgets(arguments, 100, stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                if(sscanf(arguments,"%s %s", param1, param3)!=2){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(strcmp(print_type,"t")==0) query6(NULL,param1,atoi(param3),c,2);
                else{
                    if(strcmp(format,"n")==0) query6(file_path,param1,atoi(param3),c,0);
                    else query6(file_path,param1,atoi(param3),c,1);
                }
                
                break;
            case 7:
                printf("Escreva o número de aeroportos com maior mediana:\n");
                if(fgets(param1, sizeof(param1), stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(is_number(param1)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                param1[strcspn(param1, "\n")] = 0;

                if(strcmp(print_type,"t")==0) query7(NULL,atoi(param1),c,2);
                else{
                    if(strcmp(format,"n")==0) query7(file_path,atoi(param1),c,0);
                    else query7(file_path,atoi(param1),c,1);
                }
                break;
            case 8:
                printf("Escreva o id do hotel, a data inicial e a data final:\n");
                if(fgets(arguments, 100, stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(sscanf(arguments,"%s %s %s", param3, param1, param2)!=3){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(verify_Date_Interative(param1,0)==0 || verify_Date_Interative(param2,0)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if(strcmp(print_type,"t")==0) query8(NULL,param3,param1,param2,c,2);
                else{
                    if(strcmp(format,"n")==0) query8(file_path,param3,param1,param2,c,0);
                    else query8(file_path,param3,param1,param2,c,1);
                }
                break;
            case 9:
                printf("Escreva o prefixo:\n");
                if(fgets(param1, sizeof(param1), stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }
                param1[strcspn(param1, "\n")] = 0;

                if(strcmp(print_type,"t")==0) query9(NULL,param1,c,2);
                else{
                    if(strcmp(format,"n")==0) query9(file_path,param1,c,0);
                    else query9(file_path,param1,c,1);
                }
                break;
            case 10:
                printf("Escreva o ano, o ano e o mês ou apenas prima enter:\n");
                if(fgets(arguments, 100, stdin)==0){
                    printf("Informações inválidas!\n");
                    continue;
                }

                if (sscanf(arguments, "%4s %2s", param1, param2) == 2) {
                    if(is_number(param1)==0 || is_number(param2)==0){
                        printf("Informações inválidas!\n");
                        continue;
                    }

                    if(strcmp(print_type,"t")==0) query10(NULL,atoi(param1), atoi(param2),2,c,2);
                    else{
                        if(strcmp(format,"n")==0) query10(file_path,atoi(param1), atoi(param2),2,c,0);
                        else query10(file_path,atoi(param1), atoi(param2),2,c,1);
                    }
                } 
                else if (sscanf(arguments, "%4s", param1) == 1) {
                    if(is_number(param1)==0){
                        printf("Informações inválidas!\n");
                        continue;
                    }
                    if(strcmp(print_type,"t")==0) query10(NULL,atoi(param1), -1,1,c,2);
                    else{
                        if(strcmp(format,"n")==0) query10(file_path,atoi(param1), -1,1,c,0);
                        else query10(file_path,atoi(param1), -1,1,c,1);
                    }
                }
                else {
                    if(strcmp(print_type,"t")==0) query10(NULL,-1,-1,1,c,2);
                    else{
                        if(strcmp(format,"n")==0) query10(file_path,-1,-1,1,c,0);
                        else query10(file_path,-1,-1,1,c,1);
                    }
                    query10(NULL,-1,-1,0,c,2);
                }
                break;
            default:
                printf("Número de query inválido!\n");
                break;
        }

        printf("\n");
        printf("--------------------------");
        printf("\n");
    }

    delete_Catalog(c);
}


//função responsável por comparar as respostas e os outputs corretos
int compare_outputs(int n, const char *outputs_path) {

    char produced_file[100];
    snprintf(produced_file, 100, "Resultados/command%d_output.txt", n);

    char expected_file[100];
    snprintf(expected_file, 100, "%s/command%d_output.txt", outputs_path, n);

    FILE *fp_produced, *fp_expected;
    fp_produced = fopen(produced_file, "r");
    if (!fp_produced) {
        perror("Error produced");
        return -1;
    }
    fp_expected = fopen(expected_file, "r");
    if (!fp_expected) {
        perror("Error expected");
        return -1;
    }

    char *line_produced = NULL;
    size_t len_produced;
    char *line_expected = NULL;
    size_t len_expected;
    int verify = 1;
    int count = 1;

    while (getline(&line_produced, &len_produced, fp_produced) != -1) {
        if(getline(&line_expected, &len_expected, fp_expected) != -1){
            if (strcmp(line_produced, line_expected) != 0){
                verify = 0;
                break;
            }
            count++;
        }
    }

    fclose(fp_produced);
    fclose(fp_expected);

    if (verify == 0) printf("O teste do comando %d falhou na linha %d!\n", n, count);
    else printf("O teste do comando %d passou!\n", n);

    return 0;
}

//testes de desempenho do programa (respostas corretas/tempo gaste/memória usada)
int program_tester(const char *queries_path, const char *outputs_path, CATALOG *c){
    
    FILE *queries_file = fopen(queries_path, "r");

    if(!queries_file){
        perror("Error opening information file");
        return 2;
    }

    double tempos[10] = {0};
    char *line = NULL;
    size_t len;
    int n=1;

    clock_t start, end;
    double cpu_time_used;

    while (getline(&line, &len, queries_file) != -1) {
        line[strcspn(line, "\n")] = 0;
        start = clock();
        read_queriesfile(line, c, n, tempos);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("O comando %d demorou: %f segundos\n", n, cpu_time_used);
        compare_outputs(n,outputs_path);
        n++;
    }

    for (int j = 0; j < 10; j++) {
        printf("\nTempo gasto na query %d: %f segundos", j+1, tempos[j]);
    }

    free(line);
    fclose(queries_file);

    return 0;
}


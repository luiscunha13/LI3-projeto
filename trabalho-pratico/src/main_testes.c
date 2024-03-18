#include<glib.h>
#include <time.h>
#include <stdio.h>
#include <sys/resource.h>

#include"../include/parsing.h"
#include"../include/catalog.h"


int main(int argc, char **input){

    if(argc>=3){

        struct rusage r_usage;

        struct timespec start, end;
        double elapsed;
        clock_gettime(CLOCK_REALTIME, &start);

        CATALOG *c = open_folder(input[1]); 
        program_tester(input[2],input[3],c);
        delete_Catalog(c);

        clock_gettime(CLOCK_REALTIME, &end);
        elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("\n\nElapsed time: %.6f seconds\n", elapsed);

        getrusage(RUSAGE_SELF, &r_usage);
        printf("Memory usage: %ld KB\n", r_usage.ru_maxrss);

    }

    return 0;
}
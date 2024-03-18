#include"../include/catalog.h"
#include"../include/queries.h"

#ifndef PARSING_H
#define PARSING_H

    CATALOG *open_folder(const char *folder_path);

    int read_queriesfile (char *queries_path, CATALOG *c, int number, double tempos[]);

    int normal_program(const char *queries_path, CATALOG *c);

    void interactive_program();

    int program_tester(const char *queries_path, const char *outputs_path, CATALOG *c);


#endif
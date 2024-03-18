#ifndef FUNC_H
#define FUNC_H

    int verify_Email(const char *email);

    int verify_Status(char *status);

    int verify_Breakfast(char *info);

    void create_csvfile(const char *file);

    void copy_To_ErrorsFile(const char *file, const char *line);     

    int is_number(char *nr);

    char *convertToUpperCase(char* str);

    int convertFIDtoint(char *str);

    char *convertFIDtostring(int value);

    int convertRIDtoint(char *str);

    char *convertRIDtostring(int num);

    int convertHIDtoint(char *str);

    char *convertHIDtostring(int num);

    guint int_hash(gconstpointer key);

    gboolean int_equal(gconstpointer a, gconstpointer b);

    gint compare_char(gconstpointer a, gconstpointer b);

    char *getYearFromString(const char *date);

    void freelist(char** lista, int length);

    void printline(char *out_path, char **args, int print_type, int q_nr, int q_type, int nr_line);

#endif
#include"../include/catalog.h"
#include"../include/date.h"
#include"../include/dayinfo.h"

#ifndef QUERIES_H
#define QUERIES_H

void query1(char *out_path, char *id, CATALOG *c, int f);

void query2(char *out_path, char *id, char *arg, int type, CATALOG *c, int f);

void query3(char *out_path, char *hotel_id, CATALOG *c, int f);

void query4(char *out_path,char *hotel_id,CATALOG *c, int f);

void query5(char *out_path, char *origin, char *days_bdate, char *hours_bdate, char *days_edate, char *hours_edate, CATALOG *c, int f);

void query6(char *out_path,char* year, int N, CATALOG *c, int f);

void query7(char *out_path, int N, CATALOG *c, int f);

void query8(char *out_path, char *hotel_id, char *begin_date, char *end_date, CATALOG *c, int f);

void query9(char *out_path, char *prefix, CATALOG *c, int f);

void query10(char *out_path, int year, int month, int type, CATALOG *c, int f);

#endif
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<glib.h>

#include"../include/date.h"

//estrutura que guarda todos os dados relativos a datas no programa
struct date{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

//criação da struct
DATE *newDate(){
    DATE *d = malloc(sizeof(struct date));
    d->year=0;
    d->month=0;
    d->day=0;
    d->hour=0;
    d->minute=0;
    d->second=0;
    return d;
}

//verificação de datas recebidas no modo interativo
int verify_Date_Interative(char *date, int i){
    
    if (i==0 && strlen(date)==10) {
        int year, month, day;
        if (sscanf(date, "%d/%d/%d", &year, &month, &day) == 3) {
            if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31){
                return 1;
            }
        }
    }

    if (i==1 &&strlen(date)== 19) {
        int hour, minute, second;
        if (sscanf(date, "%d:%d:%d", &hour, &minute, &second) == 3) {
            if (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && 
                second >= 0 && second <= 59) return 1;
        }
    }

    return 0;
}

//verificação da validade das datas dos ficheiros csv
DATE *verify_Date(char *date, DATE *d){
    
    if (strlen(date)== 10) {
        int year, month, day;
        if (sscanf(date, "%d/%d/%d", &year, &month, &day) == 3) {
            if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                d->year=year;
                d->month=month;
                d->day=day;
                d->hour=0;
                d->minute=0;
                d->second=0;
                return d;
            }
        }
    }

    if (strlen(date)== 19) {
        int year, month, day, hour, minute, second;
        if (sscanf(date, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) == 6) {
            if (year >= 0 && month >= 1 && month <= 12 && day >= 1 && day <= 31 &&
                hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {
                d->year=year;
                d->month=month;
                d->day=day;
                d->hour=hour;
                d->minute=minute;
                d->second=second;
                return d;
            }
        }
    }

    return NULL;
}

//diferença em segunda entre duas datas
int difference_dates(DATE *d1, DATE *d2){
    
    int dif = (d2->day - d1->day)*24*60*60+
    (d2->hour - d1->hour)*60*60 + 
    (d2->minute - d1->minute)*60 + 
    (d2->second - d1->second);

    return dif;

}

//comparação de duas datas, return 1 se d1<d2, return -1 se d1>d2 e return 0 se d1 == d2
int compare_dates(DATE *d1, DATE *d2){

    if((d1->year < d2->year) || 
       (d1->year == d2->year && d1->month < d2->month) || 
       (d1->year == d2->year && d1->month == d2->month && d1->day < d2->day) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour < d2->hour) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour == d2->hour && d1->minute < d2->minute) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour == d2->hour && d1->minute == d2->minute && d1->second < d2->second))
        return 1;
    if((d1->year > d2->year) || 
       (d1->year == d2->year && d1->month > d2->month) || 
       (d1->year == d2->year && d1->month == d2->month && d1->day > d2->day) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour > d2->hour) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour == d2->hour && d1->minute > d2->minute) ||
       (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day && d1->hour == d2->hour && d1->minute == d2->minute && d1->second > d2->second))
        return -1;
    else return 0; 
}

//passa uma data para string

char *datetostring(DATE *d, int flag){

    char *date;
    
    if(flag==1){
        if(d->day)
        if(asprintf(&date,"%04d/%02d/%02d %02d:%02d:%02d",d->year, d->month, d->day, d->hour, d->minute, d->second)==0) return NULL;
    }
    else{
        if(asprintf(&date,"%04d/%02d/%02d", d->year,d->month,d->day)==0) return NULL;
    }

    return date;
}

//gets relativos a estrutura DATE
int getyear(DATE *d){
    return(d->year);
}

int getmonth(DATE *d){
    return(d->month);
}

int getday(DATE *d){
    return(d->day);
}

int gethour(DATE *d){
    return(d->hour);
}

int getminute(DATE *d){
    return(d->minute);
}

int getsecond(DATE *d){
    return(d->second);
}




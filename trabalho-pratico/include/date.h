#ifndef DATE_H
#define DATE_H

    typedef struct date DATE;

    DATE *newDate();

    int verify_Date_Interative(char *date, int i);

    DATE *verify_Date(char *date, DATE *d);

    int compare_dates(DATE *d1, DATE *d2);

    int difference_dates(DATE *d1, DATE *d2);

    char *datetostring(DATE *d, int flag);
    //gets

    int getyear(DATE *d);

    int getmonth(DATE *d);

    int getday(DATE *d);

    int gethour(DATE *d);

    int getminute(DATE *d);

    int getsecond(DATE *d);

#endif
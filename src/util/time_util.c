//
// Created by alex on 7/11/19.
//

#include <time.h>
#include <stdlib.h>
#include "time_util.h"

char *getStringTime() {
    char *date = (char *) malloc(25);

    time_t aclock;
    time(&aclock);
    strftime(date, 25, "%Y-%m-%d %H:%M:%S", localtime(&aclock));
    //printf("%s\n", date);

    return date;
}
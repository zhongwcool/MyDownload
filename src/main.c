#include <stdio.h>

#include "util/download.c"

char *getStringTime() {
    char *date;//YYYYMMDDhhmmss
    date = (char *) malloc(10);

    time_t aclock;
    time(&aclock);
    strftime(date, 15, "%H%M%S", localtime(&aclock));
    printf("%s\n", date);

    return date;
}

int main() {
    printf("Hello, World!\n");

    char filename[23];
    sprintf(filename, "wc_%s.exe", getStringTime());
    url2file("https://dldir1.qq.com/weixin/Windows/WeChat_C1018.exe", filename);
    printf("Hello, World!\n");
    return 0;
}


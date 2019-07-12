#include <stdio.h>

#include "util/download.c"
#include "util/time_util.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("No argument input!\n");
        return -1;
    }

    char *url = argv[1];
    printf("The URL: %s \n", url);
    printf("Download START: %s\n", getStringTime());
    url2file(url, "file/WeChat.exe");
    printf("Download END  : %s\n", getStringTime());
    return 0;
}


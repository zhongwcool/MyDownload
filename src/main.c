#include <stdio.h>

#include "util/download.c"

int main() {
    printf("Hello, World!\n");
    url2file("https://dldir1.qq.com/qqfile/QQIntl/QQi_PC/QQIntl2.11.exe", "qq.exe");
    printf("Hello, World!\n");
    return 0;
}
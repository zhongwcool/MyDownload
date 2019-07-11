#include <stdio.h>

#include "util/download.c"
#include "util/time_util.h"

int main() {
    printf("Download START: %s\n", getStringTime());
    url2file("https://dldir1.qq.com/weixin/Windows/WeChat_C1018.exe", "WeChat.exe");
    printf("Download END  : %s\n", getStringTime());
    return 0;
}


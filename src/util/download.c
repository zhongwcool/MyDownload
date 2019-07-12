/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Download a given URL into a local file named page.out.
 * </DESC>
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * 许多在Linux下开发的C程序都需要头文件unistd.h，但VC中没有个头文件，
 * 所以用VC编译总是报错。把下面的内容保存为unistd.h，可以解决这个问题。
 */
#ifdef _WIN32
#include <io.h>
#include <process.h>
#else

#include<unistd.h>

#endif

#include <curl/curl.h>
#include <stdbool.h>
#include <sys/stat.h>

char *progress_data_tag = "[progress]";
const char *PATH_DOWNLOAD = "file";

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE *) stream);
    return written;
}

int my_progress_func(char *progress_data, double dltotal, double dlnow, double ultotal, double ulnow) {
    int radius = (int) (100.0 * dlnow / dltotal);
    if (radius > 0) printf("%s *************************** %d%%\n", progress_data, radius);
    return 0;
}

// 保存URL文件内容到文件
bool url2file(const char *web_url, const char *filename) {
    CURL *curl_handle;
    FILE *saveFile;

    curl_global_init(CURL_GLOBAL_ALL);

    /// init the curl session
    /// 初始化cURL协议
    curl_handle = curl_easy_init();

    /// set URL to get here
    /// 设置URL到这里
    curl_easy_setopt(curl_handle, CURLOPT_URL, web_url);

    /// Switch on full protocol/debug output while testing
    /// 测试时开启完整的协议/调试输出
    curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, false);

    /// disable progress meter, set to 0L to enable and disable debug output
    /// 禁用进度表，设置为0L启用和禁用调试输出
    curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, false);

    /// 进度信息
    curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, my_progress_func);
    curl_easy_setopt(curl_handle, CURLOPT_PROGRESSDATA, progress_data_tag);

    /// send all data to this function
    /// 所有数据发送给这个函数
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

#ifdef SKIP_PEER_VERIFICATION
    /*
         * If you want to connect to a site who isn't using a certificate that is
         * signed by one of the certs in the CA bundle you have, you can skip the
         * verification of the server's certificate. This makes the connection
         * A LOT LESS SECURE.
         *
         * If you have a CA cert for the server stored someplace else than in the
         * default bundle, then the CURLOPT_CAPATH option might come handy for
         * you.
         */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
         * If the site you're connecting to uses a different host name that what
         * they have mentioned in their server certificate's commonName (or
         * subjectAltName) fields, libcurl will refuse to connect. You can skip
         * this check, but this will make the connection less secure.
         */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /// open the file
    /// 写文件到结果文件
    mkdir(PATH_DOWNLOAD, 0777);
    saveFile = fopen(filename, "wb");
    if (saveFile) {
        /// write the page body to this file handle
        /// 写页面文件到保存文件句柄
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, saveFile);

        /* Perform the request, res will get the return code */
        CURLcode res = curl_easy_perform(curl_handle);

        /* Check for errors */
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            printf("download failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("download successful.\n");
        }

        /* close the header file */
        fclose(saveFile);
    } else {
        printf("cannot open the file: %s \n", filename);
    }

    /* always cleanup */
    curl_easy_cleanup(curl_handle);

    /* cleanup curl stuff */
    curl_global_cleanup();

    return true;
}
# MyDownload
用来演示如何在c语言中使用curl完成网络下载

#### Software Architecture
程序的运行依赖对curl源码的编译安装

#### Installation of CURL

1. 下载CURL源码
```shell
git clone https://github.com/curl/curl.git
```
2. 执行configure脚本

进入解压后的CURL根目录，执行：
```shell
./configure –enable-debug
```
3. 执行make

```shell
make
```

4. 执行make install

```shell
sudo make install
```
完成安装后，你可以在/usr/local/include发现curl目录，在/usr/local/lib发现libcurl.*文件，一般在工程中不用特别配置，因为gcc自行找到它们。
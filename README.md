# MyDownload
用来演示如何在c语言中使用curl完成网络下载

### Software Architecture
程序的运行依赖对curl和openssl源码的编译安装

#### 1. Installation of openssl

1、 下载openssl源码

官网下载openssl源码：[点这里](https://www.openssl.org/source/)，本文档编写时最新稳定版本是1.1.1系列，所以下载了openssl-1.1.1c.tar.gz

2、 执行configure脚本

进入解压后的openssl根目录，执行：
```shell
./config
```
3、 执行make

```shell
make
```

4、 执行make install

```shell
sudo make install
```
完成安装后，你可以在/usr/local/include发现openssl目录。一般在工程中不用特别配置，因为gcc自行找到它们。

#### 2. Installation of CURL

1、 下载CURL源码
```shell
git clone https://github.com/curl/curl.git
```
2、 执行configure脚本

进入解压后的CURL根目录，执行：
```shell
./configure
```
如上命令执行完，会显示配置信息。至此检查“SSL support”显示enable，说明对openssl的编译是成功的

![Image](/image/20180706132025143.png)

3、 执行make

```shell
make
```

4、 执行make install

```shell
sudo make install
```
完成安装后，你可以在/usr/local/include发现curl目录，在/usr/local/lib发现libcurl.so.*.*文件，一般在工程中不用特别配置，因为gcc自行找到它们。
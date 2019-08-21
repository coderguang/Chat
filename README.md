ChatDemo
========

[![Build Status](https://travis-ci.org/coderguang/Chat.svg?branch=master)](https://travis-ci.org/coderguang/Chat)

## just a chat demo to test io module, select、poll、epoll
* A  simple  chat  application. 
* Use C++ for server and client.
* No UI,only console.

### how to use
#### server on linux 
  1. it depend on **[Common](https://github.com/coderguang/Common)** project,so you should download it and complie it at first,it use clang .
```shell
    - git clone https://github.com/coderguang/Common.git
    - cd Common/include/json/
    - make clean && make
    - cd ../../../
    - cd Common/lib/
    - rm -rf *.a
    - cd ../../
    - cd Common/log/
    - make clean && make
    - cd ../../
    - cd Common/util/
    - make clean && make
    - cd ../../
    - cd Common/net/socket/
    - make clean && make
    - cd ../../../
    - mv Common ../
```
  2. after build **[Common](https://github.com/coderguang/Common)** project success,you can build select、poll、epoll example.
```shell
  - cd server/s_select
  - make clean && make
  - cd ../
  - cd s_poll
  - make clean && make
  - cd ../
  - cd s_epoll
  - make clean && make
```
  3. now you will get three Executive Document in server/s_select,server/s_poll,server/s_epoll.  
    defualt listen port is 9000 for epoll,9100 for poll,9200 for select  
    you can modify it on config.h,after modify,you should rebuild it  
    for example: server_poll
    **in linux server:**
     ![run img](https://github.com/coderguang/img/blob/master/chat/linux_server.png)
    **in windows:**
     ![run img](https://github.com/coderguang/img/blob/master/chat/client.png)

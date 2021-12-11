#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include "parameterManager.h"

class socketManager{
    private:
        int port;
        int socketDesc;
        bool isConnected;
        struct sockaddr_in server;
    public:
        int acceptedSocket;
        socketManager(int port);
        bool connect();
        void disConnect();
        bool hasConnection();
        std::string read();
        bool write(string message);
        bool write(int message);
        bool getConnection();
};
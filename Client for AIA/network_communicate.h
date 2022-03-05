#ifndef NETWORK_COMMUNICATE_H
#define NETWORK_COMMUNICATE_H
#include <sys/types.h>
#include <sys/ioctl.h>
#include "string.h"
#include "termios.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "special_functions.h"
#include "structures.h"
#include <iostream>
#include <string>

class network_communicate : public special_functions
{
    char buf[128];
    int bufsize = 128;

    int portnum = 8888;
    int socketfd;

    struct sockaddr_in client_addr;
    socklen_t size_client;

    char *ip_add = "127.0.0.1";
    bool connectfl = false;

    void intHandler(int dummy);
    //{
    //    keepRunning = 0;

    //}

    int create_user(void);

    int login_user(void);

public:
    network_communicate();


};

#endif // NETWORK_COMMUNICATE_H

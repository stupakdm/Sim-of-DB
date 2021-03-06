#ifndef SERVER_H
#define SERVER_H

#include "algorithmfunctions.h"
#include "structures.h"
using namespace std;


class Server : public AlgorithmFunctions//, public Exec_commands
{
private:
    int sockfd, servfd;
    vector<int> sock_serv;

    int portNum = 1500;
    bool isExit = false;
    string ip;

    int bufsize = 128;
    char buffer[128];

    struct sockaddr_in server_addr;
    socklen_t size;

    vector<struct user> users;
    int num_of_users;

public:
    Server(int num_of_clients);

    int init_connect(int server);

    int read_users();

    int create_new_user(int server);

    int login_user(int server);

};

#endif // SERVER_H


#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

struct user {
    string login;
    string password;
};

//struct user* users;
//int num_of_users;

class Server {
private:

    int sockfd, server;
    vector<int> sock_serv;

    int portNum = 1500;
    bool isExit = false;

    int bufsize = 128;
    char buffer[128];

    struct sockaddr_in server_addr;
    socklen_t size;

    vector<struct user> users;
    int num_of_users;

public:
    Server(int num_of_clients) {
        //Создаётся неименованный сокет(то есть без ip, порта)
        int err;
        err = read_users();
        if (err == -1) {
            cout << "Error while opening file" << endl;
            exit(1);
        }

        //Создаётся неименованный сокет(то есть без ip, порта)
        sockfd = socket(AF_INET, SOCK_STREAM, 0);  // Создаем сервер с надежным передачами TCP/IP( Для UDP используем SOCK_DGRAM)

        if (sockfd < 0)
        {
            cout << "Error establishing connection" << endl;
            exit(1);
        }

        cout << "Server Socket connection created..." << endl;

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(portNum);

        size = sizeof(server_addr);
        //Задаём параметры на сокет(ip, порт)в
        if (bind(sockfd, (struct sockaddr*)&server_addr, size)<0)
        {
            cout << "Error binding socket.." << endl;
            exit(1);
        }

        cout << "Waiting for clients..." << endl;

        //Слушаем сокет, второй сокет - макс. число подключений
        listen(sockfd, num_of_clients);

        //Сервер ждёт подключения и всвою очередь создается ещё один сокет подключения server
        sock_serv.push_back(sockfd);

        while (true) {

            for (int i=0; i < (int)sock_serv.size(); i++){
                if (sock_serv[i] == sockfd)
                {
                    server = accept(sockfd, (struct sockaddr*)&server_addr, &size);
                    if (server<0)
                    {
                        cout << "Error on accepting..." << endl;
                        exit(1);
                    }
                    sock_serv.push_back(server);
                    init_connect(server);
                }
                else
                {
                    //client_part
                }
            }
            //server = accept(sockfd, (struct sockaddr*)&server_addr, &size);

            //sock_serv.push_back(server);

            //init_connect();

        }
        //server = accept(sockfd, (struct sockaddr*)&server_addr, &size);

        /*if (server<0)
        {
            cout << "Error on accepting..." << endl;
            exit(1);
        }*/

    }

    int init_connect(int server) {
            char msg_log1[] = "Wellcome to AIA database\nPlease, enter your login: ";
            char msg_log2[] = "Incorrect login\nEnter login: ";
            char msg_pas1[] = "Enter password: ";
            char msg_pas2[] = "Incorrect password\nEnter password: ";
            send(server, msg_log1, strlen(msg_log1), 0);
            recv(server, buffer, bufsize, 0);

            cout << buffer;
            string s = string(buffer);
            for (int i =0; i<num_of_users;i++)
            {
                if (s.compare(users[i].login)==0) {
                    send(server, msg_pas1, strlen(msg_pas1),0);
                }
            }



    }

    int read_users()
    {
        string s;
        fstream myfile;
        struct user client;
        int i =0;
        setlocale(LC_ALL, "rus");
        myfile.open("users_list.txt", ios::in);
        if (!myfile)
        {
            cout << "users_list not open" << endl;
            return -1;
        }
        while (myfile.peek() != EOF) {
            getline(myfile, s);
            if (s.compare(";")==0)
            {
                break;
            }
            size_t find1 = s.find(':')+1;
            size_t find2 = s.find(';');
            size_t found = find2-find1;
            if (i==0) {
                num_of_users = atoi(s.substr(find1, found).c_str());
            }
            else
                if (i % 2 == 1)
                    client.login = s.substr(find1, found);
                else
                {
                    client.password = s.substr(find1, found);
                    users.push_back(client);
                }
        }
        myfile.close();
        return 0;
    }
};

#endif // SERVER_H

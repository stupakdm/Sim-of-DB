#include "network_communicate.h"
using namespace std;

void network_communicate::intHandler(int dummy)
{
    if (connectfl == true)
    {
        char msg_end[] = "\0";
        send(socketfd, msg_end, strlen(msg_end), 0);
        close(socketfd);
    }
    exit(1);
}

int network_communicate::create_user()
{
    int c;
    char k;
    string login, pass;
    string mess;
    while (1){

        c = getch();
        k = (char)c;
        //cout << endl <<k << endl <<"> ";
        if (k == '\n')
        {
            memcpy(buf, login.c_str(), login.size());
            send(socketfd, buf, bufsize, 0);
            memset(buf, 0, bufsize);
            recv(socketfd, buf, bufsize, 0);
            mess = string(buf);
            if (mess == "This name has already been used. Please, enter another: ")
            {

                continue;
            }
            else
            {
                memset(buf, 0, bufsize);
                break;
            }
        }

        special_functions
}

int network_communicate::login_user()
{

}


network_communicate::network_communicate()
{
    //struct hostent* pthr;
    string ip = "127.0.0.1";
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd < 0)
    {
        perror("Socket error");
        exit(1);
    }


    if (inet_pton(AF_INET, ip_add, &client_addr.sin_addr) <=0)
        {
            cout << "Error in IP transmision" << endl;
            exit(1);
        }

    //strcpy(ip_add, ip.c_str());
    //client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(portnum);

    //pthr = gethostbyaddr((char*) &client_addr.sin_addr, sizeof(client_addr.sin_addr), client_addr.sin_family);
    //memcpy(&client_addr.sin_addr, pthr->h_addr, pthr->h_length);
    //client_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//htonl(INADDR_LOOPBACK);  //
    //client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    size_client = sizeof(client_addr);

    if (connect(socketfd, (struct sockaddr*)&client_addr, size_client) == 0) {
        cout << "Connecting to server..." << endl;
        connectfl = true;
    }
    /*else {
        cout << "Error: connecting to server" << endl;
        exit(1);
    }*/

    /*if (bind(socketfd, (struct sockaddr*)&client_addr, size)<0)
    {
        cout << "Error binding socket.." << endl;
        exit(1);
    }*/

    cout << 1 << endl;
    recv(socketfd, buf, bufsize, 0);
    cout << buf;
    close(socketfd);
    //create_user();
    exit(1);

}



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

//Доделать эту функцию, инит, логин, креат
string network_communicate::write_message(string begin, bool use) {
    int c;
    char k;
    int err;
    string mess;
    while (1){

        c = getch();
        k = (char)c;
        //cout << endl <<k << endl <<"> ";
        if (k == '\n')
        {
            mess.push_back(k);
            cout << endl;
            return mess;

        }

        if (iscntrl(k))
        {
            //printf("%d\n", k);
            err = check_symbol(c);
            if (err == -2) {
                mess = mess.substr(0, mess.size()-1);
                print(mess, begin, use);
            }
        }
        else {
            //cout << k;

            mess.push_back(k);
            print(mess, begin, use);
        }
    }
}




int network_communicate::create_user()
{

    string mess, beg;
    char msg_name1[] = "Please, enter your name: ";
    char msg_name2[] = "This name has already been used. Please, enter another: ";
    char msg_password[] = "Please, enter your password: ";
    char cnf_password[] = "Confirm your password: ";
    char not_confirmed[] = "Incorrect password.\nClose  connection\n";
    char msg_begin[] = "Begin session\n";

    //login
    beg = string(msg_name1);
    while (1==1) {
        mess = write_message(beg, false);
        memset(buf,0,bufsize);
        memcpy(buf, mess.c_str(), mess.size());
        send(socketfd, buf, bufsize, 0);

        memset(buf,0,bufsize);
        recv(socketfd, buf, bufsize, 0);

        mess = string(buf);
        cout << mess;

        if (mess == msg_name2)
        {
            beg = mess;
            continue;
        }
        if (mess == msg_password) {
            beg = mess;
            break;
        }
    }

    //pasword
    mess = write_message(beg, true);
    memset(buf, 0, bufsize);
    memcpy(buf, mess.c_str(), mess.size());
    send(socketfd, buf, bufsize, 0);

    memset(buf, 0, bufsize);
    recv(socketfd, buf, bufsize, 0);

    mess = string(buf);
    beg = mess;
    cout << mess;

    while (1==1) {
        mess = write_message(beg,true);
        memset(buf, 0, bufsize);
        memcpy(buf, mess.c_str(), mess.size());
        send(socketfd, buf, bufsize, 0);

        memset(buf, 0, bufsize);
        recv(socketfd, buf, bufsize, 0);

        mess = string(buf);

        if (mess == not_confirmed)
        {
            close(socketfd);
            exit(1);
        }
        if (mess == msg_begin) {
            break;
        }
    }
    return 0;

}

int network_communicate::login_user()
{
    char msg_log1[] = "Please, enter your login: ";
    char msg_log_end[] = "Incorrect login\nEnd of a session\n";
    char msg_log2[] = "Incorrect login\nEnter login: ";

    char msg_pas1[] = "Enter password: ";
    char msg_pas_end[] = "Incorrect password\nEnd of a session\n";
    char msg_pas2[] = "Incorrect password\nEnter password: ";

    char msg_begin[] = "Begin session\n";
    string mess, beg;
    beg = string(msg_log1);

    //login
    mess = write_message(beg, false);
    memset(buf,0,bufsize);
    memcpy(buf, mess.c_str(), mess.size());
    send(socketfd, buf, bufsize, 0);

    memset(buf,0,bufsize);
    recv(socketfd, buf, bufsize, 0);

    mess = string(buf);
    cout << mess;
    if (mess == msg_log_end)
    {
        close(socketfd);
        exit(1);
    }

    //password
    beg = mess;
    mess = write_message(beg, true);
    memset(buf,0,bufsize);
    memcpy(buf, mess.c_str(), mess.size());
    send(socketfd, buf, bufsize, 0);

    memset(buf,0,bufsize);
    recv(socketfd, buf, bufsize, 0);

    mess = string(buf);
    cout << mess;
    if (mess == msg_pas_end)
    {
        close(socketfd);
        exit(1);
    }
    return 0;

}

int network_communicate::init_talking()
{
    int err = 0;
    char msg_welcome[] = "Welcome to AIA database\nEnter 'create' to create new account or 'login' to login: ";
    char msg_end[] = "Incorrect command\nEnd of a session\n";
    char msg_name1[] = "Please, enter your name: ";
    char msg_log1[] = "Please, enter your login: ";
    string choice;
    choice = write_message(msg_welcome, false);
    cout << choice << endl;
    memcpy(buf, choice.c_str(), choice.size());
    send(socketfd, buf, bufsize, 0);
    memset(buf, 0, choice.size());

    recv(socketfd, buf, bufsize, 0);
    choice = string(buf);
    cout << choice;
    if (msg_end == choice)
    {
        //char msg_end[] = "\0";
        //send(socketfd, msg_end, strlen(msg_end), 0);
        close(socketfd);
        exit(1);
    }
    if (choice == msg_name1)
    {
        err = create_user();
    }
    if (choice == msg_log1)
    {
        err = login_user();
    }
    return err;

}


int network_communicate::start_connection()
{
    //struct hostent* pthr;
    string ip = "127.0.0.1";
    //char msg_welcome[] = "Welcome to AIA database\nEnter 'create' to create new account or 'login' to login: ";
    //char msg_end[] = "Incorrect command\nEnd of a session\n";    //ALL IN ALL DB
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
    memset(buf,0,bufsize);
    init_talking();
    return 0;

}



#include "server.h"

using namespace std;

//void quicksort(vector<struct user>& s_arr, int first, int last);

//int binary_search(vector<struct user> s_arr, string login);

Server::Server(int num_of_clients) {
        //Создаётся неименованный сокет(то есть без ip, порта)
        int err;
        ip = "127.0.0.1";
        pid_t pid1, pid2;
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
        //server_addr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);//inet_addr(ip.c_str());//htonl(INADDR_ANY);
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
        //sock_serv.push_back(sockfd);

        while (true) {

            //for (int i=0; i < (int)sock_serv.size(); i++){
            //    if (sock_serv[i] == sockfd)
            //    {
              servfd = accept(sockfd, (struct sockaddr*)&server_addr, &size);

              if (servfd<0)
              {
                    cout << "Error on accepting..." << endl;
                    exit(1);
              }
              //sock_serv.push_back(servfd);
              pid1 = fork();
              if (pid1 == -1) {
                //for (int j =0; j < sock_serv.size(); j++)
                //    close(sock_serv[j]);
                close(sockfd);
                close(servfd);
                perror("fork");
                exit(1);
              }
              if (pid1 == 0) {
                    close(sockfd);
                    //end_connection(sockfd);
                    err = init_connect(servfd);
              }
              else {
                  close(servfd);
                  //bzero((struct sockaddr*) &server_addr,  size);
                  //end_connection(servfd);
              }
                    //err = init_connect(servfd);
            //    }
             //   else
             //   {
                    //client_part all other clients who already on server and begin communication
             //   }
            //}
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

int Server::init_connect(int server) {
            char msg_welcome[] = "Welcome to AIA database\nEnter 'create' to create new account or 'login' to login: ";
            char msg_end[] = "Incorrect command\nEnd of a session\n";    //ALL IN ALL DB
            //send(server, msg_welcome, strlen(msg_welcome), 0);
            send_msg(server, msg_welcome, '1');
            //memset(buffer, 0, bufsize);
            if (recv_msg(server) < 0) {
                end_connection(server);
                return -1;
            }

            //recv(server, buffer, bufsize, 0);
            //cout << buffer;
            //cout << buffer << endl;;
            string s = string(buffer);
            cout << s << endl;
            //s = s.substr(2, s.size()-3);
            s = s.substr(0, s.size()-1);
            cout << s << endl;

            if (s.compare("create") == 0)
            {
                create_new_user(server);
            }
            else if (s.compare("login") == 0)
            {
                return login_user(server);
            }
            else {
                send_msg(server, msg_end, '-');
                //send(server, msg_end, strlen(msg_end), 0);
                end_connection(server);
                //close(server);
                //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
            }

            return 0;
            /*for (int i =0; i<num_of_users;i++)
            {
                if (s.compare(users[i].login)==0) {
                    send(server, msg_end, strlen(msg_end),0);
                }
                else {
                    send(server)
                }
            }*/



}


//Сделать запись в файл по алфавиту, чтобы поиск можно было нормальный организовать или потом после упорядочить
int Server::create_new_user(int server)
{
        char msg_name1[] = "Please, enter your name: ";
        char msg_name2[] = "This name has already been used. Please, enter another: ";
        char msg_password[] = "Please, enter your password: ";
        char cnf_password[] = "Confirm your password: ";
        char not_confirmed[] = "Incorrect password.\nClose  connection\n";
        char msg_begin[] = "Begin session\n";
        //struct termios oldattr, newattr;

        //int rc;

        send_msg(server, msg_name1, '1');
        if (recv_msg(server) < 0) {
            end_connection(server);
            return -1;
        }
        //send(server, msg_name1, strlen(msg_name1), 0);
        //memset(buffer, 0, bufsize);
        //recv(server, buffer, bufsize, 0);
        string name = buffer;
        //name = name.substr(2, name.size()-3);
        name = name.substr(0, name.size()-1);
        cout << name;                //Изменить на бинарный поиск
        int place = binary_search(users, name);
        while (place != -1)
        {
            send_msg(server, msg_name2, '1');
            if (recv_msg(server) < 0) {
                end_connection(server);
                return -1;
            }
            //send(server, msg_name2, strlen(msg_name2), 0);
            //memset(buffer, 0, bufsize);
            //recv(server, buffer, bufsize, 0);
            name = buffer;
            //name = name.substr(2, name.size()-3);
            name = name.substr(0, name.size()-1);
            place = binary_search(users, name);
        }
        /*while (i<(int)users.size()){
            cout << users[i].login;

            while (name == users[i].login) {
                send(server, msg_name2, strlen(msg_name2), 0);
                memset(buffer, 0, bufsize);
                recv(server, buffer, bufsize, 0);
                name = buffer;
                name = name.substr(0, name.size()-1);
                i=-1;
            }
            i++;

        }*/

        send_msg(server, msg_password, '1');

        if (recv_msg(server) < 0) {
            end_connection(server);
            return -1;
        }
        //send(server, msg_password, strlen(msg_password), 0);
        //memset(buffer, 0, bufsize);
        //recv(server, buffer, bufsize, 0);

        string password = buffer;
        //password = password.substr(2, password.size()-3);
        password = password.substr(0, password.size()-1);

        send_msg(server, cnf_password, '1');
        if (recv_msg(server) < 0) {
            end_connection(server);
            return -1;
        }
        //send(server, cnf_password, strlen(cnf_password), 0);
        //memset(buffer, 0, bufsize);
        //recv(server, buffer, bufsize, 0);
        string confirm = buffer;
        //confirm = confirm.substr(2, confirm.size()-3);
        confirm = confirm.substr(0, confirm.size()-1);

        string st;
        //int i =0;
        if (confirm == password)
        {
            fstream myfile;
            setlocale(LC_ALL, "ru");
            myfile.open("/home/force/Project(не трогать)/Socket/users_list.txt", ios::app);
            if (!myfile)
            {
                cout << "users_list not open" << endl;
                return -1;
            }
            myfile << "user:" << name << ";\n";
            myfile << "password:" << password << ";\n";

            myfile.close();

            myfile.open("/home/force/Project(не трогать)/Socket/num_of_users.txt", ios::in);
            if (!myfile)
            {
                cout << "users_list not open" << endl;
                return -1;
            }
            int num;
            getline(myfile, st);
            num = atoi(st.c_str());
            //myfile << num+1;
            myfile.close();

            myfile.open("/home/force/Project(не трогать)/Socket/num_of_users.txt", ios::out | ios::trunc);
            if (!myfile)
            {
                cout << "users_list not open" << endl;
                return -1;
            }
            myfile << num+1;
            myfile.close();


            struct user client;
            client.login =  name;
            client.password = pass_coder(password, 2);;
            client.active = true;

            users.push_back(client);
            quicksort(users, 0, users.size()-1);
            send_msg(server, msg_begin, '1');
            //send(server, msg_begin, strlen(msg_begin), 0);
            return 0;
        }
        else {
            send_msg(server, not_confirmed, '-');
            //send(server, not_confirmed, strlen(not_confirmed), 0);
            end_connection(server);
            //close(server);
            //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
            return -1;
        }
        /*  только в клиенте у себя высталяется такой мод
         rc = tcgetattr( STDIN_FILENO, &oldattr);
        if (rc) {
            perror("tcgetattr");
            exit(1);
        }

        newattr = oldattr;
        newattr.c_lflag = ~(ECHO);//~( ICANON | ECHOCTL);
        rc = tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        if (rc) {
                perror("tcgetattr");
                exit(1);
        }
        */
        return 0;



}

int Server::login_user(int server) {
        char msg_log1[] = "Please, enter your login: ";
        char msg_log_end[] = "Incorrect login\nEnd of a session\n";
        char msg_log2[] = "Incorrect login\nEnter login: ";

        char msg_pas1[] = "Enter password: ";
        char msg_pas_end[] = "Incorrect password\nEnd of a session\n";
        char msg_pas2[] = "Incorrect password\nEnter password: ";

        char msg_begin[] = "Begin session\n";
        send_msg(server, msg_log1, '1');
        if (recv_msg(server) < 0) {
            end_connection(server);
            return -1;
        }
        //send(server, msg_log1, strlen(msg_log1), 0);
        //memset(buffer, 0, bufsize);
        //recv(server, buffer, bufsize, 0);

        //cout << buffer;
        string s = buffer;

        //s = s.substr(2, s.size()-3);
        s = s.substr(0, s.size()-1);
        cout << "login: " <<  s << endl;                  //Изменить на бинарный поиск
        int place = binary_search(users, s);
        if (place == -1) {
            send_msg(server, msg_log_end, '-');
            //send(server, msg_log_end, strlen(msg_log_end), 0);
            end_connection(server);
            //close(server);
            //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
            return -1;
        }
        else
        {
            send_msg(server, msg_pas1,'1');
            if (recv_msg(server) < 0) {
                end_connection(server);
                return -1;
            }
            //send(server, msg_pas1, strlen(msg_pas1),0);
            //memset(buffer, 0, bufsize);
            //recv(server, buffer, bufsize, 0);

            s = string(buffer);
            //s = s.substr(2, s.size()-3);
            s = s.substr(0, s.size()-1);
            cout << "password: " << s << endl;
            if (s == pass_decoder(users[place].password, 2))
            {
                users[place].active = true;
                send_msg(server, msg_begin, '1');
                //send(server, msg_begin, strlen(msg_begin), 0);
                return 0;
            }
            else {
                send_msg(server, msg_pas_end, '-');
                //send(server, msg_pas_end, strlen(msg_pas_end), 0);
                end_connection(server);
                //close(server);
                //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
                return -1;
            }
        }
        /*for (int i =0; i<num_of_users;i++)
        {
            if (s == users[i].login) {
                send(server, msg_pas1, strlen(msg_pas1),0);
                memset(buffer, 0, bufsize);
                recv(server, buffer, bufsize, 0);

                s = string(buffer);
                s = s.substr(0, s.size()-1);
                if (s == users[i].password)
                {
                    send(server, msg_begin, strlen(msg_begin), 0);
                    return 0;
                }
                else {
                    send(server, msg_pas_end, strlen(msg_pas_end), 0);
                    close(server);
                    sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
                    return -1;
                }
            }
            else {
                send(server, msg_log_end, strlen(msg_log_end), 0);
                close(server);
                sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
                return -1;
            }
        }*/
        send_msg(server, msg_log_end, '-');
        //send(server, msg_log_end, strlen(msg_log_end), 0);
        end_connection(server);
        //close(server);
        //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
        return -1;
}

int Server::send_msg(int client_fd, string message, char flag)
{
    packet = make_packet(message, flag);
    memset(buffer,0,bufsize);
    memcpy(buffer, packet.c_str(), packet.size());
    send(client_fd, buffer, bufsize, 0);

}

int Server::recv_msg(int client_fd)
{
    memset(buffer,0,bufsize);
    recv(client_fd, buffer, bufsize, 0);
    cout << buffer;
    string mess = string(buffer);
    if (mess.size() < 2){
        return -1;
    }
    char symb = mess[0];
    mess = mess.substr(2, mess.size()-3);
    switch (symb)   //Доделать
    {
        case '1':
            //mess = mess.substr(2, mess.size()-3);
            cout << mess;
            memset(buffer, 0 ,bufsize);
            memcpy(buffer, mess.c_str(), mess.size());
            return 0;
        case '-':
            return -1;
        default:
            return -1;
    }
    //mess = mess.substr(2, mess.size()-3);
    cout << mess;
    return 0;
}

int Server::end_connection(int fd)
{
    send_msg(fd, "Bye", '-');
    close(fd);
    //sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), fd), sock_serv.end());
}



int Server::read_users()
{
        string s;
        fstream myfile;
        struct user client;
        int i =0;
        setlocale(LC_ALL, "ru");
        /*myfile.open("/home/force/Project(не трогать)/Socket/users_list.txt", fstream::in);
        if (!myfile)
        {
            cout << "users_list not open" << endl;
            return -1;
        }*/
        //read ammount of users
        myfile.open("/home/force/Project(не трогать)/Socket/num_of_users.txt", fstream::in);
        if (!myfile)
        {
            cout << "num_of_users not open" << endl;
            return -1;
        }
        getline(myfile, s);
        num_of_users = atoi(s.c_str());
        myfile.close();

        myfile.open("/home/force/Project(не трогать)/Socket/users_list.txt", fstream::in);
        if (!myfile)
        {
            cout << "users_list not open" << endl;
            return -1;
        }
        int j=0;
        while (myfile.peek() != EOF) {
            getline(myfile, s);
            //cout << s << endl;
            if (j == num_of_users)
            {
                break;
            }
            size_t find1 = s.find(':')+1;
            size_t find2 = s.find(';');
            size_t found = find2-find1;
            /*if (i==0) {
                num_of_users = atoi(s.c_str());//atoi(s.substr(find1, found).c_str());
                j = 0;
            }*/
            if (i % 2 == 0)
            {
                client.login = s.substr(find1, found);
            }
            else
            {
                client.password = pass_coder(s.substr(find1, found), 2);
                client.active = false;
                users.push_back(client);
                j++;
            }
            i+=1;
        }
        cout << users.size() << endl;
        quicksort(users, 0, users.size()-1);
        //if (users[4].login > users[5].login)
         //   cout << 'okay';

        for (int i =0;i<(int)users.size();i++)
        {
            cout << users[i].login <<  endl;
        }
        //cout << users.size() << endl;
        myfile.close();
        return 0;
}

#include "server.h"

using namespace std;

//void quicksort(vector<struct user>& s_arr, int first, int last);

//int binary_search(vector<struct user> s_arr, string login);

Server::Server(int num_of_clients) {
        //Создаётся неименованный сокет(то есть без ip, порта)
        int err;
        ip = "127.0.0.1";
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
        sock_serv.push_back(sockfd);

        while (true) {

            for (int i=0; i < (int)sock_serv.size(); i++){
                if (sock_serv[i] == sockfd)
                {
                    servfd = accept(sockfd, (struct sockaddr*)&server_addr, &size);
                    if (servfd<0)
                    {
                        cout << "Error on accepting..." << endl;
                        exit(1);
                    }
                    sock_serv.push_back(servfd);
                    err = init_connect(servfd);
                }
                else
                {
                    //client_part all other clients who already on server and begin communication
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

int Server::init_connect(int server) {
            char msg_welcome[] = "Welcome to AIA database\nEnter 'create' to create new account or 'login' to login: ";
            char msg_end[] = "Incorrect command\nEnd of a session\n";    //ALL IN ALL DB
            send(server, msg_welcome, strlen(msg_welcome), 0);
            memset(buffer, 0, bufsize);
            recv(server, buffer, bufsize, 0);

            //cout << buffer << endl;;
            string s = string(buffer);
            cout << s << endl;
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
                send(server, msg_end, strlen(msg_end), 0);
                close(server);
                sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
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
        char msg_password[] = "Plese, enter your password: ";
        char cnf_password[] = "Confirm your password: ";
        char not_confirmed[] = "Incorrect password.\nClose  connection\n";
        char msg_begin[] = "Begin session\n";
        //struct termios oldattr, newattr;

        //int rc;

        send(server, msg_name1, strlen(msg_name1), 0);
        memset(buffer, 0, bufsize);
        recv(server, buffer, bufsize, 0);
        string name = buffer;
        name = name.substr(0, name.size()-1);
        cout <<name;                //Изменить на бинарный поиск
        int place = binary_search(users, name);
        while (place != -1)
        {
            send(server, msg_name2, strlen(msg_name2), 0);
            memset(buffer, 0, bufsize);
            recv(server, buffer, bufsize, 0);
            name = buffer;
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

        send(server, msg_password, strlen(msg_password), 0);
        memset(buffer, 0, bufsize);
        recv(server, buffer, bufsize, 0);
        string password = buffer;
        password = password.substr(0, password.size()-1);

        send(server, cnf_password, strlen(cnf_password), 0);
        memset(buffer, 0, bufsize);
        recv(server, buffer, bufsize, 0);
        string confirm = buffer;
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
            send(server, msg_begin, strlen(msg_begin), 0);
            return 0;
        }
        else {
            send(server, not_confirmed, strlen(not_confirmed), 0);
            close(server);
            sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
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
        send(server, msg_log1, strlen(msg_log1), 0);
        memset(buffer, 0, bufsize);
        recv(server, buffer, bufsize, 0);

        cout << buffer;
        string s = buffer;
        s = s.substr(0, s.size()-1);
        cout << s;                  //Изменить на бинарный поиск
        int place = binary_search(users, s);
        if (place == -1) {
            send(server, msg_log_end, strlen(msg_log_end), 0);
            close(server);
            sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
            return -1;
        }
        else
        {
            send(server, msg_pas1, strlen(msg_pas1),0);
            memset(buffer, 0, bufsize);
            recv(server, buffer, bufsize, 0);

            s = string(buffer);
            s = s.substr(0, s.size()-1);
            if (s == pass_decoder(users[place].password, 2))
            {
                users[place].active = true;
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
        send(server, msg_log_end, strlen(msg_log_end), 0);
        close(server);
        sock_serv.erase(remove(sock_serv.begin(), sock_serv.end(), server), sock_serv.end());
        return -1;
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

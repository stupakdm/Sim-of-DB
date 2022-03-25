#include "terminal.h"
#include <signal.h>
using namespace std;

//static volatile int keepRunning = 1;
//struct termios orig_mode;

//void disableRawMode();
//void enableRawMode();

void intHandler(int dummy)
{
    cout << "\nExit" << endl;
    exit(1);

}

Terminal::Terminal()
{
    //ПЕРЕДЕЛАТЬ
    signal(SIGINT, intHandler);
    int err;

    if (communication.start_connection() < 0)
        exit(1);
    //communication.socketfd;


    cout << "Start session" << endl << "> ";
    used_commands.current= 0;
    used_commands.commands.push_back("");
    used_commands.x = 0;
    s = "";
    one_side= "";
    two_side = "";
}

int Terminal::shell() {
    int c, err;
    char k;

    while (1){

        c = getch();
        k = (char)c;
        //cout << endl <<k << endl <<"> ";
        if (k == '\n') {
            if (used_commands.current == (int)used_commands.commands.size() - 1)
            {
                used_commands.commands[used_commands.current] = s;
                used_commands.current++;
                used_commands.commands.push_back("");
            }
            else
                used_commands.commands[used_commands.current] = s;
            //used_commands.commands[used_commands.current] = s;
            s = one_side + two_side;
            err = parse_string();
            if (err < 0)
            {
                cout  << "Error";
                //return -1;
            }
            if (err == 5)
            {
                cout << endl << "End of a session\n";
                return 0;
            }

            s.clear();
            one_side.clear();
            two_side.clear();
            used_commands.x = 0;
            cout << "\n\r> ";
        }
        if (iscntrl(k))
        {
            //printf("%d\n", k);
            err = parse_symb(c);
        }
        else {
            //cout << k;

            one_side.push_back(k);
            print();

        }
    }
    return 0;

}

int Terminal::parse_string(void)
{

    int flag = 0;
    int err;
    string arg;
    struct command prob_comm;
    prob_comm.num_of_args=0;

    for (int i=0; i< (int)s.size(); i++) {
        if (s[i] == ' ' && flag == 1)
        {
            prob_comm.num_of_args++;
            prob_comm.args.push_back(arg);
            arg.clear();
            flag = 0;
            continue;

        }
        if (s[i] == ' ')
            flag = 0;
        else
            flag = 1;


        if (flag == 1) {
            arg.push_back(s[i]);
        }
    }
    if (arg.size() != 0)
    {
        prob_comm.num_of_args++;
        prob_comm.args.push_back(arg);
        arg.clear();
    }


    //for (int i=0;i<prob_comm.num_of_args;i++)
    //    cout << endl << prob_comm.args[i];
    //Code for checking command
    err = check_command(prob_comm);
    switch (err) {
        case -1:
            printf("No such command\n");
               return -1;
        case -2:
            printf("Invalid arguments\n");
            return -2;
        case -3:
            printf("Too much arguments\n");
            return -3;
        case -4:
            printf("Not enough arguments\n");
            return -4;
        case 0:
            return 0;
        case 5:
            return 5;
    }
    return 0;
}

int Terminal::parse_symb(int symb) {

    int err;
    if (symb == 9) {
            //check_special_words   //Функция ищет все совпадения по символам строки
        cout << '\n' << "ls    help\nclear exit\n> ";
        print();
    }
    if (symb == 8 or symb == 127) {
        if (one_side.size()!=0)
            one_side = one_side.substr(0, one_side.size()-1);

        //cout << endl << one_side << endl;
        //cout << s;
        //printf("\033[2K");
        print();
        //used_commands.x--;
        //cout << "\r> " << s;
    }

    if (symb == 27)
    {

        symb = getch();
        if (symb == 91) {

            symb = getch();
            switch (symb){
                case 65:
                    if (used_commands.current != 0) {
                        //cout << used_commands.current << endl;
                        //cout << (int)used_commands.commands.size() << endl;
                        used_commands.current--;
                        //s = used_commands.commands[used_commands.current];
                        //used_commands.current--;
                    }
                    else {
                        used_commands.current = 0;
                        //s.clear();
                    }
                    s = used_commands.commands[used_commands.current];
                    printf("\033[2K");
                    cout << "\r> " << s;
                    one_side = s;
                    two_side = "";
                    used_commands.x = 0;
                    break;
                case 66:
                    if (used_commands.current != (int)used_commands.commands.size()-1) {
                        used_commands.current++;
                        //s = used_commands.commands[used_commands.current];
                    }
                    else {
                        used_commands.current = (int)used_commands.commands.size()-1;
                        //s.clear();
                    }
                    s = used_commands.commands[used_commands.current];
                    printf("\033[2K");
                    cout << "\r> " << s;
                    one_side = s;
                    two_side = "";
                    used_commands.x = 0;
                    break;
                case 67:
                    if (used_commands.x != 0) {
                        used_commands.x--;

                        printf("\033[1C");
                    }
                    else {
                        used_commands.x = 0;
                    }
                    if (s.size() != 0) {

                        one_side = s.substr(0, s.size() - used_commands.x);
                        if (used_commands.x != 0 )
                            two_side = s.substr(s.size() - used_commands.x, used_commands.x);
                        else
                            two_side = "";
                    }
                    break;
                case 68:
                    if (used_commands.x <= (int)s.size() -1) {
                        used_commands.x++;
                        printf("\033[1D");
                    }
                    else {
                        if (s.size() != 0)
                            used_commands.x = (int)s.size();
                        else
                            used_commands.x =0;
                    }
                    if (s.size() != 0) {
                        one_side = s.substr(0, s.size() - used_commands.x);
                        two_side = s.substr(s.size() - used_commands.x, used_commands.x);
                        //cout << "checking:" << one_side << " and " << two_side;
                    }
                    //printf("\033[1D");
                    //cout << "left" << endl;
                    break;
                default:
                    parse_symb(symb);
                    break;

            }

            return 1;
        }
        else {
            parse_symb(symb);
        }

    }
    if (symb>=32 and symb<127)
        return 0;
    return 1;

}



void Terminal::print(void) {
    printf("\033[2K");
    cout << "\r> " << one_side << two_side;
    if (used_commands.x != 0)
        printf("\033[%dD", used_commands.x);
    s = one_side+two_side;
}

int Terminal::getch(void) {
    struct termios oldattr, newattr;
    int ch, rc;
    rc = tcgetattr( STDIN_FILENO, &oldattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);

    rc = tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }

    system("stty -echo");
    ch = getchar();
    system("stty echo");

    rc = tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }
    return ch;
}

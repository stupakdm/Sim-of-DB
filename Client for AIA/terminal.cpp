#include "terminal.h"
using namespace std;

//struct termios orig_mode;

//void disableRawMode();
//void enableRawMode();

Terminal::Terminal()
{
    cout << "Start session" << endl << "> ";
    used_commands.current= 0;
    used_commands.commands.push_back("");
}

int Terminal::shell() {
    int c, err;
    char k;
    //enableRawMode();
    //string s;
    //used_commands.current= 0;
    //cout << "Start session" << endl << "> ";
    cout << used_commands.current << endl;
    cout << (int)used_commands.commands.size() << endl;
    while (1){
        //c = getchar();

        c = getch();
        k = (char)c;
        //cout << endl <<k << endl <<"> ";
        if (k == '\n') {
            used_commands.commands[used_commands.current] = s;
            used_commands.current++;
            cout << used_commands.current << endl;
            cout << (int)used_commands.commands.size() << endl;
            err = parse_string(s);
            s.clear();
            cout << "\r> ";
            if (err == 5)
                return 0;
            if (err == -1) {
                printf("Error\n");
                return -1;
            }
        }
        if (iscntrl(k))
        {
            //printf("%d\n", k);
            err = parse_symb(c);
            //cout << k;
            //s.push_back(k);
        }
        else {
            //printf("%d\n", k);
            //printf("%c", k);
            cout << k;
            s.push_back(k);
        }
        /*err = parse_symb(k);
        if (err == 0) { //0 - Обычный символ, 1 - служебный символ
            s.push_back(k);

        }*/
        //cout << "< ";

    }
    return 0;

}

int Terminal::parse_string(string s)
{
    cout << endl << s << endl;
    return 0;
}

int Terminal::parse_symb(int symb) {

    int err;
    //printf("%d\n", symb);
    if (symb == 9) {
            //check_special_words   //Функция ищет все совпадения по символам строки
        cout << '\n' << "ls    help\nclear exit\n> " << s;
    }
    if (symb == 8 or symb == 127) {
        if (s.size()!=0)
            s = s.substr(0, s.size()-1);
        //cout << s;
        printf("\033[2K");
        cout << "\r> " << s;
    }
    /*if (symb == 127) {
        if (s.size()!=0)
            s = s.substr(0, s.size()-1);
        cout << "\r> " << s;
    }*/
    if (symb == 27)
    {
        //cout << "\r> " << s;
        /*struct timeval begin, end;
        gettimeofday(&begin, 0);

        read(STDIN_FILENO, &symb, 1);
        gettimeofday(&end, 0);
        long double microseconds = end.tv_usec - begin.tv_usec;
        if (microseconds < 0.000001) {
            //cout << "\r> " << s;
        }*/
        symb = getch();
        if (symb == 91) {
            /*gettimeofday(&begin, 0);

            read(STDIN_FILENO, &symb, 1);
            gettimeofday(&end, 0);
            long double microseconds = end.tv_usec - begin.tv_usec;
            if (microseconds < 0.000001) {
                //cout << "\r> " << s;
            } // Доработать стрелочки*/
            symb = getch();
            switch (symb){
                case 65:
                    if (used_commands.current >= 0) {
                        cout << used_commands.current << endl;
                        cout << (int)used_commands.commands.size() << endl;
                        used_commands.current--;
                        s = used_commands.commands[used_commands.current];
                        //used_commands.current--;
                    }
                    else {
                        s.clear();
                    }
                    printf("\033[2K");
                    cout << "\r> " << s;
                    break;
                case 66:
                    if (used_commands.current < (int)used_commands.commands.size()-1) {
                        used_commands.current++;
                        s = used_commands.commands[used_commands.current];
                    }
                    else {
                        //used_commands.current++;
                        s.clear();
                    }
                    printf("\033[2K");
                    cout << "\r> " << s;
                    break;
                case 67:
                    cout << "right" << endl;
                    break;
                case 68:
                    cout << "left" << endl;
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
/*
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_mode);
}

void enableRawMode() {

    tcgetattr(STDIN_FILENO, &orig_mode);
    atexit(disableRawMode);

    struct termios raw = orig_mode;
    //raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    //raw.c_oflag &= ~(OPOST);
    //raw.c_cflag |= (CS8);
    raw.c_lflag = ~(ECHO | ICANON);
    //raw.c_cc[VMIN] = 0;
    //raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
*/
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

/*int Terminal::getch(void)
{
    struct termios oldattr, newattr;
    int ch, rc;

    rc = tcgetattr( STDIN_FILENO, &oldattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }

    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);//~( ICANON | ECHOCTL);
    rc = tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }
    //fflush(stdout);
    ch = getchar();

    rc = tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    if (rc) {
            perror("tcgetattr");
            exit(1);

    }

    return ch;
}
*/

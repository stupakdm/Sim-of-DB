#include "special_functions.h"
using namespace std;

special_functions::special_functions()
{
}


int special_functions::getch(void) {
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

int special_functions::check_symbol(int symb) {

    int err;
    if (symb == 9) {
        return 1;
    }
    if (symb == 8 or symb == 127) {
        return -2;

        //cout << endl << one_side << endl;
        //cout << s;
        //printf("\033[2K");
        //used_commands.x--;
        //cout << "\r> " << s;
    }

    if (symb == 27)
    {

        symb = getch();
        if (symb == 91) {

            symb = getch();
            switch (symb){
                default:
                    return 0;
                    break;

            }

            return 1;
        }
        else {
            special_functions::check_symbol(symb);
        }

    }
    if (symb>=32 and symb<127)
        return 0;
    return 1;

}

void special_functions::print(string s, string start_text, bool use) {
    printf("\033[2K");
    int n = count(start_text.begin(), start_text.end(), '\n');
    if (n!=0)
        printf("\033[%dA", n);
    cout << "\r" <<start_text;
    if (use == true)
    {
        for (int i =0; i< s.size();i++)
            cout << '*';
    }
    else
        cout << s;

}

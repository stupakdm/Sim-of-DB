#include "special_functions.h"
using namespace std;

special_functions::special_functions()
{
}

int getch(void) {
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
        return 0;
    }
    if (symb == 8 or symb == 127) {
        if (one_side.size()!=0)
            one_side = one_side.substr(0, one_side.size()-1);

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
            check_symb(symb);
        }

    }
    if (symb>=32 and symb<127)
        return 0;
    return 1;

}

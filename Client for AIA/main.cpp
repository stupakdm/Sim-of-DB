#include "terminal.h"
using namespace std;

/*struct termios orig_termios;
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {

    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHOE | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    //printf("\n");
}*/


int main()
{
    //enableRawMode(); //from now Entering symbol by symbol
    int err;

    Terminal Term;
    err = Term.shell();

    if (err != 0)
        cout << "Error" << endl;
    else
        cout << "Session Ended" << endl;
    return err;
}

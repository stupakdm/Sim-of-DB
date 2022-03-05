#ifndef TERMINAL_H
#define TERMINAL_H
//#include <structures.h>
#include "exec_commands.h"
#include "network_communicate.h"
/*#include <cstring>
#include <structures.h>
#include <sys/time.h>
#include <ctype.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "termios.h"
#include "unistd.h"
#include <iostream>*/
using namespace std;

/*struct command {
    int num_of_args;
    vector<string> args;
};

struct used_comm {
    int current;
    int x;
     vector<string> commands;
};*/

class Terminal : public Exec_commands, public network_communicate
{
private:
    struct used_comm used_commands;
    //vector<string> used_commands;
    vector<command> commands;
    command comm;
    string s;
    string one_side, two_side;
    int parse_string(void);

    int parse_symb(int symb);

    int getch(void);

    void print(void);
public:
    Terminal();

    int shell();

    //int parse_string(string s);

    //int parse_symb(int symb, string s);
};

#endif // TERMINAL_H

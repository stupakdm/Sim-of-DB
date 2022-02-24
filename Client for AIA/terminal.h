#ifndef TERMINAL_H
#define TERMINAL_H
#include <string>
#include <cstring>
#include <vector>
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
#include <iostream>
using namespace std;

struct command {
    int num_of_args;
    vector<string> args;
};

struct used_comm {
    int current;
     vector<string> commands;
};

class Terminal{
private:
    struct used_comm used_commands;
    //vector<string> used_commands;
    vector<command> commands;
    command comm;
    string s;
    int parse_string(string s);

    int parse_symb(int symb);

    int getch(void);
public:
    Terminal();

    int shell();

    //int parse_string(string s);

    //int parse_symb(int symb, string s);
};

#endif // TERMINAL_H

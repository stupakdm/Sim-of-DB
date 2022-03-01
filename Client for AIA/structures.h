#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <cstring>
#include <vector>
#include <string>
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
#define COMM_NUMS 7
using namespace std;

static const char *COMMANDS[] = {"clean",
                                 "exit",
                                 "help",
                                 "ls",
                                 "SELECT",
                                 "CREATE",
                                 "run"};

static const char* HELP[] = {"clean - очистить окно",
                             "exit - выход",
                             "help - вывести помощь по всем командам",
                             "ls - показать содержимое сесиии пользователя",
                             "SELECT",
                             "CREATE",
                             "run"}; // добавить другие комманды

struct command {
    int num_of_args;
    vector<string> args;
};

struct used_comm {
    int current;
    int x;
     vector<string> commands;
};
#endif // STRUCTURES_H

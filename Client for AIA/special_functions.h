#ifndef SPECIAL_FUNCTIONS_H
#define SPECIAL_FUNCTIONS_H
#include <iostream>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "string.h"
#include "termios.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "structures.h"
#include <iostream>
#include <string>
using namespace std;

int getch(void);


class special_functions
{
    string pass, login;
public:
    special_functions();

    int check_symbol(int symb);

};

#endif // SPECIAL_FUNCTIONS_H

#ifndef ALGORITHMFUNCTIONS_H
#define ALGORITHMFUNCTIONS_H
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sys/types.h>
#include <sys/ioctl.h>
#include "string.h"
#include "termios.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include "structures.h"



class AlgorithmFunctions
{
public:
    AlgorithmFunctions();

    int binary_search(vector<struct user> s_arr, string login);

    void quicksort(vector<struct user>& s_arr, int first, int last);

    string pass_coder(string st, int num);

    string pass_decoder(string st, int num);

    string make_packet(string s,  char type);
};

#endif // ALGORITHMFUNCTIONS_H

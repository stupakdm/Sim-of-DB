#include "Exec_command.h"

#ifndef COMM_H
#define COMM_H

struct command {
//typedef type_command {
	char **args;
	int num_args;
};

//int num_comms;

int check_args(int num, struct command comm, int num_of_comm);

int check_command(struct command comm);
#endif COMM_H

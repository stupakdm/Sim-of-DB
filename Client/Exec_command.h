#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"

#ifndef EXEC_H
#define EXEC_H

int exec_command(int num_of_comm, char* args[]);

#endif EXEC_H

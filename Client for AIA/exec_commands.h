#ifndef EXEC_COMMANDS_H
#define EXEC_COMMANDS_H
#include <structures.h>



class Exec_commands
{

public:
    Exec_commands();

    int exec_command(int num_of_comm, vector<string> args);

    int check_args(struct command comm, int num_of_args);;

    int check_command(struct command comm);
};

#endif // EXEC_COMMANDS_H

#include "exec_commands.h"

Exec_commands::Exec_commands()
{

}

int Exec_commands::exec_command(int num_of_comm, vector<string> args)
{
    //pid_t pid;
    switch(num_of_comm) {
    case 0:
            printf("\033c");
            printf("\033[0;0f");
            break;
    case 1:
            return 5;
    case 2:
            cout << endl;
            if ((int)args.size() >1) {
                for (int i=1;i<(int)args.size();i++)
                    for (int j = 0;j<COMM_NUMS;j++)
                    {
                        if (strcmp(args[i].c_str(), COMMANDS[j]) == 0) {
                            cout << HELP[j];
                            return 0;
                        }
                    }
                cout << "Error: Incorrect args\n";
            }
            for (int i =0;i<COMM_NUMS-1;i++)
            {
                    cout << HELP[i] << endl;
            }
            cout << HELP[COMM_NUMS-1];
            //cout << "clean - очистить окно\nexit - выход\nls - показать содержимое сесиии пользователя\nhelp - вывести помощь по всем командам\n";
            break;
    case 3:   //pid=fork()
            break;
    default:    //SQL commands and else
            break;

    }
    return 0;
}

int Exec_commands::check_args(struct command comm, int num_of_comm)
{
    int err = 0;
    if (num_of_comm == 0 || num_of_comm == 1 || num_of_comm == 3)
    {
        if (comm.num_of_args  == 1 )
        {
            err = exec_command(num_of_comm, comm.args);
            return err;
        }
        else {
            cout << endl << "Error: Incorrect args\n";
            return -1;
        }

    }
    if (num_of_comm == 2)
    {
        if (comm.num_of_args < 3) {
            err = exec_command(num_of_comm, comm.args);
            return err;
        }
        else {
            cout << endl << "Error: Incorrect args\n";
            return -1;
        }

    }
    else {
        return 0;
    }
    return err;

}

int Exec_commands::check_command(struct command comm)
{
    int err;

    for (int i =0;i<COMM_NUMS; i++)
    {
        if (strcmp(comm.args[0].c_str(), COMMANDS[i]) == 0)
        {
           err = check_args(comm, i);
           return err;
        }
    }
    cout << endl <<"Error: Incorrect name of command\n";
    return -1;
}


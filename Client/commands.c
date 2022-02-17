#include "commands.h"

//перечисление всех команд(наверно можно через char* commands[] сделать или как то ещё)
//enum all_commands= {"clean", "exit", "ls", "help"}; //Все команды, будут ещё и ещё 

/*struct command {
//typedef type_command {
	char *name;
	char **args;
	int num_args;
};

//struct command* commands;
int num_comms;
*/
int check_args(int num, struct command comm, int num_of_comm) {
	int err;
	if (num_of_comm==2) {
		comm.args[comm.num_args] = NULL;
		err = exec_command(num_of_comm, comm.args);
		return err;
	}
	if (comm.num_args-1 == num) {
		err = exec_command(num_of_comm, comm.args);
		if (err == 5)
			return 5;
	}
	else {
		printf("Incorrect args\n");
		return -1;
	}
	return err;
}

int check_command(struct command comm) {
	int i, j;
	//char *str;
	int err;
	char* commands[] = {"clean", "exit", "ls", "help"};		
	//Pseudocode
	int all_comms=4;


	//printf("command: %s\n", comm.args[0]);
	for (i=0;i<all_comms;i++) {
		if (strcmp(comm.args[0], commands[i]) == 0) {
			switch (i) {
				case 0:
					err = check_args(0, comm, i);
					break;
				case 1:
					err = check_args(0, comm, i);
					break;

				case 2:
					err = check_args(0, comm, i);
					break;

				case 3:
					err = check_args(0, comm, i);
					break;

			}
			return err;
		}
	}
	printf("Incorrect name of command\n");
	return -1;
}				
					

	 	
	

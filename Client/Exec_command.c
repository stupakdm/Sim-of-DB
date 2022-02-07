#include "Exec_command.h"

int exec_command(int num_of_comm, char* args[])
{
	char *arg_ls[] = {"ls", "-a", "-l"};
	pid_t pid;
	switch (num_of_comm) {
		case 0:
			printf("\033c");
			break;
			//clean printf('') очистить окно
		case 1:
			//exit
			//printf("exit\n");
			//break;
			return 5;
		case 2:
			//ls
			//Вывести содержимое сессии пользователя
			pid = fork();
			if (pid <0) 
			{
				printf("Error Fork\n");
				exit(1);
			}
			else if (pid== 0) // child
			{
				execvp("ls", args);
				printf("I am gone\n");
			}
			else { 		// parent
				wait(0);
				printf("It is parent\n");
			}
			
			printf("ls\n");
			break;
			//execlp("ls","ls", args, NULL);
			//execvp("ls", arg_ls);
		case 3:
			//print вывести помощь по всем командам
			printf("clean - очистить окно\nexit - выход\nls - показать содержимое сесиии пользователя\nhelp - вывести помощь по всем командам\n");
			break;
		}
	return 0;

}

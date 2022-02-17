#include "terminal.h"

//... all includes

int parse_string(char *str){
	int len;
	int i, flag, k, comm_args, err;

	struct command comm;

	char *word = NULL;
	char *word1= NULL;
	word1 = (char*)malloc(sizeof(char));
	if (word1 == NULL)
	{
		printf("Malloc error: terminal\n");
		return -1;
	}
	word = word1;
	comm.num_args = 0;

	comm_args = 0;
	comm.args = NULL;
	len = strlen(str);
	k=0;
	//printf("okay1\n");
	//Задаём аргументы с самого начала и очистим в конце
	comm.args = NULL;
	comm.args = (char**)malloc(sizeof(char*));
	if (comm.args == NULL)
	{
		printf("Malloc Error: terminal.h\n");
		return -1;
	}
	comm.args[comm.num_args] = NULL;
	
	flag = 0;
	for (i=0;i<=len;i++) {
		if (str[i] == '\0') {
			if (strlen(word) >0) {
				flag = 2;
				//printf("okay2\n");
				goto add_new_word;
				}
				
			break;
		}
		if (flag == 0) {
			if (str[i] == ' ' | str[i] == '\t')
				continue;
			else {
				flag = 1;
			}
		}

		if (flag == 1) {
			if (str[i] == ' ' | str[i] == '\t') {
add_new_word:
				word[k] = '\0';
				if (comm.num_args ==0) {
					//printf("okay2\n");
					comm.args[comm.num_args] = (char*)malloc(sizeof(char)*strlen(word));
					//strcpy(comm.args[comm.num_args], word);
					comm.args[comm.num_args] = word;
					
					//printf("args[0]:%s\n", comm.args[comm.num_args]);
					//printf("okay3\n");
				}
				else {
					
					comm.args = (char**)realloc(comm.args, (comm.num_args+1)*sizeof(char*));
					if (comm.args == NULL)
					{
						printf("Malloc Error: terminal.h\n");
						return -1;
					}
					comm.args[comm.num_args] = (char*)malloc(sizeof(char)*(strlen(word));
					//strcpy(comm.args[comm.num_args], word);
					comm.args[comm.num_args] = word;
				}
					

				comm.num_args +=1;

			

				//word1 = NULL;
				word1 = (char*)malloc(sizeof(char));
				if (word1 == NULL) {
					printf("Malloc error: terminal.h\n");
					return -1;
				}
				//printf("args[0]:%s\n", comm.args[comm.num_args-1]);	
				if(flag==2)
					break;
				k= 0;
				word = word1;
				flag = 0;
				//printf("args[0]:%s\n", comm.args[comm.num_args-1]);	
			}
			else {
				//printf("okay4\n");
			
				word1 = (char*)realloc(word, k+1);
				if (word1 == NULL) {
					printf("Realloc error: terminal.h\n");
					return -1;
				}
				word = word1;
				word[k] = str[i];
				k+=1;
				//printf("%s\n", word);
			}
		}
		
	}
	/*if (comm_args==0)
	{
		//free(comm.name);
		free(comm.args[0]);
		free(comm.args);
	}*/

	
	err = check_command(comm);
	
	free(word1);
	printf("%d\n", comm.num_args);
	//if (comm_args!=0) {
		//free(comm.name);
	//if (comm.num_args)
	for (i=0;i<comm.num_args;i++)
	{	
		printf("%s\n", comm.args[i]);
	} 
	//free(comm.args[i]);
	for (i=0;i<comm.num_args;i++) {
		{	
			free(comm.args[i]);
		}
	}
	free(comm.args);
	
	switch (err) {
		case -1:
			printf("No such command\n");
			return -1;
		case -2:
			printf("Invalid arguments\n");
			return -1;
		case -3:
			printf("Too much arguments\n");
			return -1;
		case -4:
			printf("Not enough arguments\n");
			return -1;
		case 0:
			return 0;
		case 5:  //for exit
			return 5;
	}
	return 0;
}
				
				
				
int terminal() {
	char a;
	char *str;
	char *str1 = NULL;
	int n =0;
	int err;
	str1 = (char*)malloc(sizeof(char));
	str = str1;
	//str[n] = '\0';
	printf("> ");
	a = getchar();
	while (1) {
		//a = getchar();
		//str[n]= a;
		/*str1 = (char*)realloc(str,n+1);
		if (str1 == NULL) {
			printf("Realloc Error: terminal.h\n");
			return -1;
		}
		str = str1;  */
		if (a == '\n') {
			str[n] = '\0';
			printf("%s\n", str);
			err = parse_string(str);
			if (err<0) {
				printf("Parse string error\n");
				//return -1;
			}
			if (err == 5) {
				free(str1);
				return 0;
			}
			printf("> ");
			n = 0;
			free(str1);
			//str1 = NULL;
			//str = str1;
			//str1 = (char*)realloc(str, n*(sizeof(char)));
			str1 = (char*)malloc(sizeof(char));
			if (str1 == NULL) {
				printf("Malloc error: terminal\n");
				return -1;
			}
			str = str1;
			//str[n] = '\0';
			a = getchar();
		}
		else {
			
			str[n] = a;
			a = getchar();
			n++;
			if (a == '\n')
				continue; 
			str1 = (char*)realloc(str,n+1);
			if (str1 == NULL) {
				printf("Realloc Error: terminal.h\n");
				return -1;
			}
			str = str1; 
			//n+=1;
		}
		//n+=1;
		
	}
	
	
	return 0;
}
	
			
			

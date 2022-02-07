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

	len = strlen(str);
	k=0;
	printf("okay1\n");
	
		
	flag = 0;
	for (i=0;i<=len;i++) {
		if (str[i] == '\0') {
			if (strlen(word) >0) {
				flag = 2;
				printf("okay2\n");
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
				if (comm_args ==0) {
					comm.name = word;
					comm.num_args = comm_args;
					comm_args+=1;
					//printf("%s\n", comm.name);
					/*word1 = (char*)malloc(sizeof(char));
					if (word1 == NULL) {
						printf("Malloc error: terminal.h\n");
						return -1;
					}
					k= 0;
					word = word1;*/
				}
				else {
					if (comm.num_args ==0) {
						comm.args = (char**)malloc(sizeof(char*));
						if (comm.args == NULL)
						{
							printf("Malloc Error: terminal.h\n");
							return -1;
						}
						comm.args[comm.num_args] = word;
					}
					else {
					
						comm.args = (char**)realloc(comm.args, comm.num_args*sizeof(char*));
						if (comm.args == NULL)
						{
							printf("Malloc Error: terminal.h\n");
							return -1;
						}
						comm.args[comm.num_args] = word;
					}
					
					//printf("ok2.1\n");
					//printf("args %d - %s\n", comm.num_args, comm.args[comm.num_args]);
					comm.num_args +=1;
					//printf("args %d - %s\n", comm.num_args, comm.args[0]);
					/*word1 = (char*)malloc(sizeof(char));
					if (word1 == NULL) {
						printf("Malloc error: terminal.h\n");
						return -1;
					}
					k= 0;
					word = word1;*/
					//comm_args +=1;
				}
				//word = NULL;
				word1 = NULL;
				word1 = (char*)malloc(sizeof(char));
				if (word1 == NULL) {
					printf("Malloc error: terminal.h\n");
					return -1;
				}
				
				if(flag==2)
					break;
				k= 0;
				word = word1;
				flag = 0;
			}
			else {
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
	if (comm_args==0)
	{
		free(comm.name);
		free(comm.args[0]);
		free(comm.args);
	}

	
	err = check_command(comm);
	
	free(word1);
	
	if (comm_args!=0) {
		free(comm.name);
		for (i=0;i<comm.num_args;i++) 
			free(comm.args[i]);
		//free(comm.args);
	}
	
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
	char *str = NULL;
	char *str1;
	int n =0;
	int err;
	str1 = (char*)malloc(sizeof(char));
	str = str1;
	printf("> ");
	while (1) {
		a = getchar();
		str1 = (char*)realloc(str,n+1);
		if (str1 == NULL) {
			printf("Realloc Error: terminal.h\n");
			return -1;
		}
		str = str1;  
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
			str1 = NULL;
			//str1 = (char*)realloc(str, n*(sizeof(char)));
			str1 = (char*)malloc(sizeof(char));
			if (str1 == NULL) {
				printf("Malloc error: terminal\n");
				return -1;
			}
			str = str1;
			continue;
		}
		else {
			str[n] = a;
		}
		n+=1;
	}
	
	
	return 0;
}
	
			
			

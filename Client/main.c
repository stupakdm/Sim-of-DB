/*#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"*/
#include "terminal.h"

int main(int argc, char* argv[]) {
	int err;
	char b;
	

	err = terminal();
	if (err == -1)
	{
		printf("Error\n");
		return -1;
	}
	return 0;
}

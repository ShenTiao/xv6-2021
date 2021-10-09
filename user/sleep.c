#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int arg,char *argv[])
{
	if(arg<2){
		fprintf(2, "Usage: sleep seconds...\n");
		exit(1);
	}
	
	int seconds=atoi(argv[1]);
	
	sleep(seconds);
	exit(0);
}

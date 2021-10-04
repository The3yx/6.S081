#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	if(argc != 2){
		printf("Error parameter, please retype command.\nFor example: sleep 10.\n");
		exit(0);
	}
	
	//The input is passed as a string, which can be converted to an integer using atoi. 
	int time = atoi(argv[1]);

	//No effect code! Because the function atoi will return 0 if the parameter was not a positive integer. 
	if(time < 0){
		printf("Error parameter, please retype command. The input time should be positive.");
		exit(0);
	}

	sleep(time);
	exit(0);

}

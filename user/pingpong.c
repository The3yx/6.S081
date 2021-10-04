#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	char buf[128];
	int p_ptoc[2];
	int p_ctop[2];

	//init the pipe
	//hint:The pipe is an one-way link!
	pipe(p_ptoc);
	pipe(p_ctop);

	if(fork() == 0){
		int pid_c = getpid();

		//read will return till the data coming
		read(p_ptoc[0],buf,1);
		printf("%d: received ping\n",pid_c);
		write(p_ctop[1],buf,1);
		exit(0);
	}
	else{
		int pid_p = getpid();

		write(p_ptoc[1],buf,1);
		read(p_ctop[0],buf,1);
		printf("%d: received pong\n",pid_p);
		exit(0);
	}

}

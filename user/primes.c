#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



void primes(int fd)
{
    //进入这个函数的fd读取的第一个数字是质数
    int first_prime;
    read(fd,&first_prime,4);
    printf("prime %d\n", first_prime);

    int tem;
    int p[2];
    int created = 0;
    int pid;
    while(read(fd,&tem,4) != 0){
        if(created == 0){
            pipe(p);
            created = 1;
            pid = fork();
            if(pid == 0){   //子进程
                close(p[1]);
                primes(p[0]);
                close(p[0]);
            }
            else{           //父进程
                close(p[0]);
            }
        }

        if(tem % first_prime != 0 ){ //筛选到质数
            write(p[1],&tem,4);
        }  

    }
    close(fd);
    close(p[1]);
    wait(0);

}


int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    int pid = fork();

    
    if(pid == 0){   //子进程
        close(p[1]);
        primes(p[0]);
        close(p[0]);

    }
    else{           //父进程
        //给管道写入2-35
        close(p[0]);
        for(int i = 2;i<=35;i++){
            write(p[1],&i,4);
        }
        close(p[1]);
    }

    wait(0);

    return 0;
}
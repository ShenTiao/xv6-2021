#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(){
    int parentFd[2];
    int childFd[2];

    pipe(parentFd);
    pipe(childFd);

    int pid=fork();
    if(pid==0){
        //child process
        close(parentFd[0]);
        close(childFd[1]);
        char buf[4];
        read(childFd[0],buf,4);
        close(childFd[0]);
        fprintf(1,"%d: received ping\n",getpid());
        write(parentFd[1],"pong",4);
        close(parentFd[1]);
        exit(0);
    }
    else if(pid>0){
        char buf[4];
        close(childFd[0]);
        close(parentFd[1]);
        write(childFd[1],buf,4);
        close(childFd[1]);
        read(parentFd[0],buf,4);
        close(parentFd[0]);
        fprintf(1,"%d: received pong\n",getpid());
        wait(&pid);//waiting for child process
    }
    else{
        exit(1);
    }
    exit(0);
}
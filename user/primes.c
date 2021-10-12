#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(){
    int num[36];
    int fd[2];
    int cnt=0;
    for(int i=2;i<=35;i++){
        num[cnt]=i;
        cnt++;
    }
    while(cnt>0){
        pipe(fd);
        //parent process
        int pid=fork();
        if(pid>0){
            close(fd[0]);
            for(int i=0;i<cnt;i++)
                write(fd[1],&num[i],4);
            close(fd[1]);
            wait((int*) 0);
            exit(0);
         }
         //child process
        else if(pid==0){
            int prime=0;
            cnt=-1;
            int first=0;
            close(fd[1]);
            while ((read(fd[0],&first,4))!=0){
                if(cnt==-1){
                    prime=first;
                    cnt++;
                }
                else{
                    if(first%prime!=0){
                    num[cnt]=first;
                    cnt++;
                    }
                } 
            }
            printf("prime %d\n",prime);
            close(fd[0]);
        }
        else exit(1);
    }
    exit(0);
}
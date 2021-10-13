#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc,char* argv[]){
    if(argc<2){
        fprintf(2,"usage: xargs your order\n");
        exit(1);
    }
    //terminating zero
    if(argc+1>MAXARG){
        fprintf(2,"too many args");
        exit(1);
    }
    char* realargc[MAXARG];
    char buf[512];
    //skip xargs
    for(int i=1;i<argc;i++){
        realargc[i-1]=argv[i];
    }
    // \0
    realargc[argc]=0;
    while (1)
    {   
        int cnt=0;
        //read a line
        while (1)
        {
            int length=read(0,&buf[cnt],1);
            if(length==0||buf[cnt]=='\n') break;
            cnt++;
        }
        if(cnt==0) break;
        int pid=fork();
        buf[cnt]=0;
        if(pid==0){
            exec(realargc[0],realargc);
            exit(0);
        }else{
            wait(0);
        }
    }
    exit(0);
}
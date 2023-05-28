#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char* argv[]) {
    if(argc > 1) {
        fprintf(2, "usage: pingpong\n");
        exit(1);
    }
    int p[2];
    pipe(p);
    if(fork() == 0) {
        //子进程
        char buf[1024];
        int ret = read(p[0], buf, sizeof(buf));
        if(ret == 1) {
            printf("%d: received ping\n", getpid());
        }else{
            fprintf(2, "something wrong");
            exit(1);
        }
        write(p[1], buf, ret);
        exit(0);
    }else{
        //父进程
        char c[0];
        strcpy(c, "c");
        write(p[1], c, 1);
        wait(0);
        char buf[1024];
        int ret = read(p[0], buf, sizeof(buf));
        if(ret == 1) {
            printf("%d: received pong\n", getpid());
        }else{
            fprintf(2, "something wrong");
            exit(1);
        }
        close(p[0]);
        close(p[1]);
        exit(0);
    }
}
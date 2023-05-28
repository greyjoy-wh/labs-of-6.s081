#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



int main() {
    int pip[2];
    pipe(pip);
    for(int i =2; i<=35; i++) {
        write(pip[1], &i, sizeof(int));
    }
    int no = -1;
    int son_num = 0;
    write(pip[1], &no, sizeof(int));
    while(fork() == 0) {
        son_num++;
        int p;
        int ret = read(pip[0], &p, sizeof(p));
        if(ret == 0) {
            close(pip[0]);
            close(pip[1]);
            exit(0);
            }
        if(p == -1) {
            exit(0);
        }
        printf("prime %d\n", p);
        int n;
        while(read(pip[0], &n, sizeof(n))) {
            if(n == -1) {
                break;
            }
            if(n % p != 0){
                write(pip[1], &n, sizeof(n));
            }
        }
        write(pip[1], &no, sizeof(n));
    }
    // sleep(1);
    // for(int i = 0; i < son_num; i++) {
    //     wait(0);
    // }
    wait(0);
    exit(0);
}
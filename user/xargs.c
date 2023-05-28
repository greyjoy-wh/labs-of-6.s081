#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"



int main(int argc, char* argv[])
 {
    //从标准输入中读取数据，一个一个的读，读取了一个换行后
    //将读取的数据加入后面要加的参数中
    char* cur_arg[MAXARG];
    for(int i = 0; i < MAXARG; i++) 
    {
        cur_arg[i] = 0;
    }
    for(int i = 0; i < argc - 1; i++) 
    {
        cur_arg[i] = argv[i+1];
    }
    char buf[16]; //最后一个参数
    char* p = buf;
    while(1)
    {
        int ret = read(0, p, 1);
        if(ret == 0)
        {
            exit(0);
            // return 0;
        }   
        if(*p == '\n')
        {
            *p = '\0';
            cur_arg[argc - 1] = buf;
            if(fork() == 0)
            {

                exec(cur_arg[0], cur_arg);
            }
            else{
                wait(0);
                p = buf;
                continue;
            }

        }
        p++;
    }
    return 0;
}


// int
// main(int argc, char* argv[])
// {
//     char* cur_argv[MAXARG];
//     char all_last[MAXARG][16];
//     int cur = 0;
//     char* p = all_last[cur];
    
//     for(int i = 0; i < argc - 1; i++) 
//     {
//         cur_argv[i] = argv[i+1];
//     }

//     while(read(0, p, 1) > 0) 
//     {
//         if(*p == '\n')
//         {
//             *p = '\0';
//             cur++;
//             p = all_last[cur];            
//         }else
//         {
//             p++;    
//         }
//     }
//     // printf("%s\n", all_last[0]);
//     for(int i = 0; i < cur; i++)
//     {
//         cur_argv[argc - 1] = all_last[i];
//         cur_argv[argc] = 0;
//         // for(int i = 0; i < argc; i++) 
//         // {
//         //     printf("%s\n", cur_argv[i]);
//         // }
//         if(fork() == 0)
//         {
//             exec(cur_argv[0], cur_argv);   
//             return 1;     
//         }
//         wait(0);
//     }
//     return 0;
// }



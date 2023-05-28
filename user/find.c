#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
find(char * path, char* target) {
    // printf("find() start:path = %s, target = %s\n", path, target);
    int fd;
    char cur_path[512], *p;
    struct dirent de;
    struct stat st;
    // if(strcmp(fmtname(path), ".") == 0 || strcmp(fmtname(path), "..") == 0){
    // return;
    // }
    if((fd = open(path, 0)) < 0){
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch (st.type)
    {
    case T_FILE:{
        // printf("%s, %s, %s\n", target,  fmtname(path),  path);
        // printf("%d, %d, %d\n", strlen(target),  strlen(path), strlen(fmtname(path)));
        char *cur = fmtname(path);
        char *cur1 = fmtname(path);
        while(1) {
            if(*cur == ' ') {
                *cur = '\0';
                break;
            }
            cur++;
        }
        
        if(strcmp(target, cur1) == 0){
            printf("%s\n", path);
        }
        break;
    }

    
    case T_DIR:{
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0) 
                continue;
            int n1 = strcmp(de.name, ".");
            int n2 = strcmp(de.name, "..");
            if(n1 == 0 || n2 == 0){
                continue;
            }
            strcpy(cur_path, path);
            p = cur_path + strlen(cur_path);
            *p++ = '/';
            strcpy(p, de.name);
            // printf("find() end :%s,%s\n", cur_path, path);
            // int n3 = strcmp(cur_path, "./");
            // if(n3 == 0) {
            //     break;
            // }
            // printf("%s\n", cur_path);
            find(cur_path, target);
        }
        break;
    }

    }
    close(fd);
}

int main(int argc, char* argv[]) {
    char *path;
    char *target;
    if(argc < 3) {
        path = "."; //如果参数就一个，那么就默认是在当前目录下递归寻找
        target = argv[1];
    }else{
        path = argv[1];
        target = argv[2];
    }
    find(path, target);
    exit(0);
    return 0;
}
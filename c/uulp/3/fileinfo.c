#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>

void show_stat_info(char *,struct stat *);

int
main(int ac, char * av[]){
    struct stat info;
    if (ac > 1){
        if (stat(av[1],&info) != -1){
            show_stat_info(av[1],&info);
            return 0;
        }else
            perror(av[1]);
       
    }
    return 1;
}

void show_stat_info(char * fname, struct stat * buf){
    printf("    name:%s\n",fname);
    printf("    mode:%o\n",buf->st_mode);
    printf("    links:%d\n",buf->st_nlink);
    printf("    user:%d\n",buf->st_uid);
    printf("    group:%d\n",buf->st_gid);
    printf("    size:%d\n",buf->st_size);
    time_t t = buf->st_atime;
    printf("    atime is %ld\n",t);
    char * cp = ctime(&t);
    char str[80];
    if (cp) {
        strcpy(str,ctime(&t));
        printf("    cp is not NULL.%s\n",str);
   
    }
     
    //time(&t);
    //printf("    last access time:%s\n",ctime(&t));

}

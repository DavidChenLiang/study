#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(void){
   int fd; 
   if((fd = creat("forlseek.txt",O_APPEND)) ==-1){
        perror("can not open/create file.");
        exit(-1);
   }
   lseek(fd,20,SEEK_END);
   char *buf = "hello after 20";
   write(fd,buf,strlen(buf));
   if (close(fd) == -1){
        perror("error closing fd");
        exit(-1);
   }
   return 0;
   
}


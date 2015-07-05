#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(void){
    int r_fd;
    int w_fd;
    int r2_fd;
    if((r_fd = open("test.txt",O_RDONLY)) ==-1){
            perror("can not open test.txt in read  mode");
    }else if ((w_fd = open("test.txt",O_WRONLY)) == -1){
       perror("can not open test.txt in write mode"); 
    }else if ((r2_fd = open("test.txt",O_RDONLY)) == -1){
        perror("can not open test.txt in read agagin;");
    }
    char rbuf[20];
    read(r_fd, rbuf, 20);
    printf("%s",rbuf);
    char * wbuf="testing 123...";
    write(w_fd,wbuf,7);
    read(r2_fd,rbuf, 20);
    printf("%s",rbuf);
    if (close(r_fd)== -1 || close(w_fd) ==-1 || close(r2_fd) ==-1){
        perror("error close test.txt");
    }
    return 0;
}

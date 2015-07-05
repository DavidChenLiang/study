#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>


int 
main(void)
{
    uid_t uid;
    uid = geteuid();        
    struct passwd * pwd = getpwuid(uid);
    printf("%s\n",pwd->pw_name);
    return(0) ;
}


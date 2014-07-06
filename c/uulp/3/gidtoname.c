#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
char *gid_to_name(gid_t gid)
{
    struct group * getgrpid(), * grp_ptr;
    static char numstr[10];
    
    if ((grp_ptr = getgrpid(gid)) == NULL){
        sprintf(numstr,"%d", gid);
        return numstr;
    }else {
        return grp_ptr->gr_name; 
    }
}

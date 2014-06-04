#include <stdio.h>
#include <gdbm.h>

int 
main(void)
{
    GDBM_FILE dbf;
    datum key = {"testkey",1};
    datum value = {"testvalue",9};

    printf("Storing key-value pair...");
    dbf = gdbm_open("test",0,GDBM_NEWDB,0644,0);
    gdbm_store(dbf,key,value,GDBM_INSERT);
    gdbm_close(dbf);
    printf("done.\n");
    return 0;

}

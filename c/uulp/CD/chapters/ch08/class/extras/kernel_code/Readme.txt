This file, exec.c, contains the kernel code that executes a program.

The actual function is at the end of the file.  The rest of the file
contains various helper functions.

There is a lot going on here, but you might what to look first for
the place where the command line args you pass to exec() are 
transferred to the new program.

Remember, the kernel has to remove from the process the calling
program and then load the called program into the process space.
All the code and data for the calling program are wiped out

but ...

the argument list passed from the caller is somehow set up as
the command line args for the newly installed program.



--------------------------------------------------------------------------
Linux Kernel Code for tty driver including the termios setting/getting code
--------------------------------------------------------------------------

   This directory has the kernel driver code for tty processing from
   Linux version 2.2.14 .  

   Look through n_tty.c to see if you can find where erase chars
   are checked and processed, where echoing is done, where signal
   handling occurs.  Where does carriagereturn->newline translation
   take place?

   The file called tty_ioctl.c is the code that handles the kernel
   side of tcgetattr() and tcsetattr().  

   Puzzle:  in canonical (`cooked') mode, characters are kept in an
            edit buffer until the user pressed the return key.  
            What data structure is used for that buffer?  Where
            do characters go when they leave that buffer?  Where
            do they come from as they enter that buffer?

   Device as File:  look in ttty_io.c for the definition of 

                static struct file_operations tty_fops = {

             this table of function pointers is used by the
             kernel when a program makes system calls to 
             open, close, read, write, lseek, etc the tty.
             Some of the calls have NULL pointers.  The lseek
	     function should be NULL, one would expect.  See
	     how the kernel handles calls to lseek on a tty.
	     Then compare that to the manual page for lseek.

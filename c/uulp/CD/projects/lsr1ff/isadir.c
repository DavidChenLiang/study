#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>

/**
 **	isadir.c
 **
 **	contains a single function that uses stat(2) to
 **	determine if the named object is a directory
 **
 **		isadir( char *name )
 **			returns 1 if string is a dir, else 0
 **
 **/

isadir( char *name )
/*
 *	calls stat, then masks the st_mode word to obtain the
 *	filetype portion and sees if that bit pattern is the
 *	pattern for a directory
 */
{
	struct stat info;

	return ( stat(name,&info)!=-1 && (info.st_mode & S_IFMT) == S_IFDIR );
}


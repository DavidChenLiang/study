#include	<stdio.h>
#include	<termios.h>

/*
 *	if first arg is X (for expand), then read stdin and 
 *	expand to char codes and bit patterns
 */


main(ac,av)
char **av;
{
	struct termios info ;
	char	vals[6][100];
	int	e, k, iflg, oflg, cflg, lflg;

	if ( ac > 1 && av[1][0] == 'X' )
		expand();

	tcgetattr(0, &info);
	if ( ac > 1 && av[1][0] == 'S' ){
		sscanf( av[2] , "E=%2xK=%2xIF=%4xOF=%4xCF=%4xLF=%4x", 
					&e, &k, &iflg, &oflg, &cflg, &lflg);
		info.c_iflag 	  =  iflg;
		info.c_oflag 	  =  oflg;
		info.c_cflag 	  =  cflg;
		info.c_lflag 	  =  lflg;
		info.c_cc[VERASE] = e;
		info.c_cc[VKILL]  = k ;
		tcsetattr(0,TCSANOW,&info);
		exit(1);
	}

/*
 * hey kids, don't try this at home. This is to make the OSF
 * special addition to the driver to work.  Read the header
 * file to see what gives (bruce, mar 7, 2001)
 */
#ifdef OXTABS
	if ( info.c_oflag & OXTABS )
		info.c_oflag |= TAB3 ;
	else 
		info.c_oflag &= ~TABDLY;
#endif
	sprintf( vals[0], "E=%02x" , info.c_cc[VERASE]);
	sprintf( vals[1], "K=%02x" , info.c_cc[VKILL] );
	sprintf( vals[2], "IF=%04x" , ( 0xcFE & info.c_iflag)  );
	sprintf( vals[3], "OF=%04x" , ( 0xcFE & info.c_oflag)  );
	sprintf( vals[4], "CF=%04x" , ( 0xcFE & info.c_cflag)  );
	sprintf( vals[5], "LF=%04x" , ( 0xcFE & info.c_lflag)  );
	if ( ac == 1 )
		printf("%s%s%s%s%s%s",  vals[0], vals[1], vals[2],
					vals[3], vals[4], vals[5]);
	else
		while ( --ac )
			if ( **++av == 'E' )
				printf("%s", vals[0]);
			else if ( **av == 'K' )
				printf("%s", vals[1]);
			else if ( strncmp(*av,"IF",2) == 0 )
				printf("%s", vals[2]);
			else if ( strncmp(*av,"OF",2) == 0 )
				printf("%s", vals[3]);
			else if ( strncmp(*av,"CF",2) == 0 )
				printf("%s", vals[4]);
			else if ( strncmp(*av,"LF",2) == 0 )
				printf("%s", vals[5]);
	putchar('\n');
}


expand()
{
	int	e, k, iflg, oflg, cflg, lflg;
	char	*val2str(), *val2bin();
	char	b[BUFSIZ];

	while ( scanf("%s", b) == 1 ){
		sscanf( b , "E=%2xK=%2xIF=%4xOF=%4xCF=%4xLF=%4x", 
					&e, &k, &iflg, &oflg, &cflg, &lflg);
		printf(" Erase = %s, ", val2str(e) );
		printf(" Kill = %s,\n",  val2str(k) );
		printf(" IFlags = %s\n", val2bin(iflg) );
		printf(" OFlags = %s\n", val2bin(oflg) );
		printf(" CFlags = %s\n", val2bin(cflg) );
		printf(" LFlags = %s\n", val2bin(lflg) );
	}
}

char *val2str( n )
{
	static char	retval[4];

	if ( n == 127 )
		strcpy( retval, "DEL" );
	else if ( n > ' ' && n < 127 )
		sprintf( retval , "%c", n );
	else 
		sprintf( retval , "^%c", ( n | 64 ) );
	return retval ;
}

char *val2bin( n )
{
	static	char	retval[100];
	char	*cp = retval ;
	int	mask = 0x8000 ;

	while ( mask ){
		*cp++ = ( (mask & n) ? '1' : '0' );
		mask >>= 1 ;
	}
	*cp = '\0';
	return retval ;
}


/*
 * Revision History:
 *
 * Original source from:
 *  Peter da Silva (ihnp4!shell!neuro1!{hyd-ptd,datafact,baylor}!peter)
 *
 * Changes for padding added by:
 *  Andrew Scott Beals ({ucbvax,decwrl}!amdcad!bandy or bandy@amdcad.amd.com)
 *  20 April 1987
 *
 * Additional changes for padding, fix for computation of tglen,
 * increase max lines, improve termlib handling, add System V #ifdefs.
 *  Bill Randle (billr@tekred.TEK.COM)
 *  21 April 1987
 *
 * Some long-standing 8-bit bugs fixed, and more randomness added.
 *  Peter da Silva <peter@sugar.hackercorp.com> Dec 1 1989.
 *
 * ((char *)0) de-referencing removed. [Caused SEGV core dumps on Sun-3's]
 *  Andrew Scott Beals <bandy@toad.com> 7 May 1990
 *
 * "PG" emulation added Dec '90 by Peter da Silva, in a fit of boredom.
 * Now "rot" acts like a pager, only dumping the screen if you wait too long.
 */

#include <stdio.h>
#include <string.h>

#ifdef SYSV
# include <termio.h>
#else
# include <sgtty.h>
#endif

#include <signal.h>

/*		-- Miscellaneous defines --				     */
#define FALSE 0
#define TRUE 1
#define MAXCOL 80
#define MAXLI 34
#define SLEEPFACTOR 2	/* Assumed reading speed, lines per second */
#define COLRATIO 8	/* For delays, amount to discount columns by */

extern char *tgetstr();

int lastx, lasty;
struct _c {
	struct _c *c_next;
	int c_line, c_column;
	char c_mark;
} *clist;

/*		-- Global variables --					     */
char *tent;                                               /* Pointer to tbuf */
extern char PC;                                             /* Pad character */
extern char *UP, *BC;                         /* Upline, backsapce character */
extern short ospeed;                                /* Terminal output speed */
int tglen;

char *cm,                                                   /* Cursor motion */
     *cl,                                                    /* Clear screen */
     *ti,						    /* Init terminal */
     *te;						   /* Reset terminal */
int  li,                                                  /* lines on screen */
     co;                                                    /* columns ditto */
char screen[MAXLI+1][MAXCOL];
char newscreen[MAXLI+1][MAXCOL];
char *me;						     /* program name */

/* Options */
int packflag = 0;

main(ac, av)
int ac;
char **av;
{
	/* set ospeed so padding works correctly */
#ifdef SYSV
	struct termio	p;

	if(ioctl(1, TCGETA, &p) != -1)
		ospeed=p.c_cflag & CBAUD;
#else
	struct sgttyb	p;

	if(ioctl(1, TIOCGETP, &p) != -1)
		ospeed=p.sg_ospeed;
#endif

	me = *av;

	srand(getpid());
	tinit(getenv("TERM"));
	while(ac > 1 && av[1][0]=='-') {
		while(av[1][1]) {
			switch(av[1][1]) {
				case 'p': packflag=1; break;
				default: fprintf(stderr, "%s [-p] [file]...\n", me);
			}
			av[1]++;
		}
		av++;
		ac--;
	}
	if(ac > 1)
		while(*++av)
			dropf(*av);
	else
		fdropf(stdin);
	tend();
}

at(x, y, c)
int x, y;
char c;
{
#ifdef DEBUG
	_at(x, y);
#else
	if(y==lasty) {
		if(x!=lastx) {
			if(x<lastx && lastx-x<tglen)
				while(x<lastx) {
					putchar('\b');
					lastx--;
				}
			else if(x>lastx && x-lastx<tglen)
				while(x>lastx) {
					putchar(0x7F&newscreen[lasty][lastx]);
					lastx++;
				}
			else
				_at(x, y);
		}
	} else
		_at(x, y);
#endif
	c &= 0x7F;
	putchar(c);
	if(c >= ' ' && c != '\177')
		lastx++;
	if(lastx>=co) {
		lastx -= co;
		lasty++;
	}
}

_at(x, y)
int x, y;
{
	extern void	outc();

	tputs(tgoto(cm, x, y), 1, outc);	 /* handle padding */
	lastx = x;
	lasty = y;
}

void
outc(c)
register c;
{
	putc(c&0x7F, stdout);
}

tinit(name)
char *name;
{
	static char junkbuf[1024], *junkptr;
	char tbuf[1024];
	int  intr();

	junkptr = junkbuf;

	tgetent(tbuf, name);

	if (!tgetflag("bs"))		/* is backspace not used? */
		BC = tgetstr("bc",&junkptr);	/* find out what is */
	else
		BC = "\b";		/* make a backspace handy */
	if (tgetstr("pc", &junkptr) != NULL)
		PC = *junkptr;  /* set pad character */
	else
		PC = '\0';
	UP = tgetstr("up", &junkptr);
	cm = tgetstr("cm", &junkptr);
	if (cm == NULL) {
		printf("Can't rot on dumb terminals.\n");
		exit(1);
	}
	cl = tgetstr("cl", &junkptr);
	ti = tgetstr("ti", &junkptr);
	te = tgetstr("te", &junkptr);
	li = min(tgetnum("li"), MAXLI);
	if (li == -1)
		li = 24;
	co = min(tgetnum("co"), MAXCOL);
	if (co == -1)
		co = 80;
	tglen =  strlen((char *)tgoto(cm, co-1, li-1));
}

tend()
{
	if(te != NULL) outs(te);
	_at(0, li-1);
	putchar('\n');
	fflush(stdout);
}

readscreen(fp)
FILE *fp;
{
	int line, column, p;
	char tmp[256];

	for(line=0; line<li; line++)
		for(column=0; column<co; column++)
			{
			newscreen[line][column] = screen[line][column] = ' ';
			}
	strncpy(&newscreen[li-1][0], "--Hit CR--", 10);
	for(column=0; column<co; column++)
		newscreen[li][column] = screen[li][column] = '*';
	line=0;
	while(line<li-1) {
		if(!fgets(tmp, 256, fp))
			return(max(line,column/COLRATIO));

		for(column=0, p=0; tmp[p]; p++) {
			tmp[p] &= ~0200;
			if(tmp[p] < ' ' || tmp[p] == 127)
				switch(tmp[p]) {
					case '\t':
						while(++column % 8)
							continue;
						break;
					case '\n':
						column = 0;
						line++;
						break;
					default:
						newscreen[line][column] = '^';
						column++;
						if(column>=co) {
							column -= co;
							line++;
						}
						newscreen[line][column] =
							(tmp[p]+'@') & 127;
						column++;
						break;
				}
			else {
				newscreen[line][column] = tmp[p];
				column++;
			}
			if(column >= co) {
				column -= co;
				line++;
			}
			if(line >= li)
				break;
		}
	}
	for(column=0; column<co; column++)
		newscreen[li][column] = screen[li][column] = '*';
	return(max(line,column/COLRATIO));
}

drawscreen()
{
	lastx = lasty = 0;
	outs(cl);
	update();
}

update() /* copy new screen back to old screen */
{
	int l, c;

	for(l=0; l<li; l++)
		for(c=0; c<co; c++)
			if(screen[l][c] != newscreen[l][c]) {
				if((screen[l][c] & ~0200) !=
				   (newscreen[l][c] & ~0200))
					at(c, l, newscreen[l][c]);
				screen[l][c] = newscreen[l][c];
			}
}

drop(line, column)
int line, column;
{
	struct _c *hold, *temp;

	if(line<0 || line>=li || column<0 || column>=co ||
	   (line>=li-2 && column >= co-1) || /* scroll potential */
	   screen[line][column]==' ' || /* empty */
	   screen[line][column] & 0200) /* already in list */
		return;
	if(screen[line+1][column]!=' ' &&
	   (column==co-1 ||screen[line+1][column+1]!=' ') &&
	   (column==0 ||screen[line+1][column-1]!=' '))
		return;

	hold = (struct _c *) malloc(sizeof(struct _c));
	hold -> c_next;
	hold -> c_column = column;
	hold -> c_line = line;
	hold -> c_mark = 0;
	screen[line][column] |= 0200;

	for(temp = clist; temp && temp->c_next; temp=temp->c_next)
		if(!(rand()&1111))
			break;
	if(temp) {
		hold->c_next = temp->c_next;
		temp->c_next = hold;
	} else {
		hold->c_next = clist;
		clist = hold;
	}
}

drops()
{
	int l, c;
	struct _c *hold;
	for(hold = clist; hold; hold=hold->c_next) {
		int line = hold->c_line, column=hold->c_column;
		if(line>= li-2 && column>=co-1) {
			newscreen[line][column] &= ~0200;
			screen[line][column] &= ~0200;
			hold->c_mark = 1;
			continue;
		}
		if(newscreen[line+1][column+1] == ' ' &&
		   newscreen[line+1][column-1] == ' ')
			drop(line+1, column);
		drop(line, column+1);
		drop(line-1, column);
		drop(line, column-1);
		if(newscreen[line+1][column]==' ' ||
		   (packflag &&
		    newscreen[line+1][column]==(screen[line][column]&~0200)
		   )
		  ) {
			newscreen[line+1][column] = screen[line][column];
			newscreen[line][column] = ' ';
			line++;
		} else if(rand()&01000) {
			if(column>0 && newscreen[line][column-1] == ' ' &&
			    newscreen[line+1][column-1]==' ') {
				newscreen[line][column-1] =
					screen[line][column];
				newscreen[line][column] = ' ';
				column--;
			}
			else if(column<co-1 &&
				newscreen[line][column+1] == ' ' &&
				newscreen[line+1][column+1]==' ') {
					newscreen[line][column+1] =
						screen[line][column];
					newscreen[line][column] = ' ';
					column++;
			}
			else {
				screen[line][column] &= ~0200;
				newscreen[line][column] &= ~0200;
				hold -> c_mark = 1;
			}
		} else {
			if(column<co-1 && newscreen[line][column+1] == ' ' &&
			    newscreen[line+1][column+1]==' ') {
				newscreen[line][column+1] =
					screen[line][column];
				newscreen[line][column] = ' ';
				column++;
			}
			else if(column>0 && newscreen[line][column-1] == ' ' &&
			    newscreen[line+1][column-1]==' ') {
				newscreen[line][column-1] =
					screen[line][column];
				newscreen[line][column] = ' ';
				column--;
			}
			else {
				newscreen[line][column] &= ~0200;
				screen[line][column] &= ~0200;
				hold -> c_mark = 1;
			}
		}
		hold -> c_column = column;
		hold -> c_line = line;
		fflush(stdout);
	}

	while(clist && clist->c_mark) {
		struct _c *p = clist;
		clist = clist -> c_next;
		free(p);
	}
	hold = clist;
	while(hold && hold->c_next)
		if(hold->c_next->c_mark) {
			struct _c *p = hold->c_next;
			hold->c_next = p->c_next;
			free(p);
		} else
			hold=hold->c_next;
}

droplet(line, column)
int line, column;
{
	int ret;
	if(line==li-1)
		return 0;
	while(column>=0 &&
	      screen[line][column]!=' ' &&
	      screen[line+1][column]==' ')
		column--;
	column++;
	while(column<co &&
	      screen[line][column]!=' ' &&
	      screen[line+1][column]==' ')
		drop(line, column++);
	ret = clist != 0;
	while(clist) {
		drops();
		usleep(100000);
		update();
	}
	return ret;
}

dropscreen()
{
	int column, line;
	int rubbish = 0, count = 0;

	do {
		int start, limit, incr;
		count++;
		rubbish = 0;
		if(count&1) { start=li-2; limit=0; incr = -1; }
		else { start=0; limit=li-2; incr=1; }
		for(line=start; line!=limit && !rubbish; line+=incr) {
			if(line&1)
				for(column=0; column<co && !rubbish; column++)
					rubbish += droplet(line, column);
			else
				for(column=co-1; column>=0 && !rubbish; column--)
					rubbish += droplet(line, column);
		}
	} while(rubbish);
}

dropf(file)
char *file;
{
	FILE *fp;

	if(!(fp = fopen(file, "r"))) {
		perror(file);
		return -1;
	}
	fdropf(fp);
}

fdropf(fp)
FILE *fp;
{
	int i,lines;

	while(!feof(fp)) {
		lines=readscreen(fp);
		drawscreen();
		fflush(stdout);
		if( 1 || more(lines) == 0) { /* Timed out */
			for(i=0; i<20; i++)
				droplet((rand()>>4) % (li-1), (rand()>>4) % co);
			dropscreen();
		}
	}
}

char timed_out;

void tmo(int s)
{
	timed_out = 1;
}

more(lines)
int lines;
{
	char c;

	timed_out = 0;
	signal(SIGALRM, tmo);
	alarm(max(lines/SLEEPFACTOR,1));
	while(!timed_out) {
		read(0, &c, 1);
		if(c=='\n' || c=='\r') break;
	}
	alarm(0);
	return !timed_out;
}

outs(s)
char *s;
{
	fputs(s, stdout);
}

min(a, b)
int a, b;
{
	if(a<b) return a;
	return b;
}

max(a, b)
int a, b;
{
	if(a>b) return a;
	return b;
}

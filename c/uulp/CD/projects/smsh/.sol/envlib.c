#include	<stdio.h>

/*
 *	envlib		- a set of functions for mananging
 *			- the environment.  These are taken
 *			- directly from `Advanced Unix Programming'
 *			- by Marc Rochkind, chapter 5.
 */

/* -------------------------------------------------------------------
 *	STUFF
 */

typedef	int BOOLEAN;	
#define	TRUE	1
#define	FALSE	0

/* -------------------------------------------------------------------
 *	DATA
 *	simple array of structs holds the symbols in the environment
 */

#define	MAXVAR		100
#define	VARLEN		20

static struct varslot {
	char *name;		/* variable name */
	char *val;		/* variable value */
	BOOLEAN  exported;	/* is it to be exported ? */
} sym[MAXVAR];

/* -------------------------------------------------------------------
 *	CODE
 */

static struct varslot *
find(name)
char *name;
/*
 *	find - 	returns a pointer to a slot in the table or NULL
 *		if no slots are available.
 */
{
	int i;
	struct varslot *v;

	v = (struct varslot *) NULL ;
	for ( i = 0 ; i < MAXVAR ; i++ )
		if ( sym[i].name == NULL ){
			if ( v == NULL )
				v = &sym[i];
		}
		else if ( strcmp(sym[i].name,name) == 0 ){
			v = &sym[i];
			break;
		}
	return v;
}

BOOLEAN 
EVset(name,val)
char *name, *val;
/*
 *	add name and value to environment
 *	return FALSE if there is no more space, else TRUE
 */
{
	struct varslot *v;

	if ( ( v = find(name) ) == ( struct varslot *) NULL )
		return( FALSE );
	return ( assign(&v->name,name) && assign(&v->val,val) );
}

char *malloc(), *realloc();

static BOOLEAN
assign(buffp,s)
char **buffp, *s;
/*
 *	initialize name or value, pass it address of buffer
 *	and new string to put there
 */
{
	int	size;
	size = strlen(s) + 1;
	if ( *buffp == NULL ){		/* unused slot in table */
		if ( (*buffp = malloc(size)) == NULL )
			return (FALSE);
	}
	else if ( (*buffp = realloc(*buffp,size)) == NULL )/* resize storage */
		return ( FALSE );

	strcpy(*buffp, s);
	return (TRUE);
}

BOOLEAN 
EVexport(name)	/* set variable to be exported */
char *name;	/* install the name it if not there	*/
{
	struct varslot *v;
	if ( (v = find(name)) == NULL )
		return (FALSE);
	if ( v->name == NULL )
		if ( !assign(&v->name,name) || !assign(&v->val,""))
			return (FALSE);
	v->exported = TRUE;
	return (TRUE);
}

char *
EVget(name)
char *name;
/*
 *	retrieve value of variable from table, or NULL
 */
{
	struct varslot *v;

	if ( (v = find(name)) == NULL || v->name == NULL )
		return (NULL);
	return (v->val);
}

BOOLEAN
EVinit()
/*
 *	read the environment and build symbol table
 *	modified from Rochkind to catch overlong variable names
 */
{
	int	i, namelen, usablelen;
	char	name[VARLEN+1];
	extern	char **environ;

	for (i=0; environ[i] != NULL ; i++ ){
		namelen = strcspn(environ[i],"=");
		usablelen = (namelen>VARLEN?VARLEN:namelen);
		strncpy(name,environ[i], usablelen);
		name[usablelen] = '\0';
		if ( !EVset(name,&environ[i][namelen+1]) || !EVexport(name))
			return(FALSE);
	}
	return (TRUE);
}

strcspn(string, lookfor)
char *string, *lookfor;
{
	int	i;
	for (i=0; string[i] != *lookfor ; i++ )
		;
	return i ;
}

BOOLEAN
EVupdate()
/*
 *	rebuild environment from symbol table
 */
{
	int i, envi,nvlen;
	struct varslot *v;
	static BOOLEAN updated = FALSE ;

	if ( !updated )
		if ( (environ = (char **)malloc((MAXVAR+1) * sizeof(char *)))
			== NULL )
			   return(FALSE);
	envi = 0;
	for (i=0; i<MAXVAR; i++ ){
		v = &sym[i];
		if ( v->name == NULL || !v->exported )
			continue;
		nvlen = strlen(v->name) + strlen(v->val) + 2 ;
		if ( !updated ){
			if ((environ[envi] = malloc(nvlen)) == NULL )
				return(FALSE);
		}
		else if ( (environ[envi]=realloc(environ[envi],nvlen))==NULL)
			return(FALSE);
		sprintf(environ[envi],"%s=%s", v->name, v->val);
		envi++;
	}
	environ[envi] = NULL ;
	updated = TRUE;
	return(TRUE);
}

void
EVprint()
/*
 *	dump symbol table
 */
{
	int i;
	for(i = 0; i<MAXVAR; i++)
		if ( sym[i].name != NULL )
			printf("%3s %s=%s\n", sym[i].exported ? "[E]" : "" ,
				sym[i].name, sym[i].val);
}

#ifdef	STANDALONE
main()
{
	if ( !EVinit() )
		exit(2);
	printf("First..\n");
	EVprint();
	if (!EVset("count", "0"))
		exit(3);
	if ( !EVset("BOOK","/usr/marc/book") || !EVexport("BOOK"))
		exit(4);
	printf("After updating\n");
	EVprint();
	EVupdate();
	execl("lsenv", "lsenv", 0);
}
#endif

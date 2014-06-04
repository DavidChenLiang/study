On some versoions of Unix you can type  login smith  to a shell
and you'll be logged in as the new user.  There is no logout
record in wtmp in that case.  On some versions you could type
exec login smith to the shell.  Maybe it does not apply in your
case.  Nonetheless last handles it as a logout.

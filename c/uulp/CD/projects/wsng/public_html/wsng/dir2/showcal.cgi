#!/bin/sh
#
# expects a month number in QUERY_STRING
#

	echo "Content-type: text/html"
	echo ""

	echo "<html>
	<head><title>A calendar</title></head>
	<body bgcolor=white>"

	OK=NO
	NUM=$QUERY_STRING
	case "$NUM" in

		[1-9]|1[012])	OK=YES ;;

		?*)	echo "Incorrect month number"	;;
		*)	echo "missing month number"	;;
	esac

	if test "$OK" = NO 
	then
		exit
	fi

	set "x" Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
	shift $NUM

	echo "
	<center>A Calendar for $1

	<table border=2>
	<tr><td><pre>"

	cal $NUM 2002

	echo "</pre></td></tr></table>"

	echo "</center>"

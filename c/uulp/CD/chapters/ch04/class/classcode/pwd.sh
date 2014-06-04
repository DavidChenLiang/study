#!/bin/sh
#	pwd as a shell script
#	sort of works most of the time
#

PATHTAIL=""

#	will build path from end as we move upwards through tree

while :
do
	set `ls -id .`				# get inode number of .
	MYINODE=$1
	cd ..					# now step up one level
	set `ls -id .`				# see if at top of filesys
	if test $1 = $MYINODE			# i.e. where .. == .
	then
		echo /$PATHTAIL			# there, get out
		exit
	fi
	set `ls -ia | grep "$MYINODE " `	# not there, find my name
	MYNAME=$2				# store it
	if test "$PATHTAIL" = ""		# add to head of string
	then
		PATHTAIL=$MYNAME
	else
		PATHTAIL=$MYNAME/$PATHTAIL
	fi
done

#!/bin/sh
#
# quiz.sh
#		purpose	use quizzer to ask several questions
#		
	SCORE=0
	quizzer "Who is buried in Grant's tomb" grant 3
	if test $? = 0
	then
		echo "Correct!"
		SCORE=`expr $SCORE + 1`
	else
		echo "Too bad"
	fi
	quizzer "What is 2 + 2" 4 5
	if test $? = 0
	then
		echo "Correct!"
		SCORE=`expr $SCORE + 1`
	else
		echo "too bad"
	fi
	quizzer "What is the capital of Massachusetts" boston 4
	if test $? = 0
	then
		echo "Correct!"
		SCORE=`expr $SCORE + 1`
	else
		echo "too bad"
	fi
	echo "total score = $SCORE"

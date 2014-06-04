if test "$1" != ""
then
	VER=$1
else
	VER=0
fi

while true
do
	echo "How much do you want? "
	read amount
	echo "here is $amount dollars"
	echo  
	if play_again$VER
	then
		:
	else
		break
	fi
done

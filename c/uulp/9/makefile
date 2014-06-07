CC=gcc
getenv:getenv.o
	$(CC) -o $@ $^
showenv:showenv.o
	$(CC) -o $@ $^
changeenv:changeenv.o
	$(CC) -o $@ $^
.PHONY:clean
clean:
	-rm -rf *.o
	-rm -rf getenv showenv changeenv 

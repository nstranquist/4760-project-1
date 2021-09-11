# Makefile - Project 1
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/

driver: driver.c log.h log.c
	gcc -o driver driver.c log.c -I .

log: log.c log.h
	gcc -o log log.c log.h -I .

clean:
	rm driver.o
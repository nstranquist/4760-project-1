# Makefile - Project 1
# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/


# Run First
driver: driver.c log.h log.c
	gcc -o driver driver.c log.c -I .

# Run second
# log:
# 	ar -rc driver.a driver

clean:
	rm driver.o driver driver.a
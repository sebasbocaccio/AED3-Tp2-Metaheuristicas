# Makefile for el tp de algo3 parte 2



CC=g++ -Wall -j2 -O3 

SRC_DIR=.
EXE_DIR=.

EXES = \
       ./main
	

${EXE_DIR}/%: %.o
	${CC} -o $@ $< ${LIBS}

%.o: ${SRC_DIR}/%.c
	${CC} -o $@ -c $<

all:    ${EXES}


clean:
	@rm -f ${EXES}

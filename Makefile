CXX = u++					# compiler
CXXFLAGS = -g -multi -O2 -Wall -Wextra -MMD # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = bank.o bottlingplant.o config.o groupoff.o main.o nameserver.o parent.o printer.o student.o truck.o \
	vendingmachine.o watcard.o watcardoffice.o
EXEC = soda

DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"

#############################################################

.PHONY : all clean

all : ${EXEC}									# build all executables

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################
${OBJECTS} : ${MAKEFILE_NAME}					# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}								# include *.d files containing program dependences

clean :											# remove files that can be regenerated
MYCODEDIR := .

# Directories to search for header files
SEARCHDIRS := -I${MYCODEDIR}

DEPENDFLAGS := -g -Wall -Werror ${SEARCHDIRS}

# C preprocessor (C, C++, FORTRAN)
CPPFLAGS = 

# C compiler
CC     := gcc
CFLAGS  = ${DEPENDFLAGS}

%.o : %.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

# C++ compiler
CXX      := g++
CXXFLAGS  = ${DEPENDFLAGS}

%.o : %.cc
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $< -o $@

%.o : %.C
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $< -o $@

%.o : %.cpp
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $< -o $@

%.o : %.cxx
	${CXX} ${CPPFLAGS} ${CXXFLAGS} -c $< -o $@

# C/C++/Eiffel/FORTRAN linker

LINKER    := g++
LDFLAGS    = 
LOADLIBES := -lm -lGL -lglut -lGLU

# bb

bb : ./biobox.o ./force.o ./main.o ./model.o ./muscle.o ./organism.o ./point.o ./glutMaster.o ./glutWindow.o
	${LINKER} ${LDFLAGS} -o $@ ${filter-out %.a %.so, $^} ${LOADLIBES}

# target for making everything

.PHONY : all
all: bb


# target for removing all object files

.PHONY : tidy
tidy::
	@${RM} core ./biobox.o ./force.o ./glutMaster.o ./glutWindow.o ./main.o ./model.o ./muscle.o ./organism.o ./point.o

# target for removing all object files

.PHONY : clean
clean:: tidy
	@${RM} bb

# list of all source files

MM_ALL_SOURCES := ./biobox.cc ./force.cc ./glutMaster.cc ./glutWindow.cc ./main.cc ./model.cc ./muscle.cc ./organism.cc ./point.cc


# target for checking a source file

CHECKSYNTAXFILE := ${basename ${filter %${CHECKSTRING}, ${MM_ALL_SOURCES}}}

.PHONY : checksyntax
checksyntax:
  ifneq (${CHECKSYNTAXFILE},)
	@${MAKE} ${addsuffix .o, ${CHECKSYNTAXFILE}}
  else
	@echo No target to make ${CHECKSTRING}
  endif


# DO NOT DELETE THIS LINE -- makemake depends on it.

./biobox.o: ./biobox.h ./force.h ./glutMaster.h ./glutWindow.h ./model.h ./muscle.h ./organism.h ./point.h ./vector.h /usr/include/GL/gl.h /usr/include/GL/glu.h /usr/include/GL/glut.h /usr/include/math.h /usr/include/stdlib.h

./force.o: ./biobox.h ./force.h ./glutMaster.h ./glutWindow.h ./model.h ./muscle.h ./organism.h ./point.h ./vector.h /usr/include/GL/gl.h /usr/include/GL/glu.h /usr/include/GL/glut.h /usr/include/math.h /usr/include/stdlib.h

./glutMaster.o: ./glutMaster.h ./glutWindow.h /usr/include/GL/glut.h

./glutWindow.o: ./glutWindow.h

./main.o: ./biobox.h ./force.h ./glutMaster.h ./glutWindow.h ./model.h ./muscle.h ./organism.h ./point.h ./vector.h /usr/include/GL/gl.h /usr/include/GL/glu.h /usr/include/GL/glut.h /usr/include/math.h /usr/include/stdlib.h

./model.o: ./biobox.h ./force.h ./glutMaster.h ./glutWindow.h ./model.h ./muscle.h ./organism.h ./point.h ./vector.h /usr/include/GL/gl.h /usr/include/GL/glu.h /usr/include/GL/glut.h /usr/include/math.h /usr/include/stdlib.h

./muscle.o: ./force.h ./muscle.h ./point.h ./vector.h /usr/include/math.h

./organism.o: ./biobox.h ./force.h ./glutMaster.h ./glutWindow.h ./model.h ./muscle.h ./organism.h ./point.h ./vector.h /usr/include/GL/gl.h /usr/include/GL/glu.h /usr/include/GL/glut.h /usr/include/math.h /usr/include/stdlib.h

./point.o: ./force.h ./muscle.h ./point.h ./vector.h /usr/include/math.h


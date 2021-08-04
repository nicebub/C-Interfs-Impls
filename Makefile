ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	CLEANDIR = rmdir
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
#	GENERATE_RUNNER= tools/genrunners.sh
endif

.PHONY: all clean test run lint

SRCDIR = src
OBJDIR = obj
BUILDDIR = build
HDRDIR = include

FULLOBJDIR = ${BUILDDIR}/${OBJDIR}

SFILES = *.c
HFILES = *.h

SRC := $(wildcard ${SRCDIR}/${SFILES})
HDR := $(wildcard ${HDRDIR}/${HFILES})
SRC_STRIP := $(subst ./,,$(wildcard ${SRCDIR}/${SFILES}))
HDR_STRIP := $(subst ./,,$(wildcard ${HDRDIR}/${HFILES}))

OBJS := $(patsubst ${SRCDIR}/%,%,$(subst .c,.o, $(SRC)))
FULLOBJS := $(patsubst %,${FULLOBJDIR}/%,${OBJS})
DEBUG = -g -Wall
DEBUG += -DNDEBUG
CC = `which gcc`
BINARY = bin
EXEC = ${BUILDDIR}/${BINARY}
LINT = cpplint
LINTFLAGS = --verbose=2

STD = -std=gnu2x
CFLAGS += -I${HDRDIR} -I. ${STD}

all: ${BUILDDIR} ${FULLOBJDIR} ${EXEC}
#	@echo "---------------Source Files------------------"
#	@echo "in directory: " ${SRCDIR}
#	@echo ${SRC}
#	@echo "---------------Header Files------------------"
#	@echo "in directory: " ${HDRDIR}
#	@echo ${HDR}
#	@echo "------Will turn into these object files------"
#	@echo "in directory: " ${FULLOBJDIR}
#	@echo ${OBJS}

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

$(FULLOBJDIR):
	$(MKDIR) $(FULLOBJDIR)


${FULLOBJDIR}/%.o: ${SRCDIR}/%.c ${HDRDIR}/%.h
	${CC} ${CFLAGS} ${DEBUG} -c $< -o $@
${FULLOBJDIR}/%.o: ${SRCDIR}/%.c 
	${CC} ${CFLAGS} ${DEBUG} -c $< -o $@
	
${EXEC}: ${FULLOBJS}
	@echo ${FULLOBJS}
	${CC} ${CFLAGS} ${DEBUG} $^ -o $@

lint:
	 ${LINT} ${LINTFLAGS} ${SRCDIR}/*.c ${HDRDIR}/*.h

clean:
	${CLEANUP} ${FULLOBJDIR}/*
	${CLEANDIR} ${FULLOBJDIR}
	${CLEANUP} ${BUILDDIR}/*
	${CLEANDIR} ${BUILDDIR}
	


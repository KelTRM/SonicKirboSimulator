CC=g++
CF=-o2

LIB=libs
INC=inc

CL=-lraylib -lopengl32 -lgdi32 -lwinmm

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
BIN=out.exe

WIN_OBJ=${subst /,\,${OBJ}}

.PHONY: all clean

${BIN}: ${OBJ}
	${CC} ${CF} ${OBJ} -L ${LIB} ${CL} -o ${BIN}

all: ${BIN}

%.o: %.cpp
	${CC} -g3 ${CF} -I ${INC} $< -c -o $@

ifneq ($(uname), Linux)
run: ${BIN}
	.\${BIN} ${ARGS}
clean: ${BIN}
	del ${WIN_OBJ}
else
run:
	./${BIN} ${ARGS}
clean: ${BIN}
	rm ${OBJ}
endif

debug: all
	gdb ${BIN}
CC=			g++
CFLAGS= 	-std=c++17 -Wall -w -g -pthread
INCLUDE:= 	-I include/
LIB=		lib/*.cpp
SOURCE:= 	src/*.cpp
CLARGS:=	-L /usr/local/lib -lc -l OpenCL

EXE=		mll.bin

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $(SOURCE) -o $(EXE) $(CLARGS)

run:
	./$(EXE)

rb:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $(SOURCE) -o $(EXE) $(CLARGS) && ./$(EXE)

clean:
	rm $(BIN)

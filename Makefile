# Project: silo
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe
CC       = gcc.exe
AR		 = ar.exe
WINDRES  = windres.exe
OBJ      = silo_node.o silo_recycle.o silo_signal.o silo_simulate.o silo_nodeconf.o silo_gate.o
LINKOBJ  = silo_node.o silo_recycle.o silo_signal.o silo_simulate.o silo_nodeconf.o silo_gate.o
LIBS     = -L"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/lib" -L"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/lib" -static-libgcc
INCS     = -I"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/include" -I"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include"
CXXINCS  = -I"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/include" -I"C:/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/x86_64-w64-mingw32/include"
BIN      = libsilo-newc.a
CXXFLAGS = $(CXXINCS) 
CFLAGS   = $(INCS) 
RM       = rm.exe -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(AR) rcs $(BIN) $(LINKOBJ)

silo_node.o: silo_node.c
	$(CC) -c silo_node.c -o silo_node.o $(CFLAGS)

silo_recycle.o: silo_recycle.c
	$(CC) -c silo_recycle.c -o silo_recycle.o $(CFLAGS)

silo_signal.o: silo_signal.c
	$(CC) -c silo_signal.c -o silo_signal.o $(CFLAGS)

silo_simulate.o: silo_simulate.c
	$(CC) -c silo_simulate.c -o silo_simulate.o $(CFLAGS)

silo_nodeconf.o: silo_nodeconf.c
	$(CC) -c silo_nodeconf.c -o silo_nodeconf.o $(CFLAGS)

silo_gate.o: silo_gate.c
	$(CC) -c silo_gate.c -o silo_gate.o $(CFLAGS)

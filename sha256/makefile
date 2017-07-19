SRC:= sha256.c
OBJ:= sha256.o

CC:= gcc
CFLAGS:= -g -Wall
INCS:= -I/usr/local/ssl/include
LIBS:= -L/usr/local/ssl/lib -lcrypto

BIN:= sha256
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCS) -o $@ $< $(LIBS) 

.c.o:
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

clean:
	rm -rf sha256 *.o
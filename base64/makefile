SRC:= base64.c
OBJ:= base64.o

CC:= gcc
CFLAGS:= -g -Wall
INCS:= -I/usr/local/ssl/include
LIBS:= -L/usr/local/ssl/lib -lcrypto

BIN:= base64
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCS) -o $@ $< $(LIBS) 

.c.o:
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

clean:
	rm -rf base64 *.o
SRC:= aes.c
OBJ:= aes.o

CC:= gcc
CFLAGS:= -g -Wall
INCS:= -I/usr/local/ssl/include
LIBS:= -L/usr/local/ssl/lib -lcrypto

BIN:= aes
all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCS) -o $@ $< $(LIBS) 

.c.o:
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

clean:
	rm -rf aes *.o
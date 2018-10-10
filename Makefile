CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=-lcurl
SOURCES=src/main.c
BIN=bin/simple_http_check

all: $(BIN)

bin/simple_http_check: $(SOURCES)
	mkdir -p bin
	$(CC) -o $(BIN) $(CFLAGS) $(LDFLAGS) $(SOURCES)

clean:
	rm -rf bin

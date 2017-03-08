CC=gcc
CCOPTS=-g

TARGETS=kajalserver kajalclient udpserver udpclient

all: $(TARGETS)

kajalserver: kajalserver.c
	$(CC) $(CCOPTS) -o $@ $^

kajalclient: kajalclient.c
	$(CC) $(CCOPTS) -o $@ $^

udpserver: udpserver.c
	$(CC) $(CCOPTS) -o $@ $^

udpclient: udpclient.c
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -f $(TARGETS) *.o

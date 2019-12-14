CC:=g++
OBJS = sockop
TARGETS=server

all: $(TARGETS)	

$(OBJS).o: $(OBJS).cpp
	$(CC) -c -o $@ $<

cards.o:cards.cpp
	$(CC) -c -o cards.o cards.cpp

server: server.cpp $(OBJS).o cards.o
	$(CC) -pthread -g -o server $^

clean:
	rm *.o
	rm $(TARGETS)

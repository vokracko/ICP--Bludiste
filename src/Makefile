FLAGS=-std=c++11

.PHONY: server
.PHONY: client
.PHONY: errors

all: server client-gui client-cli
	make -C server all

server:
	make -C server

client-gui:
	make -C client gui

client-cli:
	make -C client cli

clean:
	make -C server clean
	make -C client clean
	rm -f *.o

errors: errors.cpp
	g++-4.8 $(FLAGS) -c errors.cpp -o errors.o

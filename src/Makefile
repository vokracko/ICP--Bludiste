FLAGS=-std=c++11

.PHONY: server
.PHONY: errors
all: server

server:
	make -C server bin

clean:
	make -C server clean

errors: errors.cpp
	g++ $(FLAGS) -c errors.cpp -o errors.o

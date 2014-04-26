FLAGS=-std=c++11

.PHONY: server
.PHONY: errors

all:
	make -C server all

server:
	make -C server bin

clean:
	make -C server clean
	make -C client clean
	rm *.o

errors: errors.cpp
	g++ $(FLAGS) -c errors.cpp -o errors.o

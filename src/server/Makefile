FLAGS=-std=c++11 -g3

all: clean bin

bin:  connection.o player.o server.o  game.o map.o bludiste2014-server.o errors
	g++ $(FLAGS) *.o ../errors.o -o bludiste2014-server -lboost_system -lpthread -lboost_filesystem

errors:
	make -C ../ errors

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o bludiste2014-server 2 > /dev/null


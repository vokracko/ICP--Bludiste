FLAGS=-std=c++11

all: bin

bin:  connection.o player.o server.o  game.o map.o bludiste2014-server.o monster.o errors
	g++-4.8 $(FLAGS) *.o ../errors.o -o bludiste2014-server -lboost_system -lpthread -static-libstdc++

errors:
	make -C ../ errors

%.o: %.cpp
	g++-4.8 $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o bludiste2014-server 2 > /dev/null


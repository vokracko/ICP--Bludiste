FLAGS=-std=c++11 -g3

all: clean bin

# TODO přidat mapu
bin:  connection.o player.o server.o  game.o bludiste2014-server.o
	g++ $(FLAGS) *.o -o bludiste2014-server -lboost_system -lpthread

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o bludiste2014-server 2 > /dev/null


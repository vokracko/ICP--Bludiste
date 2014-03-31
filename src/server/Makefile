FLAGS=-std=c++11

bin: server.o client.o connection.o bludiste2014-server.o
	g++ $(FLAGS) *.o -o bludiste2014-server -lboost_system

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o bludiste2014-server 2 > /dev/null


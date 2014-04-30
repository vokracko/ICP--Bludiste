
.PHONY: doxygen

all: server client-gui

server:
	make -C src server && mv src/server/bludiste2014-server .

client-gui:
	make -C src client-gui && mv src/client/gui/bludiste2014 .

client-cli:
	make -C src client-gui && mv src/client/cli/bludiste2014-cli .

run: client-gui server
	./bludiste2014 &
	./bludiste2014-server

pack: clean
	tar --exclude .git --exclude .gitignore --exclude xvokra00.tar.gz -zcvf xvokra00.tar.gz *

clean:
	rm -rf bludiste2014 bludiste2014-server bludiste2014-cli 2> /dev/null
	rm -rf doc xvokra00.tar.gz 2> /dev/null
	make -C src clean

doxygen: Doxyfile clean
	doxygen Doxyfile

# TODO mapy
# TODO překlad na merlinovi - qmake, g++-4.8

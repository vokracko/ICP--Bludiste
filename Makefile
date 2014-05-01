.PHONY: doxygen

all: server client cli

server:
	make -C src server && mv src/server/bludiste2014-server ./examples

client:
	make -C src client-gui && mv src/client/gui/bludiste2014 ./examples

cli:
	make -C src client-cli && mv src/client/cli/bludiste2014-cli ./examples

run: client server
	./examples/bludiste2014 &
	cd examples; ./bludiste2014-server

pack: clean
	tar --exclude .git --exclude .gitignore --exclude xvokra00.tar.gz -zcvf xvokra00.tar.gz *

clean:
	rm -rf examples/bludiste2014 examples/bludiste2014-server examples/bludiste2014-cli 2> /dev/null
	rm -rf doc xvokra00.tar.gz 2> /dev/null
	make -C src clean

doxygen: Doxyfile clean
	doxygen Doxyfile

# TODO mapy

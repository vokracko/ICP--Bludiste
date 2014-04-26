
.PHONY: doxygen

doxygen: Doxyfile clean
	doxygen Doxyfile

server:
	make -C src server && mv src/server/bludiste2014-server .

run: client server
	./bludiste2014-server
	./bludiste2014

pack: clean
	tar -f xvokra00 -z *

clean:
	rm -rf bludiste2014 bludiste2014-server bludiste2014-cli
	rm -rf doc
	make -C src clean

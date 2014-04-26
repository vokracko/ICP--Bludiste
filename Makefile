
.PHONY: doxygen

doxygen: Doxyfile clean
	doxygen Doxyfile

server:
	make -C src server && mv src/server/bludiste2014-server .

run: client server
	./bludiste2014-server
	./bludiste2014

clean:
	rm -rf bludiste2014 bludiste2014-server bludiste2014-cli
	rm -rf doc/*
	make -C src clean

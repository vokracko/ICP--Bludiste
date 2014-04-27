
.PHONY: doxygen

doxygen: Doxyfile clean
	doxygen Doxyfile

server:
	make -C src server && mv src/server/bludiste2014-server .

run: client server
	./bludiste2014-server
	./bludiste2014

pack: clean
	tar --exclude .git --exclude .gitignore --exclude xvokra00.tar.gz -zcvf xvokra00.tar.gz *

clean:
	rm -rf bludiste2014 bludiste2014-server bludiste2014-cli
	rm -rf doc xvokra00.tar.gz 2> /dev/null
	make -C src clean

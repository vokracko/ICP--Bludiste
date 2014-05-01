qmake=qmake
host=$(shell hostname)

ifeq ($(host),merlin.fit.vutbr.cz)
	qmake=/usr/local/share/Qt-5.2.1/5.2.1/gcc_64/bin/qmake
endif

.PHONY: cli gui qmake

all: cli gui

cli: qmake-cli
	make -C cli

gui: qmake-gui
	make -C gui


qmake-cli: cli/cli.pro
	cd cli; $(qmake)

qmake-gui: gui/gui.pro
	cd gui; $(qmake)

qmake: qmake-cli qmake-gui

clean: qmake
	make -C gui clean
	make -C cli clean

	rm -rf *.o cli/Makefile gui/Makefile


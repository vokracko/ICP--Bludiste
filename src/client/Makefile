.PHONY: cli gui

all: cli gui

cli: qmake-cli
	make -C cli

gui: qmake-gui
	make -C gui


qmake-cli: cli/cli.pro
	cd cli; qmake

qmake-gui: gui/gui.pro
	cd gui; qmake

qmake: qmake-cli qmake-gui

clean: qmake
	make -C gui clean
	make -C cli clean
	rm cli/Makefile
	rm gui/Makefile


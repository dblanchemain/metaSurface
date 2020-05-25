LIB ?= /usr/local/lib
INC = /usr/local/faust

DESTDIR ?=
PREFIX ?= 

prefix := $(DESTDIR)$(PREFIX)

all: padPlayer padPlayer2 metaLoop
padPlayer: simpleLecteur.cpp
	$(CXX)  -std=c++11 -O3 -Wall -g simpleLecteur.cpp -lsndfile -llo -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lLLVM  -I/c:/jack/includes -L/c:/jack/lib -ljack64 -I/usr/local/include -L/usr/local/lib -lfaust -lpthread `pkg-config  --libs  --cflags sndfile gtk+-2.0 ` -lOSCFaust -o padPlayer

padPlayer2: simpleLecteur2.cpp
	$(CXX)  -std=c++17 -O3 simpleLecteur2.cpp   -ljack -lsndfile -lfaust -llo -I/usr/include/gtk-2.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include  -lpthread `pkg-config   --libs --cflags jack sndfile gtk+-2.0  ` -lOSCFaust -o padPlayer2

 
metaSurface: main.cpp 
	$(CXX)  -std=c++17 -O3 -Wall -g apropos.cpp plugin.cpp colorSelector.cpp contraintesFx.cpp omni.cpp pave.cpp newSurface.cpp metaSurface.cpp surfaceSelect.cpp menu.cpp selectFile.cpp info.cpp parametres.cpp configuration.cpp main.cpp    -I$(INC) -lboost_system-mt -lboost_filesystem-mt  -I/c:/jack/includes -L/c:/jack/lib -ljack64 -lLLVM -lsndfile -I/usr/local/include -L/usr/local/lib -lfaust -lsfml-graphics -lsfml-window -lsfml-system -I/usr/include -llo  -lpthread `pkg-config  --cflags --libs  sndfile gtk+-2.0  glib-2.0  ` -lOSCFaust -o metaSurface.bin



install: 
	cp mcMidiPlayer.sh $(prefix)/bin
	chmod 755 $(prefix)/bin/mcMidiPlayer.sh
	cp mcMidiPlayer.bin  $(prefix)/bin
	chmod 755 $(prefix)/bin/mcMidiPlayer.bin
	mkdir $(prefix)/share/mcMidiPlayer 
	cp -Rfa Themes $(prefix)/share/mcMidiPlayer
	cp -Rfa gui $(prefix)/share/mcMidiPlayer
	cp -Rfa Lang $(prefix)/share/mcMidiPlayer
	cp midiPlayer $(prefix)/share/mcMidiPlayer
	chmod 755 $(prefix)/share/mcMidiPlayer
	cp simplePlayer2 $(prefix)/share/mcMidiPlayer
	chmod 755 $(prefix)/share/mcMidiPlayer
	cp parametres.conf $(prefix)/share/mcMidiPlayer


clean:
	rm -f metaloop.bin



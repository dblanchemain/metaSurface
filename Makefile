LIB ?= /usr/local/lib
INC = /usr/local/faust

DESTDIR ?=
PREFIX ?= 

prefix := $(DESTDIR)$(PREFIX)


metaSurface: main.cpp 
	$(CXX)  -std=c++17 -O3 apropos.cpp plugin.cpp colorSelector.cpp contraintesFx.cpp omni.cpp pave.cpp newSurface.cpp metaSurface.cpp surfaceSelect.cpp menu.cpp selectFile.cpp info.cpp parametres.cpp configuration.cpp main.cpp    -I$(INC) -L/usr/local/lib -lboost_system -lboost_filesystem -ljack -lsndfile -lfaust -lsfml-graphics -lsfml-window -lsfml-system -llo  -lpthread `pkg-config  --cflags --libs jack sndfile gtk+-2.0  glib-2.0  ` -lOSCFaust -o metaSurface.bin

clean:
	rm -f metaSurface.bin
	
install: 
	cp metaSurface.sh $(prefix)/bin
	chmod 755 $(prefix)/bin/metaSurface.sh
	cp metaSurface.bin  $(prefix)/bin
	chmod 755 $(prefix)/bin/metaSurface.bin
	mkdir $(prefix)/share/metaSurface 
	cp -Rfa Themes $(prefix)/share/metaSurface/
	cp -Rfa gui $(prefix)/share/metaSurface
	cp -Rfa Lang $(prefix)/share/metaSurface
	cp -Rfa surfaces $(prefix)/share/metaSurface
	cp -Rfa surfacesBkg $(prefix)/share/metaSurface
	cp -Rfa faust $(prefix)/share/metaSurface
	cp -Rfa sound $(prefix)/share/metaSurface
	echo Thème=base >> parametres.conf
	echo Lang=Fr >> parametres.conf
	echo dossierConfig=$(prefix)/share/metaSurface >> parametres.conf
	echo Editeur=emacs >> parametres.conf
	echo Navigateur=firefox >> parametres.conf
	echo Daw=Ardour >> parametres.conf
	echo port=3819 >> parametres.conf
	echo serveur=localhost >> parametres.conf
	echo OSC=5510 >> parametres.conf
	cp -Rfa parametres.conf $(prefix)/share/metaSurface

desinstall:

	rm -f $(prefix)/bin/metaSurface.bin
	rm -f $(prefix)/bin/metaSurface.sh
	rm -r $(prefix)/share/metaSurface
	
	



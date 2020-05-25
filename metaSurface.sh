#! /bin/sh

dir="${HOME}/metaSurface"
if [ -d ${dir} ] ; then
    echo "Le dossier paramètres ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier paramètres ${dir} est créé"
	cp  parametres.conf ${dir}	
fi
dir="${HOME}/metaSurface/surfaces"
if [ -d ${dir} ] ; then
    echo "Le dossier de travail ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier de travail ${dir} est créé"
fi
./metaSurface.bin "${HOME}/metaSurface" "${HOME}"

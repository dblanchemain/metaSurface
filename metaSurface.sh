#! /bin/sh

dir="${HOME}/metaSurface4"
if [ -d ${dir} ] ; then
    echo "Le dossier paramètres ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier paramètres ${dir} est créé"
	cp  ~/Compile/CodeBlocks/metaSurfaces3/parametres.conf ${dir}	
fi
dir="${HOME}/metaSurface2/surfaces"
if [ -d ${dir} ] ; then
    echo "Le dossier de travail ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier de travail ${dir} est créé"
fi
~/Compile/CodeBlocks/metaSurface4/metaSurface.bin "${HOME}/Compile/CodeBlocks/metaSurface4" "${HOME}"
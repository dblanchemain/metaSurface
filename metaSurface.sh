#! /bin/sh

dir="${HOME}/metaSurface"
if [ -d ${dir} ] ; then
    echo "Le dossier paramètres ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier paramètres ${dir} est créé"
	cp  parametres.conf ${dir}
fi
dir="${HOME}/metaSurface/Pad"
if [ -d ${dir} ] ; then
    echo "Le dossier des Pads ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier des Pads ${dir} est créé"
fi
dir="${HOME}/metaSurface/surfaces"
if [ -d ${dir} ] ; then
    echo "Le dossier des surfaces ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier des surfaces ${dir} est créé"
fi
dir="${HOME}/metaSurface/surfacesBkg"
if [ -d ${dir} ] ; then
    echo "Le dossier des pavages ${dir} existe"
else    
	dir="${HOME}/metaSurface"
	echo "Le dossier des pavages ${dir} est créé"
	cp  ./surfacesBkg ${dir}
fi
dir="${HOME}/metaSurface/sounds"
if [ -d ${dir} ] ; then
    echo "Le dossier des échantillons ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier des échantillons ${dir} est créé"
fi
dir="${HOME}/metaSurface/Plugins"
if [ -d ${dir} ] ; then
    echo "Le dossier des Plugins ${dir} existe"
else    
	mkdir ${dir}
	echo "Le dossier des Plugins ${dir} est créé"
	cp  ./Plugins/nplug.lib ${dir}
	cp  ./Plugins/usrPlugins ${dir}
fi
/usr/local/bin/metaSurface.bin "/usr/local/share/metaSurface" "${HOME}"

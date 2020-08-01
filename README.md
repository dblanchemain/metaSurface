# metaSurface64 
est une surface de contrôle de transformations continues du son en temps réel qui dispose à la fois de son propre générateur de boucles jusqu'à 64 voix et d'un moteur FX multieffets.

Chaque pavé de cette surface peut permettre de contôler directement le gain et les plug-ins attachés. Il est possible également de contrôler les pistes et les plug-ins d'un séquenceur externe (Ardour ou Reaper). Pour ce faire, l'application utilise des modules contrôlables par OSC qui proviennent de la librairie du langage Faust qui est embarqué dans l'application. Il est également possible de disposer d'une entrée externe pour un pavé.

Il est proposé d'écrire et d'intégrer de nouveaux plug-ins en langage Faust à la surface. Vous pouvez également définir les contrôleurs pour des plug-ins externes incorporés à votre DAW.

Enfin, vous pouvez créer de nouveaux pavages pour votre surface. 

Les fichiers audios des pavés peuvent être multicanaux. La sortie de chaque pavé sur Jack se règle indépendamment et peut être mono ou multicanal.

Pour intaller cette application :

git clone https://github.com/dblanchemain/metaSurface

make metaSurface
make install PREFIX=/usr/local

puis pour Linux :

./metaSurface.sh

La documentation est disponible ici :

http://blanchemain.info/Documents/Programmation/index.php?page=metaSurface

Cette version 1.0 a été réalisée et testée sur debian/LibraZik2

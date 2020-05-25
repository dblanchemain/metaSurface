# metaSurface 
est une surface de contrôle de transformations continues du son en temps réel qui dispose à la fois de son propre générateur de boucles jusqu'à 64 voix et d'un moteur FX multieffets.
Chaque pavé de cette surface peut permettre de contôler directement le gain et les plug-ins attachés. Il est possible également de contrôler les pistes d'un séquenceur externe (Ardour ou Reaper). Pour ce faire, l'application utilise des modules contrôlables par OSC qui proviennent de la librairie du langage Faust qui est embarqué dans l'application.
Les fichiers audios des pavés peuvent être multicanaux. La sortie de chaque pavé sur Jack se règle indépendamment et peut être mono ou multicanal.

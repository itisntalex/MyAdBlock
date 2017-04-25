# Réseau et système avancés : MyAdBlock #

Ce projet a été réalisé par:
 - Alexandre Jamet (LE)
 - Killian Raoux (LE)

Le système de compilation par défaut de ce projet est `cmake` et non `make`
son utilisation requiert l'installation d'une application du même nom, accessible
via les gestionnaire de paquets populaire `apt`, `brew`, etc...

Cependant un `Makefile` est joint à ce projet pour l'utiliser, il suffit de
réaliser la suite de commande suivante:

```sh
$ cd build
$ make
```

L'utilisation du bloqueur de publicité est extrêmement simple, rendez-vous dans
le répertoire `bin/` et exécuté le programme `MyAdBlock`. Il faut ensuite
configurer votre navigateur web à l'adresse `127.0.0.1` et au port `2017` et le
tour est joué.

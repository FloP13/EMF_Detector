# EMF_Detector
Projet d'introduction à l'IOT pour les 5eme année en Big Data à ESGI 2018 - 2019

**Groupe** : Thomas Dudoux, Ghiles Cherfaoui, Florian Papin


## Description du projet
Le but est de réaliser un détecteur EMF (ElectroMagnetif fields aka champs éléctromagnétique) pour mesurer en temps réel le champs magnétique auquel nous somme soumis en permanence.

Selon les valeurs mesuré un banc de 8 leds allant du vert au rouge s'allumeras pour signifier l'intensité des ondes captées.  
De la même manière un buzzer émettera un son (Do1 à Do8) en accord avec les leds pour exprimer la puissance des ondes captées.

Ce détecteur est aussi connecté en Wifi et lorsque utilisateur est connecté au meme wifi que notre appareil, ce dernier peut accéder à une page web qui montre en temps réelle la valeur mesuré par le détecteur.

Ce projet permetaussi de détecter les fantomes, les lutins et les greemlins !


## Sujets similaires
Martin De Bie avec son Tshirt antenne à réalisé un atelier englobe l'idée de croiser la science et l'art à travers les e-textiles et les objets à porter, en créant des artefacts technologiques faits à la main qui peuvent détecter les champs électromagnétiques.
[Workshop EMF Sensing textile](http://www.martindebie.com/education/emf-sensing-textile/)

Ou encore un EMF avec un arduino comme réalisé ici avec un petit ecran à led qui affiche la valeur en temps réels [Arduino EMF (Electromagnetic Field) Detector](https://www.instructables.com/id/Arduino-EMF-Detector/)


## Utilisation
Pour utiliser notre solution il vous faut tout d'abord configurer le wifi en décommentant la ligne 145, téléverser, se connecter au réseau WIFI "EMFSensor", configurer le WIFI de la carte, recommenter la ligne, re-téléverser, une fois ceci fait il faut se connecter au même wifi que celui configuré sur l'appareil, puis accéder à la l'adresse http://EMFSensor.local, enjoy.

##  Matériel utilisé
Pour réaliser ce projet il vous faudras :

### Matériel
- ESP8266MOD
- Une antenne
- Un buzzer
- Un banc de leds
- Des résistances
  - 3.3M Ohm pour l'antenne (orange, orange, vert)
  - 330 Ohm pour le buzzer (orange, orange, marron)

### Librairies
- Adafruit_NeoPixel
- WiFiManager
- ESP8266WiFi


## Schéma

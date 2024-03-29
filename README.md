# *Projet Weather Data*

![](RackMultipart20230525-1-7yasw7_html_9f4d251b08dd6c4d.png) ![](RackMultipart20230525-1-7yasw7_html_a91048167f7c9898.png)

### Prérequis :

- OS : Ubuntu
- QT Creator 5.15.2
- Dans le fichier 'Projet\_Final/ *config.json'* , changez la valeur de db\_location avec le chemin absolu de l'endroit où vous souhaitez que la base de données soit créée (préférablement le dossier Projet\_Final)

Le projet est divisé en plusieurs parties. L'installation va se faire partie par partie. Si vous avez déjà un langage/librairie/module d'une partie, vous pouvez passer l'étape correspondante.

### 1 - Avant de commencer les installations

*$ sudo apt update*

### 2 - Installations de la partie liée à Python et à la base de données

## Installation de Python 3 :

*$ sudo apt install python3*

## Installation de pip et du module "requests":

*$ sudo apt install python3-pip*

*$ pip3 install requests*

## Installation de SQLite3 et de DBBrowser (pour SQLite) :

*$ sudo apt install sqlite3*

*$ sudo apt install sqlitebrowser*

## Test de la partie liée à Python :

Afin de vérifier que les installations ci-dessus ont bien fonctionnées, lancez la commande suivante en étant situé dans le dossier *"Projet\_Final/python\_scripts"* :

*$ python3 weather.py*

### 3 - Installation de la partie liée au code C

## Installation de la librairie jansson :

*$ sudo apt install libjansson-dev*

## Installation de la librairie liée à SQLite3 :

*$ sudo apt-get install libsqlite3-dev*

## Installation de mosquitto MQTT broker :

*$ sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa*

*$ sudo apt-get update*

*$ sudo apt-get install mosquitto*

*$ sudo apt-get install mosquitto-clients*

*$ sudo apt clean*

## Installation de la librairie mosquitto :

*$ sudo apt install libmosquitto-dev*

## Test de la partie liée au code C :

Afin de vérifier que les installations ci-dessus ont bien fonctionnées, lancez les commandes suivantes en étant situé dans le dossier *"Projet\_Final/C\_programs"* :

*$ gcc main.c functions.c -o prog -ljansson -lsqlite3 -pthread -lmosquitto*

*$ ./prog*

Des fichiers .csv auront normalement été générés dans le dossier *"Projet\_Final/C\_programs/output"* , avec des données à l'intérieur.

### 4 - Installation de la partie liée au script C++

Qt Creator 5.15.2 est utilisé pour ce projet. Comme précisé dans les prérequis, il est considéré comme installé.

## Installation du module QtMqtt pour une installation dans QtCreator :

Clonez le projet [mqtt-git](https://github.com/qt/qtmqtt) depuis GitHub dans le dossier où QtCreator est installé :

*$ git clone https://github.com/qt/qtmqtt.git --branch 5.15.2*

Suite au clonage du projet, naviguez vers le nouveau fichier (qtmqtt) et installez le module en tapant les commandes suivantes (en pensant que vous avez peut être installé QtCreator dans un autre dossier):

*$ sudo ~/Qt/5.15.2/gcc\_64/bin/qmake*

*$ sudo make*

*$ sudo make install*

Une fois ceci fait, vous pouvez importer et utiliser le module MQTT dans QtCreator.

### 5 - Lancement du projet

Une fois que toutes les étapes d'installations et de compilations faites, vous pouvez désormais lancer les programmes Python et C en lançant le script " *run\_scripts.sh"* situé dans le dossier *"Projet\_Final"*

## Attribution de droits d'éxécution :

*$ chmod +x run\_scripts.sh*

## Lancement du programme :

*$ ./run\_scripts.sh*


# PLT

[![Actions Status](https://github.com/cbares/plt/workflows/PLT%20build/badge.svg)](https://github.com/cbares/plt/actions)


# Projet PLT - Jeu de Jamaica - (WIP)

Bienvenue dans le dépôt du jeu **Jamaica** ! Ce document vous guide à travers les étapes pour télécharger, configurer et compiler le client du jeu.

## Prérequis

Important : Le jeu est conçu pour tourner sous Linux. N'utilisez pas une version trop ancienne pour éviter tout problème de compatibilité.
Avant de commencer, assurez-vous d'avoir installé les éléments suivants :

- **CMake** (version 3.10 ou supérieure)
- **g++** (compilateur C++)
- **SFML** (Simple and Fast Multimedia Library)
- **Git** (pour cloner le dépôt)
- **Make** (pour la compilation)

### Installer les éléments manquants :

Vous pouvez par exemple installer la bibliothèque **SFML** avec votre gestionnaire de paquets :
```
sudo apt-get install libsfml-dev
```

### Cloner le répertoire Git

Positionnez vous et créez un dossier là ou vous souhaitez télécharger le jeu. Par exemple :
```
cd {chemin vers votre espace personnel}/Bureau
mkdir Jamaica
git clone https://github.com/Meliognir/PLT.git
```
Entrez ensuite dans ce répertoire avec la commande :
```
cd PLT
```
### Construire le client

Vous devez maintenant générer les fichiers d'en-têtes à partir du diagramme *state.dia*, puis construire client à partir du *main.c*. Pour cela, il suffit d'exécuter les commandes suivantes :
```
cd build
cmake ..
```

### Exécutez le client :

A cette étape, votre répertoire courant devrait être PLT/build. Dans ce cas, utilisez la commande suivante :
```
./../bin/client
```

### WIP : Le jeu est encore en développement, revenez plus tard si vous souhaitez tester ce jeu...

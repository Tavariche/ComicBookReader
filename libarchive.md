Téléchargement et compilation de libarchive.
________________________________________________

# Téléchargements
* **libarchive**: http://www.libarchive.org/
* **CMake** : https://cmake.org/
* **MinGW-get** : http://sourceforge.net/projects/mingw/files/ (télécharger l'éxécutable)

Décompresser libarchive dans un dossier et installer CMake et MinGW-get.

# Préparation de la compilation de libarchive
* Lancer "MinGW Installation Manager" accessible depuis la barre de recherche du menu démarrer.
Dans la section "MinGW Libraries" cocher les deux entrées "mingw32-libz".
Installer ces packages à l'aide du menu "Installation" -> "Apply changes".

* Se rendre dans la fenêtre des variables d'environnement et ajouter la variable "CC" pointant vers le compilateur gcc de Code::Blocks. Exemple : E:/Programmes/CodeBlocks/MinGW/bin/gcc.exe.

**/!\ La modification d'une variable d'environnement nécessite le redémarrage des programmes pour qu'elle soit prise en compte.**

# Compilation de libarchive
* 
* **Étape 1**
* Lancer "CMake gui" et choisir comme dossier source le dossier contenant le résultat de la décompression de l'archive libarchive.
* Choisir un dossier build vide.
* Cliquer sur "Configure" et choisir le compilteur "MinGW Makefiles" puis valider.
* A la fin de la configuration cliquer sur "Generate".

* 
* **Étape 2**
* Lancer une console et se rendre dans le dossier build sélectionné dans CMake.
* Lancer la commande "mingw32-make" et attendre la fin de la compilation. Si pas d'erreur, c'est déjà incroyable.

* 
* **Étape 3**
* Créer un nouveau dossier déstiné à contenir libachive.
* Copier/coller dedans le contenu du dossier *SOURCE_CMAKE/libarchive* et le fichier **libarchive.dll** situé dans *BUILD_CMAKE/bin*.
* Modifier le **App.pro** en indiquant le bon chemin vers le dossier contenant libarchive.

Normalement tout devrait fonctionner. Tester la compilation du projet ComicBookReader et vérifier que l'archive est bien décompressée dans le dossier temporaire (cf les variables d'environnement pour en connaître le chemin).
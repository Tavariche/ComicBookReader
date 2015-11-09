# README_ComicBookReader

Une liseuse de documents ComicBooks par Baptiste Studer et Gabriel Busnot

##Cahier des charges

* Formats fichiers de départ :
	* .zip
	* .rar
* Formats fichiers images :
	* .jpg / .jpeg
	* .png
	* .bmp
	* .gif
* Fonctionnalités minimales :
	* Tolérer tous les formats précisés y compris mélangés
	* Afficher page par page les fichiers
	* Proposer des boutons de navigation
	* Redimensionner les pages à des tailles égales adaptées avec filtrage CPU
	* Effectuer un préchargement parallélisé des pages proches
* Fonctionnalités améliorées :
	* Affichage des pages 2 par 2 si fenêtre du bon format
	* Permettre le redimensionnement de la fenêtre
	* Permettre le zoom (curseur et Ctrl + Molette)
	* Proposer la lecture manga
	* Défilement des pages à la molette
	* Accès rapide à un numéro de page
	* Enregistrement dans un autre format des pages
* Fonctionnalités avancées :
	* Création d'un ComicBook depuis un ensemble d'images
	* Filtrage GPU avec compatibilité maximale (pas de galère nVidia only etc.)
	* Convertion PDF ???
	* Lecture en mode continu (pages les une sous les autres qui défilent à la souris)

##Trucs à faire

* ~~Passer le mémo C++ en MarkDown~~
* Conception logiciel en UML ???
* Design interface

##Notes diverses

* [Compilation **sans DLL** !](https://openclassrooms.com/courses/compiler-et-utiliser-des-applications-developpees-avec-qt-sans-dll) Incompatible avec le multithread... DLL indépendante de Qt
* [ImageMagic (Magick++)](http://www.imagemagick.org/Magick++/) : une bibliothèque de traitement d'images qui utilise parfois le GPU... A préciser
* Qt propose tout ce dont on peut avoir besoin en dehors de l'aspect GPU, et encore.
	* QtConcurrent::run() pour le parallélisme
	* QImage pour tous les formats à supporter
	* qUncompress pour la décompression


test pc
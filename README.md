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

##Implémentation de quelques fonctionnalités

###Préchargement des pages

Utiliser un conteneur de pointeurs trié par priorités (buffer) comme suit : page courante -> page suivante -> page précédente -> première page -> dernière page.

Au chargement d'un CB, remplir le buffer et charger les pages dans l'ordre (avec thread par la suite).

Au changement de page, màj du buffer : placer la nouvelle page courante en stockant la précédente dans une variable teporaire. Stocker la précédente principale à sa nouvelle place si elle reste dans le buffer et stocker la page remplacée dans la variable temporaire. Ainsi de suite jusqu'à ce que la variable temporaire ne contienne plus une page qui doit rester dans le buffer. Dans ce cas, décharger la page de la variable temporaire.

Passer sur la case 2 du buffer et opérer de même, puis sur la case 3. Les cases 4 et 5 restent inchangées.

*Remarques : Utiliser un template pour rendre le mécanisme fonctionnel avec affichage page double.

**Exemple**

* Ouverture du fichier
    * 1 - 2 - ?(1 null dernier ...) - 1 - dernière
* Avance de 1
    * temp <- 1
    * case 1 <- 2 ; page déjà chargée
    * case 3 <- temp (1) (nouvelle place de 1) ; page déjà chargée
    * temp <- null ; passage en case 2
    * 2 - 2 - 1 - 1 - d
    * temp <- 2
    * case 2 <- 3 ; lancement du chargement
    * 2 déjà placé ; passage case 3
    * 2 - 3 - 1 - 1 - d
    * 1 à la bonne place ; fin de l'algo de changement de page.

###Stockage des pages

A l'ouverture d'un CB, créer un vecteur de classes page contenant entre autre : un pixmap (ou QImage, cf rqe) au format d'origine chargé quand la page est dans le buffer, un pixmap mignature créé directement, un pixmap au format d'affichage calculé quand la page est dans le buffer.

*Remarque : pour certaines transformations, le QImage est plus efficace car un Qpixmap peut être converti vers QImage avant transformation puis reconverti après en Qpixmap à notre insu. Autant partir du QImage et faire la conversion soi-même dans ce cas.*

###Enregistrement des paramètres du programme

Qt contient une classe QSettings prévue pour ça. Il faut respécter quelques contraintes et la sauvegarde/récupération des paramètres est automatique, triviale et adaptée à l'OS.

##Notes diverses

* [Compilation **sans DLL** !](https://openclassrooms.com/courses/compiler-et-utiliser-des-applications-developpees-avec-qt-sans-dll) Incompatible avec le multithread... DLL indépendante de Qt
* [ImageMagic (Magick++)](http://www.imagemagick.org/Magick++/) : une bibliothèque de traitement d'images qui utilise parfois le GPU... A préciser
* Qt propose tout ce dont on peut avoir besoin en dehors de l'aspect GPU, et encore.
	* QtConcurrent::run() pour le parallélisme
	* QImage pour tous les formats à supporter
	* qUncompress pour la décompression
* Pour adapter la taille des pages à la fenêtre, pas de signal `resized(size)` pour un widget. Regarder du côté des mécanismes d'event. (`QWidget::resizeEvent`)
#Qt

##Les bases

##Généralités

###[La doc en ligne](http://qt-project.org/doc)
###Le code minimal
	#include <QApplication>
	 
	int main(int argc, char *argv[])
	{
	    QApplication app(argc, argv);
	    return app.exec();
	}

Ajouter au fichier .pro la ligne `QT += widgets`

* `#include <QtWidgets>` -> Pour être tranquille
* `Element.show()` -> Afficher un élément
* `element.attribut()` -> Accesseur de lecture d'attribut
* `element.setAttribut()` -> Accesseur d'écriture d'attribut
* `QCoreApplication::applicationDirPath() + "/chemin"` -> chemin relatif universel

##Evenements et slots

Utiliser la méthode statique suivante :

	QObject::connect(*emetteur, SIGNAL(signal()), *recepteur, SLOT(slot())

* `qApp` -> Pointeur vers l'application principale créé automatiquement
* `public slots:` -> Environnement des slots personnalisés d'un objet
* `signals:` -> Environnement des signals personnalisés d'un objet
	* On implémente pas un signal
	* un signal renvoit toujours void et passe ses arguments au slot connecté
	* écrire `emit monSignal()` là où le signal doit être émis

##Positionnement grace aux layouts

* `layout->addWidget(unWidget)` -> Ajouter un widget au layout
* `QVBoxLayout *layout = new QVBoxLayout` -> Layout vertical
	* `QHBoxLayout` -> Layout horizontal
	* `QFormLayout` -> Layout Formulaire
* `fenetre.setLayout(layout)` -> Appliquer un layout
* `QGridLayout::addWidget(widget, i, j, rowSpan, colSpan)` -> Layout grille avec coordonnées matricielles

##Des widgets et leurs propriétés

La destruction des éléments fils d'un widget est automatique dans Qt.

L'ajout de & devant un caractère dans le nom d'un widget en fait un raccourci clavier lorsque c'est pertinent.

###La Fenêtre principale

* `class QMainWindow` -> class dont hérite notre class de fenêtre principale
* `meth setCentralWidget(unWidget)` -> Indiquer le widget de la zone centrale
	* `class QWidget` pour du Single Document Interface
	* `class QMdiArea` pour du Multiple DI
		* `meth addSubWindow(unWidget)` -> Ajout d'une sous fenêtre de zone MDI
		* `meth removeSubWindow(*QMidSubWindow)` -> Fermer une sous fenêtre
		* `meth subWindowList()` -> Liste de sous fenêtres
* `QMenu *menuFichier = menuBar()->addMenu("&Fichier")` -> Ajout d'un menu Fichier à la barre de menu (Ctrl+F)
	* `class QAction` -> Une action d'un menu ou de la barre d'outils
		* `sig triggered()` -> Action sélectionnée
		* `sig hovered()` -> Souris sur l'action
		* `meth setShortcut(QKeySequence("Ctrl+Q"))` -> Créer un raccourci
		* `meth setIcon(QIcon("image.png"))` -> Definir une icône
		* `meth setCheckable(true)` -> Cochable
	* `meth addAction` -> Ajouter une action à un menu
	* `meth addmenu` -> Créer un sous menu (`QMenu`)
* `QToolBar *toolBarFichier = addToolBar()` -> Ajout d'une barre d'outils à la fenêtre principale
	* `meth addAction()` -> Ajouter une action
	* `meth addWidget()` -> Ajouter un widget quelconque
	* `meth addSeparator()` -> Ajouter un séparateur

###Autre widgets courants

* `class QWidget` -> Fenêtre de base
	* `prop cursor` -> Curseur au survol
	* `prop enabled` -> Widget utilisable ou non
	* `prop height, width, size` -> Dimensions
	* `prop visible` -> Visibilité
	* Fenêtres seulement :
		* `class QMainWindow` -> Fenêtre principale
		* `class QDialog` -> Boîte de dialogue de base (personnalisable)
* Conteneurs
	* `class QTabWidget` -> Conteneur à onglets
		* Un seul widget par onglet (QWidget qui contient les autres)
		* ` meth addTab(&unQWidget)` -> Ajout d'un onglet
* `class QAbstractButton`
	* `class QPushButton` -> Bouton standard
	* `classQRadioButton` -> Bouton radio pour fair eun choix
	* `class QCheckBox` -> Case à cocher
		* `sig stateChanged(bool)` -> Siganl de changement d'état
		* `meth isChecked()` -> True ssi cochée
	* `calss QGroupBox` -> Regroupe des cases à cocher ou des boutons radio
* Afficheurs
	* `class QLabel` -> Boîte de dialogue
	* `class QProgressBar` -> Barre de progression
		* `prop maximum` -> Définir le max
		* `prop minimum` -> Définir le min
		* `prop value` -> Valeur actuelle
		* `sig valueChanged(int)` -> Signal de changement de valeur
* Champs
	* `class QLineEdit` -> Champ de texte à une ligne
		* `prop text` -> Texte contenu
		* `prop alignment` -> Alignement du texte
		* `prop echoMode` -> Mode d'affichage du contenu
		* `prop inputMask` -> Masque de saisie
		* `prop maxLength` -> Longueur maximale
		* `prop readOnly` -> Lecture seule
		* `sig returnPressed()` -> Entrée pressé
		* `sig textChanged()` -> Text changé
	* `class QTextEdit` -> Champ de texte à plusieurs lignes avec mise en forme
		* `prop plainText` -> Contenu en texte brut
		* `prop html` -> Contenu enrichi HTML
	* `class QSpinBox` -> Champ de saisie de nombre entier
		* `prop value` -> Valeur contenue
		* `prop accelerated` -> Accélération du défilement autorisée
		* `prop minimum maximum` -> Fixe le min et le max
		* `prop singleStep` -> Pas de varitaion
		* `prop prefix suffix` -> Texte avant et après le nombre
	* `class QDoubleSpinBox` -> Champ de saisie de double
		* Même prop que `QSpinBox`
		* `prop decimals ` -> Nombre de décimales à afficher
	* `class QSlider` -> Curseur
		* Prop communes avec `QSpinBox`
		* `prop orientation` -> Orientation V ou H
		* 
	* `class QComboBox` -> Liste déroulante
		* `prop count` -> Nb d'éléments dans la liste
		* `prop currentIndex` -> Index sélectionné
		* `prop editable` -> Autorise l'ajout de valeurs personnalisées
		* `sig currentIndexChanged()` -> Indique que l'index a changé
		* `sig highlighted()` -> Element survolé